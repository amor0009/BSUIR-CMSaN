import socket
import time
import os
import select

BIND_ADDRESS = "172.20.10.5"
BIND_PORT = 54321
OPT_INTERVAL = 10
OPT_COUNT = 3
FRAME_SIZE = 8192


def setOptions(clientSocket):
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
    clientSocket.setsockopt(socket.SOL_TCP, socket.TCP_USER_TIMEOUT, 30000)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, OPT_COUNT)

    return clientSocket


def downloadStart(conn, fileName, commandText):
    if not os.path.exists(fileName):
        conn.send("0".encode())
        return (False, "Файл \"" + fileName + "\" не найден.")

    conn.send("1".encode())

    file = open(fileName, 'rb')
    fileSize = os.path.getsize(fileName)
    offset = int(conn.recv(FRAME_SIZE).decode())
    conn.sendall(str(fileSize).encode() + b"\n")
    file.seek(offset, 0)

    socketsToWrite.append(conn)
    setFileProperties(conn, True, file, fileSize, offset, commandText)
    printStartFileLoading(conn, fileName, False)
    return (True, None)


def downloadFile(conn):
    data = properties[conn.fileno()][2].read(FRAME_SIZE)

    if data:
        conn.send(data)
        # print("# Отправлена порция данных на", properties[conn.fileno()][0][0])
        return False
    else:
        return True


def downloadEnd(conn):
    properties[conn.fileno()][2].close()
    socketsToWrite.remove(conn)
    command = properties[sock.fileno()][5]
    setFileProperties(conn, False, None, None, None, "")
    return command, "Файл передан успешно."


def uploadStart(conn, fileName, commandText):
    clientHasFile = conn.recv(1).decode()
    if clientHasFile == "0":
        return (False, conn.recv(FRAME_SIZE).decode())

    mode = 'ab' if os.path.exists(fileName) else 'wb+'

    file = open(fileName, mode)
    fileSize = int(conn.recv(FRAME_SIZE).decode())
    conn.send(str(os.path.getsize(fileName)).encode())
    offset = os.path.getsize(fileName)
    file.seek(0, os.SEEK_END)

    setFileProperties(conn, True, file, fileSize, offset, commandText)
    printStartFileLoading(conn, fileName, True)
    return (True, None)


def uploadFile(conn):
    fileno = conn.fileno()
    if properties[fileno][3] > properties[fileno][4]:
        data = conn.recv(min(FRAME_SIZE, properties[fileno][3]))
        properties[fileno][3] -= len(data)
        properties[fileno][2].write(data)
        # print("# Принята порция данных от", properties[fileno][0][0])

    if properties[fileno][3] > properties[fileno][4]:
        return False
    else:
        return True


def uploadEnd(conn):
    properties[conn.fileno()][2].close()
    command = properties[sock.fileno()][5]
    setFileProperties(conn, False, None, None, None, "")
    return command, "Файл загружен успешно."


def echo(data):
    return data


def _time():
    currentTime = time.asctime(time.localtime())
    return "Время сервера: " + currentTime


def exit():
    return "Отключение от сервера..."


def handleCommand(conn, clientInput):
    command, argument = clientInput.partition(" ")[::2]

    match (command.lower()):
        case "echo":
            response = echo(argument)

        case "time":
            response = _time()

        case "download":
            response = downloadStart(conn, argument, clientInput)

        case "upload":
            response = uploadStart(conn, argument, clientInput)

        case "exit":
            response = exit()

        case _:
            response = "Такой команды не существует!"

    return command, response


def printLog(clientInput, response, addr):
    print("Команда пользователя", addr[0])
    print("Содержание:", clientInput)
    print("Ответ:", response, "\n")


def printStartFileLoading(conn, fileName, dir):
    if dir:
        print(f"\nНачат приём файла {fileName}\n"
              f"Отправитель: {properties[conn.fileno()][0][0]}\n")
    else:
        print(f"\nНачата передача файла {fileName}\n"
              f"Получатель: {properties[conn.fileno()][0][0]}\n")


def unregClient(conn):
    del properties[conn.fileno()]
    connections.remove(conn)
    conn.close()
    print("Всего подключено:", len(connections) - 1, '\n')


def regClient(conn, addr):
    connections.append(conn)
    properties[conn.fileno()] = [addr, False, None, None, None, ""]
    print("Всего подключено:", len(connections) - 1, '\n')


def setFileProperties(conn, loading, fd, bytesRemaining, offset, commandText):
    properties[conn.fileno()] = [properties[conn.fileno()][0], loading, fd, bytesRemaining, offset, commandText]


# ------------

try:
    connections = []
    socketsToWrite = []
    properties = {}
    # properties[0] = адрес
    # properties[1] = наличие загрузки файла
    # properties[2] = файловый дескриптор
    # properties[3] = байтов осталось
    # properties[4] = смещение
    # properties[5] = текст команды

    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket = setOptions(serverSocket)
    serverSocket.bind((BIND_ADDRESS, BIND_PORT))
    serverSocket.listen()

    serverSocket.setblocking(False)

    connections.append(serverSocket)

    print("Сервер начал работу.\n")

    while (True):
        readReady, writeReady, socketsWithErrors = select.select(connections, socketsToWrite, connections)

        for sock in readReady:
            if sock == serverSocket:
                clientConn, clientAddr = serverSocket.accept()
                print("Обнаружено подключение\n" + "Адрес:", clientAddr[0])
                regClient(clientConn, clientAddr)
                continue

            try:
                if properties[sock.fileno()][1] == True:
                    end = uploadFile(sock)
                    if (end):
                        command, response = uploadEnd(sock)
                        sock.send(response.encode())
                        printLog(command, response, properties[sock.fileno()][0])
                    continue

                clientInput = sock.recv(FRAME_SIZE).decode()
                if not clientInput:
                    print('Обрыв соединения с', properties[sock.fileno()][0])
                    if sock in socketsToWrite:
                        socketsToWrite.remove(sock)
                    unregClient(sock)
                    continue

                else:
                    command, response = handleCommand(sock, clientInput)
                    if ((command == 'upload' or command == 'download') and response[0] == True):
                        continue

                    sock.send((response[1] if type(response) is tuple else response).encode())
                    printLog(clientInput, response[1] if type(response) is tuple else response,
                             properties[sock.fileno()][0])

                    if clientInput == 'exit':
                        print('Клиент', properties[sock.fileno()][0], 'отключился.')
                        unregClient(sock)

            except socket.error:
                print('\nОбрыв соединения с', properties[sock.fileno()][0])
                if sock in socketsToWrite:
                    socketsToWrite.remove(sock)
                unregClient(sock)

        for sock in writeReady:
            try:
                if properties[sock.fileno()][1] == True:
                    end = downloadFile(sock)
                    if (end):
                        command, response = downloadEnd(sock)
                        sock.send(response.encode())
                        printLog(command, response, properties[sock.fileno()][0])

            except socket.error:
                print('\nОбрыв соединения с', properties[sock.fileno()][0])
                if sock in socketsToWrite:
                    socketsToWrite.remove(sock)
                unregClient(sock)

        for sock in socketsWithErrors:
            print('\nОбрыв соединения с', properties[sock.fileno()][0])
            if sock in socketsToWrite:
                socketsToWrite.remove(sock)
            unregClient(sock)

except KeyboardInterrupt:
    print("\nЗавершение работы.\n")