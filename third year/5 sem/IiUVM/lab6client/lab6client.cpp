#include <iostream>
#include <fstream>
#include <vector>
#include <Winsock2.h>
#include <Ws2bth.h>
#include <BluetoothAPIs.h>
#include <conio.h>
#include <map>
#include <set>
#include <mutex>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <cstdlib>
#include <thread>
#include <atomic>

std::vector<BLUETOOTH_DEVICE_INFO> devices;
std::vector<BLUETOOTH_DEVICE_INFO> newDevices;
std::vector<std::pair<std::string, std::string>> files;
std::set<std::string> audioExtensions = { ".mp3",".wav", ".ogg", ".flac", ".aac", ".m4a" };
SOCKET clientSocket;
std::mutex deviceMutex;
std::atomic<bool> flagContinue = true;

bool findFiles(const std::string& path) {

    if (std::filesystem::exists(path)) {
        files.clear();
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            std::string extension = entry.path().extension().string();
            if (audioExtensions.count(extension)) {
                files.emplace_back(entry.path().filename().string(), entry.path().string());
            }
        }
    }
    else {
        return false;
    }
    return true;
}

void displayFiles() {
    for (int i = 0; i < files.size(); i++) {
        std::cout << i + 1 << ". " << files[i].first << " -> " << files[i].second << std::endl;
    }
}

void findBluetoothDevices(std::vector<BLUETOOTH_DEVICE_INFO>& vec) {
    vec.clear();
    BLUETOOTH_DEVICE_SEARCH_PARAMS filter = {
            sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS)
    };

    filter.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
    filter.fReturnAuthenticated = true;
    filter.fReturnConnected = true;
    filter.fReturnRemembered = false;
    filter.fReturnUnknown = false;
    filter.cTimeoutMultiplier = 8;

    BLUETOOTH_DEVICE_INFO devInfo = { sizeof(BLUETOOTH_DEVICE_INFO), 0 };

    HBLUETOOTH_DEVICE_FIND hFind = BluetoothFindFirstDevice(&filter, &devInfo);
    if (hFind != nullptr) {
        do {
            vec.push_back(devInfo);
        } while (BluetoothFindNextDevice(hFind, &devInfo));
    }

    BluetoothFindDeviceClose(hFind);
}

void displayDevs() {
    for (int i = 0; i < devices.size(); i++) {
        std::wcout << i + 1 << ". ";
        printf("%ls", devices[i].szName);
        std::cout << " - " << devices[i].Address.ullLong << std::endl;

        std::wcout.flush();
    }
}

void sendFile(const std::string& filePath) {
    std::ifstream fileToSend(filePath, std::ios::binary);

    auto begin = fileToSend.tellg();

    fileToSend.seekg(0, std::ios::end);

    auto end = fileToSend.tellg();

    auto fsize = end - begin;

    char fSizeStr[100];
    _itoa_s(fsize, fSizeStr, 10);

    send(clientSocket, fSizeStr, 100, 0);

    fsize = 0;
    fileToSend.seekg(0);

    char buffer[1024];
    while (!fileToSend.eof()) {
        fileToSend.read(buffer, sizeof(buffer));
        int bytes = send(clientSocket, buffer, sizeof(buffer), 0);
        if (bytes == -1) {
            std::cerr << "Error: failed writing to socket!";
            return;
        }
    }

    fileToSend.close();
}

void client(const BLUETOOTH_DEVICE_INFO& devInfo) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error: failed to initialize socket!" << std::endl;
        exit(1);
    }

    BTH_ADDR addr = devInfo.Address.ullLong;

    SOCKADDR_BTH sockAddrBthServer = { 0 };
    sockAddrBthServer.addressFamily = AF_BTH;
    sockAddrBthServer.serviceClassId = RFCOMM_PROTOCOL_UUID;
    sockAddrBthServer.port = 6;
    sockAddrBthServer.btAddr = addr;

    clientSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error: failed creating client socket!" << std::endl;
        WSACleanup();
        exit(1);
    }

    if (connect(clientSocket,
        reinterpret_cast<sockaddr*>(&sockAddrBthServer),
        sizeof(sockAddrBthServer)
    ) == SOCKET_ERROR
        ) {
        std::cerr << "Error: failed connecting to the server!" << std::endl;
        system("pause");
        closesocket(clientSocket);
        WSACleanup();
        exit(1);
    }

    std::cout << "Successfully connected to server" << std::endl;
}

void close() {
    closesocket(clientSocket);
    WSACleanup();
}

void displayAll() {
    while (flagContinue) {
        deviceMutex.lock();
        findBluetoothDevices(newDevices);
        if (newDevices.size() != devices.size()) {
            system("cls");
            devices = newDevices;
            displayDevs();
        }
        deviceMutex.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main() {
    findBluetoothDevices(devices);

    std::thread monitorThread(displayAll);


    while (flagContinue) {

        bool flagContinueChoose = false;
        bool flagContinueFileFind = false;

        displayDevs();


        int choice = 1;
        std::cin >> choice;

        if (choice == 0) {
            flagContinue = false;
        }

        if (choice < 1 || choice > devices.size()) {
            system("cls");
            continue;
        }

        deviceMutex.lock();

        flagContinueFileFind = true;

        system("cls");

        auto dev = devices.at(choice - 1);


        while (flagContinueFileFind) {
            system("cls");
            std::cout << "1. Write the path of directory, where is your audiofile: " << std::endl;
            std::cout << "2. Exit to the main menu" << std::endl;

            char ch;

            std::cin >> ch;

            switch (ch) {
            case '1': {
                std::cout << "Write the path of directory, where is your audiofile: ";
                std::string path;
                std::cin >> path;
                auto exists = findFiles(path);
                if (!exists) {
                    std::cout << "Error: cannot find path to directory!" << std::endl;
                    system("pause");
                    continue;
                }

                if (files.empty()) {
                    std::cout << "Error: cannot find audiofiles" << std::endl;
                    system("pause");
                    continue;
                }

                flagContinueFileFind = false;
                flagContinueChoose = true;
                system("cls");
                break;
            }
            case '2': {
                system("cls");
                flagContinueFileFind = false;
                break;
            }
            default: {
                break;
            }
            }
        }

        if (flagContinueChoose) {
            client(dev);
        }

        while (flagContinueChoose) {
            displayFiles();
            std::cout << "Choose the number of audiofile you would like to send (0 to exit): ";

            std::cin >> choice;

            if (choice == 0) {
                close();
                flagContinueChoose = false;
            }

            if (choice < 1 || choice > devices.size()) {
                system("cls");
                continue;
            }

            std::string filePath = files.at(choice - 1).second;

            sendFile(filePath);
        }

        deviceMutex.unlock();
    }

    if (monitorThread.joinable()) {
        monitorThread.join();
    }

    return 0;
}