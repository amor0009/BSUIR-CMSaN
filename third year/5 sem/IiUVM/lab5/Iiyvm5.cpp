#include <windows.h>
#include <dbt.h>
#include <iostream>
#include <initguid.h>
#include <Usbiodef.h>
#include <SetupAPI.h>
#include <vector>
#include <Cfgmgr32.h>
#include <conio.h>
#include <string>

#pragma comment (lib, "user32.lib" )
#pragma comment (lib, "Setupapi.lib")

using namespace std;

#define CLS_NAME "WindowClass"

struct USB
{
	DEVINST devInst;
	string friendlyName;
	wstring name;
	HANDLE handle;
	bool safety;
	bool removable;
};

vector<USB> deviceArray;

bool StringComparator(wstring s1, wstring s2)
{
	if (s1.size() != s2.size())
		return false;
	for (int i = 0; i < s1.size(); i++)
		if (toupper(s1[i]) != toupper(s2[i]))
			return false;
	return true;
}

string handleToFriendlyName(HANDLE handle)
{
	for (auto it : deviceArray)
		if (it.handle == handle)
			return it.friendlyName;
}

bool GetSafety(wstring name)
{
	for (auto it : deviceArray)
		if (StringComparator(it.name, name))
			return it.safety;
	return false;
}

void SetSafety(HANDLE handle, bool safety)
{
	for (int i = 0; i < deviceArray.size(); i++)
		if (deviceArray[i].handle == handle)
			deviceArray[i].safety = safety;
}

void deleteByName(wstring name)
{
	for (int i = 0; i < deviceArray.size(); i++)
		if (StringComparator(deviceArray[i].name, name))
		{
			deviceArray.erase(deviceArray.begin() + i);
			return;
		}
}


string getFriendlyName(wchar_t* name)
{
	HDEVINFO deviceList = SetupDiCreateDeviceInfoList(NULL, NULL);
	SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
	SetupDiOpenDeviceInterfaceW(deviceList, name, NULL, &deviceInterfaceData);
	SP_DEVINFO_DATA deviceInfo;
	ZeroMemory(&deviceInfo, sizeof(SP_DEVINFO_DATA));
	deviceInfo.cbSize = sizeof(SP_DEVINFO_DATA);
	SetupDiEnumDeviceInfo(deviceList, 0, &deviceInfo);
	DWORD size = 0;
	SetupDiGetDeviceRegistryPropertyA(deviceList, &deviceInfo, SPDRP_DEVICEDESC, NULL, NULL, NULL, &size);
	BYTE* buffer = new BYTE[size];
	SetupDiGetDeviceRegistryPropertyA(deviceList, &deviceInfo, SPDRP_DEVICEDESC, NULL, buffer, size, NULL);
	string deviceDesc = (char*)buffer;
	delete[] buffer;

	return deviceDesc;
}

bool getRemoveability(wchar_t* name)
{
	HDEVINFO deviceList = SetupDiCreateDeviceInfoList(NULL, NULL);
	SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
	SetupDiOpenDeviceInterfaceW(deviceList, name, NULL, &deviceInterfaceData);
	SP_DEVINFO_DATA deviceInfo;
	ZeroMemory(&deviceInfo, sizeof(SP_DEVINFO_DATA));
	deviceInfo.cbSize = sizeof(SP_DEVINFO_DATA);
	SetupDiEnumDeviceInfo(deviceList, 0, &deviceInfo);
	DWORD properties;
	SetupDiGetDeviceRegistryPropertyA(deviceList, &deviceInfo, SPDRP_CAPABILITIES, NULL, (PBYTE)&properties, sizeof(DWORD), NULL);
	return properties & CM_DEVCAP_REMOVABLE;
}

string getFriendlyName(PDEV_BROADCAST_DEVICEINTERFACE_A info)
{
	wchar_t* name = (wchar_t*)info->dbcc_name;
	return getFriendlyName(name);
}

