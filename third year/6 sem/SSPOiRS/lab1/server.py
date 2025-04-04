import socket
import time
import os

BIND_ADDRESS = "0.0.0.0"
BIND_PORT = 65432
OPT_INTERVAL = 5
OPT_COUNT = 3
FRAME_SIZE = 1024


def setOptions(clientSocket):
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, OPT_COUNT)

    return clientSocket


def reconnect(serverSocket, clientSocket):
    print("Соединение разорвано.")
    clientSocket.close()
    clientSocket, clientAddr = serverSocket.accept()

    global lastClientAddr
    if clientAddr[0] == lastClientAddr[0]:
        print("Соединение восстановлено.\n")
    else:
        print("Обнаружено подключение\n"
              "Адрес:", clientAddr[0], "\n")
    connected = True

    lastClientAddr = clientAddr

    return clientSocket


def download(fileName, clientSocket):
    """Обрабатывает команду загрузки файла с сервера."""
    if not os.path.exists(fileName):
        clientSocket.send("0".encode("utf-8"))  # Файл не найден
        return f"Файл \"{fileName}\" не найден."

    clientSocket.send("1".encode("utf-8"))  # Файл существует

    downloadFile(fileName, clientSocket)
    time.sleep(2)
    return "Файл передан успешно."


def downloadFile(fileName, clientSocket):
    """Передаёт файл клиенту с возможностью докачки."""
    fileSize = os.path.getsize(fileName)

    # Получаем оффсет от клиента (10 байт - целое число)
    offsetData = clientSocket.recv(10)
    if not offsetData:
        return

    offset = int(offsetData.decode("utf-8").strip())

    # Отправляем заголовок с полным размером файла (10 байт - целое число)
    clientSocket.send(f"{fileSize:010}".encode("utf-8"))

    # Начинаем отправку файла с указанного оффсета
    with open(fileName, 'rb') as file:
        file.seek(offset)
        if(offset != 0):
            print(f"Продолжение загрузки с оффсета: {offset}")
        else:
            print(f"Начало загрузки. Оффсет: {offset}")

        while True:
            data = file.read(FRAME_SIZE)
            if not data:
                break
            try:
                clientSocket.send(data)
            except socket.error:
                print("Загрузка прервана.")
                return  # Прерывание загрузки из-за ошибки соединения

    print("Загрузка завершена.")


def upload(fileName):
    clientHasFile = clientSocket.recv(1).decode("utf-8")
    if clientHasFile == "0":
        return clientSocket.recv(FRAME_SIZE).decode("utf-8")

    uploadFile(fileName)
    return "Файл загружен успешно."


def uploadFile(fileName):
    mode = 'ab' if os.path.exists(fileName) else 'wb+'

    with open(fileName, mode) as file:
        fileSize = int(clientSocket.recv(FRAME_SIZE).decode("utf-8"))
        clientSocket.send(str(os.path.getsize(fileName)).encode("utf-8"))
        offset = os.path.getsize(fileName)
        if (offset != 0):
            print(f"Продолжение загрузки с оффсета: {offset}")
        else:
            print(f"Начало загрузки. Оффсет: {offset}")
        file.seek(0, os.SEEK_END)

        while fileSize > offset:
            try:
                data = clientSocket.recv(FRAME_SIZE)
                if not data:
                    break
                file.write(data)
                offset += len(data)
            except socket.error:
                print("Загрузка прервана.")
                return  # Прерывание загрузки из-за ошибки соединения

    print("Загрузка завершена.")


def echo(data):
    if data:
        return data
    return "Команда 'echo' требует аргумент."


def _time():
    currentTime = time.asctime(time.localtime())
    return "Время сервера: " + currentTime


def exit():
    global connected
    connected = False
    return "Отключение от сервера..."


def handleCommand(clientInput):
    command, argument = clientInput.partition(" ")[::2]
    match (command.lower()):
        case "echo":
            response = echo(argument)

        case "time":
            response = _time()

        case "download":
            response = download(argument, clientSocket)

        case "upload":
            response = upload(argument)

        case "exit":
            response = exit()

        case _:
            response = "Такой команды не существует!"

    return response


def printLog(clientInput, response):
    print("Команда пользователя:", clientInput)
    print("Ответ:", response, "\n")


# ------------
try:
    connected = False
    lastClientAddr = 0

    print("Сервер начал работу.\n")

    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket = setOptions(serverSocket)
    serverSocket.bind((BIND_ADDRESS, BIND_PORT))
    serverSocket.listen()

    while (True):
        clientSocket, clientAddr = serverSocket.accept()
        print("Обнаружено подключение\n"
              "Адрес:", clientAddr[0], "\n")
        connected = True
        lastClientAddr = clientAddr

        clientSocket = setOptions(clientSocket)

        while (connected):
            try:
                clientInput = clientSocket.recv(FRAME_SIZE).decode("utf-8")
                response = handleCommand(clientInput)
                clientSocket.send(response.encode("utf-8"))
                printLog(clientInput, response)

            except socket.error:
                clientSocket = reconnect(serverSocket, clientSocket)
except KeyboardInterrupt:
    print("\nЗавершение работы.\n")