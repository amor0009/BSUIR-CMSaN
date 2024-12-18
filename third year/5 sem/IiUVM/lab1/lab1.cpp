#include "functions.h"
#include <locale.h>


int main() {
    setlocale(LC_ALL, "Russian");
    SYSTEM_POWER_STATUS powerStatus;

    while (true) {
        if (GetSystemPowerStatus(&powerStatus)) {
            system("cls");
            PrintPowerStatus(powerStatus);
        }
        else {
            std::cerr << "Не удалось получить информацию об энергопитании.\n";
        }
        std::cout << "\nКоманды:\n1 - Перевести в спящий режим\n2 - Перевести в гибернацию\n3 - Обновить информацию\n0 - Выйти\n";
        int command;
        std::cin >> command;

        switch (command) {
        case 1:
            sleepMode();
            continue;
        case 2:
            hibernateMode();
            continue;
        case 3:
            continue;
        case 0:
            return 0;
        default:
            std::cout << "Неизвестная команда!\n";
        }
    }

    return 0;
}