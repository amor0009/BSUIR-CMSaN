#include "functions.h"


static void printBatteryType() {
	
	HDEVINFO DeviceInfoSet;
	DeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_BATTERY, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	// интерфейс устройства в наборе сведений об устройстве
	SP_DEVICE_INTERFACE_DATA DeviceInterfaceData = { 0 };
	ZeroMemory(&DeviceInterfaceData, sizeof(SP_DEVINFO_DATA));
	DeviceInterfaceData.cbSize = sizeof(SP_DEVINFO_DATA);			

	// элемент информации о устройстве в наборе информации об устройстве(набор инфы об устройстве, индекс элемента, идентификатор батареи, интерфейс устройства)
	SetupDiEnumDeviceInterfaces(DeviceInfoSet, NULL, &GUID_DEVCLASS_BATTERY, 0, &DeviceInterfaceData);
	DWORD cbRequired = 0;										


	SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, NULL, NULL, &cbRequired, NULL);

	
	PSP_DEVICE_INTERFACE_DETAIL_DATA pdidd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, cbRequired);
	pdidd->cbSize = sizeof(*pdidd);								

	
	SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, pdidd, cbRequired, &cbRequired, NULL);

	
	HANDLE batteryFile = CreateFile(pdidd->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// структура с информацией о запросе батареи
	BATTERY_QUERY_INFORMATION BatteryQueryInformation = { 0 };
	DWORD bytesWait = 0;											
	DWORD bytesReturned = 0;										

	// команда файлу устройства извлечь текущую метку батареи
	DeviceIoControl(batteryFile, IOCTL_BATTERY_QUERY_TAG, &bytesWait, sizeof(bytesWait), &BatteryQueryInformation.BatteryTag,
		sizeof(BatteryQueryInformation.BatteryTag), &bytesReturned, NULL) && BatteryQueryInformation.BatteryTag;


	BATTERY_INFORMATION BatteryInfo = { 0 };
	BatteryQueryInformation.InformationLevel = BatteryInformation;

	// команда файлу устройства извлечь информацию об аккумуляторе
	DeviceIoControl(batteryFile, IOCTL_BATTERY_QUERY_INFORMATION, &BatteryQueryInformation, sizeof(BatteryQueryInformation),
		&BatteryInfo, sizeof(BatteryInfo), &bytesReturned, NULL);


	std::cout << "Тип батареи:";
	for (int i = 0; i < 4; i++) {
		std::cout << BatteryInfo.Chemistry[i];
	};
	std::cout << std::endl;

	
	LocalFree(pdidd);
	SetupDiDestroyDeviceInfoList(DeviceInfoSet);
}


void PrintPowerStatus(const SYSTEM_POWER_STATUS& status) {
	std::cout << "Тип/источник питания: ";
	if (status.ACLineStatus == 0)
		std::cout << "батарея.\n";
	else if (status.ACLineStatus == 1)
		std::cout << "сетевое питание.\n";
	else
		std::cout << "неизвестный. :(\n";

	std::cout << "Уровень заряда батареи: " << (int)status.BatteryLifePercent << "%.\n";

	printBatteryType();
		
    std::cout << "Оставшееся время работы батареи: ";
    if (status.ACLineStatus == 1)
        std::cout << "неизвестно, сетевое питание.\n";
    else
        std::cout << status.BatteryLifeTime / 3600 << "ч. " << (status.BatteryLifeTime / 60) % 60 << "м. " << (status.BatteryLifeTime % 60) << "c.\n";

	std::cout << "Время работы батареи без подключения к зарядке: ";
	if (status.ACLineStatus == 1)
		std::cout << "неизвестно, сетевое питание.\n";
	else {
		int fullTime = (status.BatteryLifeTime * 100) / status.BatteryLifePercent;
		std::cout << fullTime / 3600 << "ч. " << (fullTime / 60) % 60 << "м. " << (fullTime % 60) << "c.\n";
	}

    std::cout << "Текущий режим энергосбережения: ";
    if (status.SystemStatusFlag == 0)
        std::cout << "Нормальный режим\n";
    else
        std::cout << "Экономия энергии\n";
}


void sleepMode() {
    if (!SetSuspendState(FALSE, FALSE, FALSE)) 
        std::cerr << "Не удалось перевести систему в спящий режим.\n";
}

void hibernateMode() {
    if (!SetSuspendState(TRUE, FALSE, FALSE)) 
        std::cerr << "Не удалось перевести систему в гибернацию.\n";
}