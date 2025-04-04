import socket
import os
import time

HOST_ADDRESS = "172.20.10.5"
HOST_PORT = 65432
OPT_INTERVAL = 5
OPT_COUNT = 3
FRAME_SIZE = 4096

exitFlag = False


def setOptions(clientSocket):
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, OPT_COUNT)

    return clientSocket


def connect(clientSocket):
    clientSocket = setOptions(clientSocket)
    clientSocket.connect((HOST_ADDRESS, HOST_PORT))
    return clientSocket


def reconnectPrompt():
    print("Соединение разорвано.",
          "\nХотите попробовать восстановить соединение? [y/n]")

    answer = input()
    if (answer[0] == "Y") or (answer[0] == "y"):
        return True

    return False


def upload(filePath):
    if not os.path.exists(filePath):
        clientSocket.send("0".encode("utf-8"))
        clientSocket.send(("Файл \"" + filePath + "\" не найден.").encode("utf-8"))
        return clientSocket.recv(FRAME_SIZE).decode("utf-8")

    clientSocket.send("1".encode("utf-8"))

    startTime = time.time()
    offset, fileSize = uploadFile(filePath)
    endTime = time.time()


    speed = "{:.2f}".format((fileSize - offset) / (endTime - startTime) / 1024)
    print("Скорость загрузки:", speed, "КБ/с")
    return clientSocket.recv(FRAME_SIZE).decode("utf-8")


def uploadFile(filePath):
    with open(filePath, 'rb') as file:
        clientSocket.send(str(os.path.getsize(filePath)).encode("utf-8"))
        offset = int(clientSocket.recv(FRAME_SIZE).decode("utf-8"))

        if (offset != 0): 
            print(f"Продолжение загрузки с оффсета: {offset}")
        else:
            print(f"Начало загрузки. Оффсет: {offset}")

        file.seek(offset, 0)
        while True:
            data = file.read(FRAME_SIZE)
            if not data:
                break
            clientSocket.send(data)

    file.close()
    return (offset, os.path.getsize(filePath))


def download(filePath, clientSocket):
    """Запрашивает у сервера файл и загружает его."""
    serverHasFile = clientSocket.recv(1).decode("utf-8")
    if serverHasFile == "0":
        return clientSocket.recv(FRAME_SIZE).decode("utf-8")

    startTime = time.time()
    offset, fileSize = downloadFile(filePath, clientSocket)
    endTime = time.time()

    speed = "{:.2f}".format(offset / (endTime - startTime) / 1024)
    print("Скорость загрузки:", speed, "КБ/с")
    
    return clientSocket.recv(FRAME_SIZE).decode("utf-8")

def downloadFile(filePath, clientSocket):
    """Принимает файл от сервера, поддерживает докачку."""
    mode = 'ab' if os.path.exists(filePath) else 'wb+'
    with open(filePath, mode) as file:
        offset = os.path.getsize(filePath)

        clientSocket.send(f"{offset:010}".encode("utf-8"))

        fileSizeData = clientSocket.recv(10)
        if not fileSizeData:
            return offset, offset 

        fileSize = int(fileSizeData.decode("utf-8").strip())

        if (offset != 0): 
            print(f"Продолжение загрузки с оффсета: {offset}")
        else:
            print(f"Начало загрузки. Оффсет: {offset}")
        
        
        startTime = time.time()
        while offset < fileSize:
            try:
                data = clientSocket.recv(FRAME_SIZE)
                if not data:
                    break
                file.write(data)
                offset += len(data)
            except socket.error:
                print("Загрузка прервана.")
                return offset, fileSize

    return offset, fileSize

def exit():
    global exitFlag
    exitFlag = True


def otherCommand(userInput):
    return clientSocket.recv(FRAME_SIZE).decode("utf-8")


def handleCommand(userInput):
    command, argument = userInput.partition(" ")[::2]

    match (command.lower()):
        case "upload":
            response = upload(argument)

        case "download":
            response = download(argument, clientSocket)

        case _:
            response = otherCommand(userInput)

    if (userInput.lower() == "exit"):
        exit()

    return response


try:
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket = connect(clientSocket)
    print("Соединение установлено.\n")

    while not exitFlag:
        try:
            userInput = input("> ")
            while userInput == "":
                userInput = input("> ")
            clientSocket.send(userInput.encode("utf-8"))
            response = handleCommand(userInput)
            print(response, "\n")

        except socket.error:
            clientSocket.close()
            try:
                result = reconnectPrompt()
                if (result):
                    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    clientSocket = connect(clientSocket)
                    print("Соединение восстановлено.\n")
                else:
                    exitFlag = True
            except socket.error:
                print("Не удалось восстановить подключение.")
                exitFlag = True

except socket.error:
    print("Сервер недоступен.\n")
except KeyboardInterrupt:
    print("\nЗавершение работы.\n")

finally:
    clientSocket.close()