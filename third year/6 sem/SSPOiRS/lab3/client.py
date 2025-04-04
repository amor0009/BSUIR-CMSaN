import socket
import os
import time
import select

SERVER_ADDRESS = "172.20.10.5"
SERVER_PORT = 54321
OPT_INTERVAL = 10
OPT_COUNT = 3
BUF_SIZE = 1024

exitFlag = False

def setOptions(clientSocket):
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
  #  clientSocket.setsockopt(socket.SOL_TCP, socket.TCP_USER_TIMEOUT, 30000)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, OPT_COUNT)

    return clientSocket

def connect(clientSocket):
    clientSocket = setOptions(clientSocket)
    clientSocket.connect((SERVER_ADDRESS, SERVER_PORT))
    return clientSocket

def reconnectPrompt():
    print("Соединение разорвано.",
          "\nХотите попробовать восстановить соединение? [y/n]")
    
    answer = input()
    if len(answer) <= 0:
        return False
    if (answer[0] == "Y") or (answer[0] == "y"):
        return True
    
    return False

def upload(filePath):
    if not os.path.exists(filePath):
        clientSocket.send("0".encode())
        clientSocket.send(("Файл \"" + filePath + "\" не найден.").encode())
        return clientSocket.recv(BUF_SIZE).decode()

    clientSocket.send("1".encode())

    offset, fileSize = uploadFile(filePath)
    
    return clientSocket.recv(BUF_SIZE).decode()

def uploadFile(filePath):
    with open(filePath, 'rb') as file:
        fileSize = os.path.getsize(filePath)
        clientSocket.send(str(os.path.getsize(filePath)).encode())
        offset = int(clientSocket.recv(BUF_SIZE).decode())
        file.seek(offset, 0)

        while offset < fileSize:
            # print("#")
            data = file.read(BUF_SIZE)
            clientSocket.send(data)
            fileSize -= len(data)

    file.close()
    return (offset, os.path.getsize(filePath))

def download(filePath):
    serverHasFile = clientSocket.recv(1).decode()
    if serverHasFile == "0":
        return clientSocket.recv(BUF_SIZE).decode()
    
    offset, fileSize = downloadFile(filePath)

    return clientSocket.recv(BUF_SIZE).decode()
    

def downloadFile(fileName):
    mode = 'ab' if os.path.exists(fileName) else 'wb+'

    with open(fileName, mode) as file:
        offset = os.path.getsize(fileName)
        clientSocket.send(str(offset).encode())
        # fileSize = int(clientSocket.recv(BUF_SIZE).decode())

        size_data = b""
        while b"\n" not in size_data:
            size_data += clientSocket.recv(1)

        fileSize = int(size_data.decode().strip())  

        file.seek(0, os.SEEK_END)

        while fileSize > offset:
            # print("#")
            data = clientSocket.recv(BUF_SIZE if BUF_SIZE < fileSize - offset else fileSize - offset)
            fileSize -= len(data)
            file.write(data)

    file.close()
    return (offset, os.path.getsize(fileName))

def exit():
    global exitFlag
    exitFlag = True

def otherCommand(userInput):
    return clientSocket.recv(BUF_SIZE).decode()

def handleCommand(userInput):
    command, argument = userInput.partition(" ")[::2]

    match (command.lower()):
        case "upload":
            response = upload(argument)
        
        case "download":
            response = download(argument)

        case _:
            response = otherCommand(userInput)

    if (userInput.lower() == "exit"):
        exit()

    return response

#------------

try:
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket = connect(clientSocket)
    print("Соединение установлено.\n")

    while not exitFlag:
        try:
            userInput = input("> ")
            while userInput == "":
                userInput = input("> ")
            clientSocket.send(userInput.encode())
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