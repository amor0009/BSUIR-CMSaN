#include <iostream>
#include <fstream>
#include <Winsock2.h>
#include <Ws2bth.h>
#include <clocale>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Bthprops.lib")

int getFile(SOCKET clientSocket)
{
    char fileSize[100];
    memset(fileSize, '\0', 100);
    if (!recv(clientSocket, fileSize, 100, 0))
        return -1;
    int dataSize = atoi(fileSize);

    if (dataSize <= 0)
        return 0;

    std::ofstream outputFile("./recFile.mp3", std::ios::out | std::ios::binary | std::ios::trunc);
    while (dataSize > 0)
    {
        char buffer[1024];
        int bytes = recv(clientSocket, buffer, min(1024, dataSize), 0);
        outputFile.write(buffer, bytes);
        dataSize -= bytes;
    }


    outputFile.close();

    system("start ./recFile.mp3");

    return 0;
}

SOCKET initServerSocket()
{
    SOCKADDR_BTH sockaddrBthServer = { 0 };
    sockaddrBthServer.addressFamily = AF_BTH;
    sockaddrBthServer.serviceClassId = RFCOMM_PROTOCOL_UUID;
    sockaddrBthServer.port = 6;

    SOCKET serverSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    bind(serverSocket, reinterpret_cast<sockaddr*>(&sockaddrBthServer), sizeof(sockaddrBthServer));

    return serverSocket;
}

SOCKET initClientSocket(SOCKET serverSocket)
{
    SOCKADDR_BTH sockaddrBthClient = { 0 };
    int clientAddrSize = sizeof(sockaddrBthClient);
    SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&sockaddrBthClient), &clientAddrSize);

    return clientSocket;
}

int main() {
    setlocale(LC_ALL, "Russian");

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error of init Winsock!" << std::endl;
        return -1;
    }

    SOCKET serverSocket = initServerSocket();
    if (serverSocket == INVALID_SOCKET) {
        return -1;
    }

    listen(serverSocket, SOMAXCONN);
    std::wcout << L"Сервер готов к работе" << std::endl;

    while (true) {
        SOCKET clientSocket = initClientSocket(serverSocket);
        if (clientSocket == INVALID_SOCKET) {
            continue;
        }

        while (true) {
            int result = getFile(clientSocket);
            if (result == -1) {
                std::cerr << "Ошибка приёма файла или разрыв соединения" << std::endl;
                break;
            }
        }
        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}