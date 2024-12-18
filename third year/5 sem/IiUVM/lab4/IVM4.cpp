#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <windows.h>
#pragma comment(lib,"vfw32.lib")
#pragma comment(lib, "setupapi.lib")
#include <iostream>
#include <locale.h>
#include <fstream>
#include <conio.h>
#include <vfw.h>
#include <string>
#include <conio.h>
#include <Setupapi.h>
#include <devguid.h>

void camInfo()
{
    HDEVINFO devInfo = SetupDiGetClassDevsA(&GUID_DEVCLASS_CAMERA, "USB", NULL, DIGCF_PRESENT);

    if (devInfo == INVALID_HANDLE_VALUE) return;

    SP_DEVINFO_DATA devInfoData;
    TCHAR buffer[1024];
    char instanceIDBuffer[1024];

    for (int i = 0; ; i++)
    {
        devInfoData.cbSize = sizeof(devInfoData);
        if (SetupDiEnumDeviceInfo(devInfo, i, &devInfoData) == FALSE) break;

        memset(buffer, 0, sizeof(buffer));
        SetupDiGetDeviceRegistryProperty(devInfo, &devInfoData, SPDRP_DEVICEDESC, NULL, (BYTE*)buffer, 1024, NULL);
        std::wstring name(buffer);

        memset(buffer, 0, sizeof(buffer));
        SetupDiGetDeviceRegistryProperty(devInfo, &devInfoData, SPDRP_HARDWAREID, NULL, (BYTE*)buffer, 1024, NULL);
        std::wstring ids(buffer);

        memset(buffer, 0, sizeof(buffer));
        SetupDiGetDeviceInstanceIdA(devInfo, &devInfoData, (PSTR)instanceIDBuffer, 1024, NULL);
        std::string instanceID(instanceIDBuffer);

        std::wstring ven(ids.substr(ids.find(L"VID_") + 4, 4));
        std::wstring dev(ids.substr(ids.find(L"PID_") + 4, 4));

        if (name.substr(name.size() - 4, 4) == dev) name = name.substr(0, name.size() - 7);

        std::wcout << L"Name: " << name << std::endl;
        std::wcout << L"Vendor ID: " << ven << std::endl;
        std::wcout << L"Device ID: " << dev << std::endl;
        std::cout << "Instance ID: " << instanceID << std::endl;

        SetupDiDeleteDeviceInfo(devInfo, &devInfoData);
    }
    SetupDiDestroyDeviceInfoList(devInfo);
}

int main() {

    ShowWindow(GetConsoleWindow(), SW_SHOW);

    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cout << "Error opening video stream" << std::endl;
        return -1;
    }

    int frame_width = camera.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = camera.get(cv::CAP_PROP_FRAME_HEIGHT);
    cv::VideoWriter video("video.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(frame_width, frame_height), true);
    if (!video.isOpened()) {
        std::cout << "Video creation error" << std::endl;
        return -1;
    }

    std::cout << "Camera:" << std::endl;
    camInfo();

    cv::Mat frame;

    int s;
    bool h = true;
    while (s = _getch())
    {
        switch (s) {
        case 'h':
        case 'H':
            h == true ? ShowWindow(GetConsoleWindow(), SW_HIDE) : ShowWindow(GetConsoleWindow(), SW_SHOW);
            h = !h;
            break;

        case 'p':
        case 'P':
            camera >> frame;
            cv::imwrite("photo.jpg", frame);
            std::cout << "Photo was saved to file photo.jpg" << std::endl;
            break;

        case 'v':
        case 'V':
            

            while (true) {
                if (_kbhit()) if (_getch() == 'v') break;
                try {
                    camera >> frame;
                    video.write(frame);
                }
                catch (std::exception ex)
                {
                    std::cout << ex.what() << std::endl;
                }
            }
            std::cout << "Video recording ended. Video saved to video.avi" << std::endl;

            break;

        case 'e':
        case 'E':
            camera.release();
            video.release();
            cv::destroyAllWindows();
            return 0;
        }
    }

    return 0;
}