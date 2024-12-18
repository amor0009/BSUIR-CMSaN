#include <iostream>
#include <iomanip>

#define ARRAY_SIZE 10

int main() {
    double array_start[ARRAY_SIZE]{ };
    std::cout << "Enter the values of array with length(" << ARRAY_SIZE << "): ";
    for (auto&& iter : array_start)
        std::cin >> iter;
    for (auto&& iter : array_start)
        std::cout << iter << std::setw(10);
    _asm { 
        finit
        xor esi, esi
        xor edi, edi
        mov ebx, ARRAY_SIZE

        fld array_start[esi]        // Загрузить первый элемент массива в регистр ST(0)
        fsin                        // Вычислить синус
        fstp array_start[esi]       // Сохранить результат обратно в массив

                                    // Повторить для остальных элементов
        mov ecx, ARRAY_SIZE - 1     // Загрузить количество элементов
        mov esi, 8                  // Загрузить размер элемента(double - 8 байт)
        add edi, esi                // Указатель на следующий элемент массива

    loop_start :
        fld array_start[edi]        // Загрузить следующий элемент массива
        fsin                        // Вычислить синус
        fstp array_start[edi]       // Сохранить результат обратно в массив

        add edi, esi                // Перейти к следующему элементу
        loop loop_start             // Повторить для остальных элементов

    mov eax, 0 
    fwait
    }

    std::cout << std::endl << std::endl << std::left; 
    for (double& iter : array_start) {
        std::cout << iter << std::setw(10);
    }
    return 0;
}