string getInstId(const wchar_t* name)
{
	HDEVINFO deviceList = SetupDiCreateDeviceInfoList(NULL, NULL);
	SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
	SetupDiOpenDeviceInterfaceW(deviceList, name, NULL, &deviceInterfaceData);
	SP_DEVINFO_DATA deviceInfo;
	ZeroMemory(&deviceInfo, sizeof(SP_DEVINFO_DATA));
	deviceInfo.cbSize = sizeof(SP_DEVINFO_DATA);
	SetupDiEnumDeviceInfo(deviceList, 0, &deviceInfo);
	BYTE buffer[BUFSIZ];
	SetupDiGetDeviceInstanceIdA(deviceList, &deviceInfo, (PSTR)buffer, BUFSIZ, NULL);
	return (char*)buffer;
}

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	bool result = false;
	if (message == WM_DEVICECHANGE)
	{
		if (wParam == DBT_DEVICEARRIVAL)
		{
			PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
			if (lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
			{
				PDEV_BROADCAST_DEVICEINTERFACE_A info = (PDEV_BROADCAST_DEVICEINTERFACE_A)lpdb;
				cout << "New device: \"" << getFriendlyName(info) << "\"" << endl;

				HANDLE deviceHandle = CreateFileW((wchar_t*)info->dbcc_name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				DEV_BROADCAST_HANDLE deviceFilter;
				deviceFilter.dbch_size = sizeof(deviceFilter);
				deviceFilter.dbch_devicetype = DBT_DEVTYP_HANDLE;
				deviceFilter.dbch_handle = deviceHandle;
				HDEVNOTIFY notifyHandle = RegisterDeviceNotificationW(hWnd, &deviceFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
				CloseHandle(deviceHandle);

				DEVINST devInst;
				CM_Locate_DevNodeA(&devInst, (DEVINSTID_A)getInstId((wchar_t*)info->dbcc_name).c_str(), CM_LOCATE_DEVNODE_NORMAL);

				USB tempDesc;
				tempDesc.devInst = devInst;
				tempDesc.handle = deviceHandle;
				tempDesc.name = (wchar_t*)info->dbcc_name;
				tempDesc.safety = false;
				tempDesc.friendlyName = getFriendlyName(info);
				tempDesc.removable = getRemoveability((wchar_t*)info->dbcc_name);
				deviceArray.push_back(tempDesc);
			}
		}
		if (wParam == DBT_DEVICEQUERYREMOVEFAILED)
		{
			PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
			if (lpdb->dbch_devicetype == DBT_DEVTYP_HANDLE)
			{
				PDEV_BROADCAST_HANDLE info = (PDEV_BROADCAST_HANDLE)lpdb;
				cout << "Remove device attempt failed \"" << handleToFriendlyName(info->dbch_handle) << "\"" << endl;
				SetSafety(info->dbch_handle, false);
			}
		}
		if (wParam == DBT_DEVICEREMOVECOMPLETE)
		{
			PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
			if (lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
			{
				PDEV_BROADCAST_DEVICEINTERFACE_A info = (PDEV_BROADCAST_DEVICEINTERFACE_A)lpdb;
				cout << "Device \"" << getFriendlyName(info) << "\" was removed "
					<< (GetSafety((wchar_t*)info->dbcc_name) ? "in safe mode!" : "not safe!") << '\n';

				deleteByName((wchar_t*)info->dbcc_name);
			}
			if (lpdb->dbch_devicetype == DBT_DEVTYP_HANDLE)
			{
				PDEV_BROADCAST_HANDLE info = (PDEV_BROADCAST_HANDLE)lpdb;
				UnregisterDeviceNotification(info->dbch_hdevnotify);
			}
		}
		if (wParam == DBT_DEVICEQUERYREMOVE)
		{
			PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
			//cout << "Device removed in safe mode" << endl;
			if (lpdb->dbch_devicetype == DBT_DEVTYP_HANDLE)
			{
				PDEV_BROADCAST_HANDLE info = (PDEV_BROADCAST_HANDLE)lpdb;
				SetSafety(info->dbch_handle, true);
			}
			else
			{
				return BROADCAST_QUERY_DENY;
			}
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter) {
	HWND hWnd = NULL;
	WNDCLASSEX wx;
	ZeroMemory(&wx, sizeof(wx));

	wx.cbSize = sizeof(WNDCLASSEX);
	wx.lpfnWndProc = (WNDPROC)(WndProc);
	wx.lpszClassName = (LPCWSTR)CLS_NAME;

	GUID guid = GUID_DEVINTERFACE_USB_DEVICE;

	if (RegisterClassExW(&wx))
		hWnd = CreateWindowW((LPCWSTR)CLS_NAME, (LPCWSTR)("DeviceNotificationWindow"), WS_ICONIC, 0, 0, CW_USEDEFAULT, 0, 0, NULL, GetModuleHandle(0), (void*)&guid);

	DEV_BROADCAST_DEVICEINTERFACE_A filter;
	filter.dbcc_size = sizeof(filter);
	filter.dbcc_classguid = guid;
	filter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	RegisterDeviceNotificationW(hWnd, &filter, DEVICE_NOTIFY_WINDOW_HANDLE);

	HDEVINFO devicesHandle = SetupDiGetClassDevsA(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	DWORD deviceNumber = 0;
	SP_DEVICE_INTERFACE_DATA devinterfaceData;
	devinterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	while (SetupDiEnumDeviceInterfaces(devicesHandle, NULL, &GUID_DEVINTERFACE_USB_DEVICE, deviceNumber++, &devinterfaceData)) {

		DWORD bufSize = 0;
		SetupDiGetDeviceInterfaceDetailW(devicesHandle, &devinterfaceData, NULL, NULL, &bufSize, NULL);
		BYTE* buffer = new BYTE[bufSize];
		PSP_DEVICE_INTERFACE_DETAIL_DATA_W devinterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)buffer;
		devinterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W);
		SetupDiGetDeviceInterfaceDetailW(devicesHandle, &devinterfaceData, devinterfaceDetailData, bufSize, NULL, NULL);

		wchar_t* path = devinterfaceDetailData->DevicePath;

		DEVINST devInst;
		CM_Locate_DevNodeA(&devInst, (DEVINSTID_A)getInstId(devinterfaceDetailData->DevicePath).c_str(), CM_LOCATE_DEVNODE_NORMAL);

		HANDLE deviceHandle = CreateFileW(path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		DEV_BROADCAST_HANDLE deviceFilter;
		deviceFilter.dbch_size = sizeof(deviceFilter);
		deviceFilter.dbch_devicetype = DBT_DEVTYP_HANDLE;
		deviceFilter.dbch_handle = deviceHandle;
		HDEVNOTIFY notifyHandle = RegisterDeviceNotificationW(hWnd, &deviceFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
		CloseHandle(deviceHandle);

		USB tmpUsbDev;
		tmpUsbDev.devInst = devInst;
		tmpUsbDev.friendlyName = getFriendlyName(path);
		tmpUsbDev.handle = deviceHandle;
		tmpUsbDev.name = path;
		tmpUsbDev.safety = false;
		tmpUsbDev.removable = getRemoveability(path);
		deviceArray.push_back(tmpUsbDev);
	}

	MSG msg;
	while (GetMessageW(&msg, hWnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

void printDeviceArray() {
	int id = 1;
	cout << endl << "Detected USB devices:" << endl;
	for (auto it : deviceArray)
		cout << id++ << " - " << it.friendlyName << (it.removable ? " (Removable)" : "") << endl;
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	CreateThread(NULL, NULL, ThreadProc, NULL, NULL, NULL);

	int choise = -1;
	while (true) {
		cout << "1 - Device list" << endl << "2 - Safe Remove" << endl << "0 - Exit" << endl;
		cin >> choise;
		if (choise == 1) {
			printDeviceArray();
		}
		else if (choise == 2) {
			printDeviceArray();
			cout << "Input num of device to remove: ";
			choise = 0;
			while (!(cin >> choise))
			{
				cin.clear();
				rewind(stdin);
			}
			if (choise > deviceArray.size() || choise <= 0)
			{
				cout << "Device with this number not exist" << choise << "!" << endl;
				continue;
			}
			if (deviceArray[choise - 1].removable)
				CM_Request_Device_EjectW(deviceArray[choise - 1].devInst, NULL, NULL, NULL, NULL);
			else
				cout << "Device with number " << choise << " remove error!" << endl;
		}
		else if (choise == 0) {
			return 0;
			::system("CLS");
		}
		rewind(stdin);
		_getch();
		::system("CLS");
	}
}