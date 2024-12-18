#include <iostream>
#include <Windows.h>
#include <powrprof.h>
#include <conio.h>

#include <winbase.h>
#include <winioctl.h>
#include <batclass.h>

#include <Poclass.h>
#include <Setupapi.h>
#include <devguid.h>

#pragma comment(lib, "powrprof.lib")
#pragma comment(lib, "setupapi.lib")

static void printBatteryType();
void PrintPowerStatus(const SYSTEM_POWER_STATUS& status);
void sleepMode();
void hibernateMode();