#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int referees()                                      // функция для ввода количества судей( оценок)
{
    int n;
    printf_s("\nEnter the numer of the referees (no less than 3): ");
    
    while (scanf_s("%d", &n) != 1 || (n < 3))       // цикл с предусловием для проверки введённого значения n (кол-во судей\ оценок)  
    {
            rewind(stdin);                          // очистка буфера ввода
            printf_s("\nYou have entered the wrong data type,\nyou should eneter the number of the referees,\ntry again please: ");
    }
    return n;
}

int* a_memory(int* a, int n)                        // функция выделения динамической памяти
{
    a = (int*)malloc(n * sizeof(int));              // выделение динамической памяти
    if (!a)                                         // проверка на выделение памяти
        printf_s("Memory error!\n");                

    return a;
}

void a_input(int* a, int n)                         // функция для ввода массива
{
    printf_s("\nThe marks of the sportsman:\n");
    for (int i = 0; i < n; i++)                     // цикл с параметром для ввода элементов массива
    {
        printf_s("%d. ", i + 1);
        while (scanf_s("%d", a + i) != 1 || (*(a + i) > 10 || *(a + i) < 0))           //цикл с предусловием для проверки введённых элементов массива (ввод до тех пор, пока не введён правильный тип)
        {
            rewind(stdin);                          //очистка буффера ввода (без него, при вводе char'ов зациклится)
            printf_s("\nYou have entered the wrong data type,\nyou should eneter the number of the referees,\ntry again please:\n\n");
            printf_s("%d. ", i + 1);
        }

    }
}

void a_output(int* a, int n)                        // функция для вывода элементов массива
{
    printf_s("\n\nAll marks:\n");
    for (int i = 0; i < n; i++)
        printf_s("%d mark: %d\n", i + 1, *(a + i));
}

int* a_change(int* a, int n)                         // функция для изменения массива по заданному условию задачи
{
    int min, max;                                   // max - для максимального элемента, min - для минимального
    int i_min, i_max;                               // i_max - для индекса макс эл-та, i_min - для индекса мин эл-та
    min = *a;                                       // примем первый элемент массива за минимальный (для сравнения)
    
    for (int i = 0; i < n; i++)                     // цикл с параметром для нахождения минимального элемента и его индекса
    {
        if (*(a + i) < min)                         // для сравнение эл-ов массива и для поиска минимального эл-та
        {
            min = *(a + i);
            i_min = i;
        }
    }

    for (int i = i_min; i < n - 1; i++)             // удаление минимального элемента массива (сдвиг элементов массива влево относительно минимального элемента)
        *(a + i) = *(a + i + 1);

    a = (int*)realloc(a, (--n * sizeof(int)));      // уменьшение выделенной памяти 

    if (!a)
        printf_s("Memory error!\n");                

    max = *a;                                       // примем первый элемент массива за максимальный (для сравнения)
 
    for (int i = 0; i < n; i++)                     // цикл с параметром для нахождения максимального элемента и его индекса
    {
        if (*(a + i) > max)                         // для сравнения эл-тов и поиска максимального эл-та
        {
            max = *(a + i);
            i_max = i;
        }
    }

    for (int i = i_max; i < n - 1; i++)             // удаление максимального элемента массива(сдвиг элементов массива влево относительно максимального элемента)
        *(a + i) = *(a + i + 1);

    a = (int*)realloc(a, (--n * sizeof(int)));      // уменьшение выделенной памяти

    if (!a)
        printf_s("Memory error!\n");                // проверка на выделение памяти

    //printf_s("\n\nSorted marks:\n");
    //for (int i = 0; i < n; i++)                     // цикл с параметром для вывода изменённого массива
    //    printf_s("%d mark: %d\n", i + 1, *(a + i));

    return a;
}

void a_average(int* a, int n)                       // функция для вычисления среденей оценки и её вывода
{
 
    float sum = 0.0;
    float average = 0.0;
    printf_s("\n\n");
    for (int i = 0; i < n; i++)                     
        sum = sum + (float)a[i];                    // счёт суммы элементов массива

    average = sum / (float)n;                       // счёт среднего арифметического 
    printf("Average mark = %.2f", average);
}
int check(void)                                     // функция для выбора действия над программой
{
    int cho;

    printf("\n\n0. Try again!\n");
    printf("1. Finish the program!\n");
    printf("Your choice is: ");
    
		
    while ((scanf_s(" %d", &cho) != 1) || ((cho < 0) || (cho > 1)))   // цикл с предусловием для проверки введённого значения переменной cho (выбора лействия)
    {
        rewind(stdin);
        printf("\nYou have entered the wrong data,\nyou should to enter 0 or 1 to choice the option, try again please: ");
    }

    printf("\nThank you for your choice\n");

    if (cho == 1)                                                     // условный оператор if для вывода сообщения
        printf("\nThank you for using my programm!\nGood luck :)\n");

    return cho;
}
int a_changed_output(int* mas, int n)               // функция для вывода изменённого массив оценок
{
    n = n - 2;                                      // уменьшаем кол-во оценок на 2
    printf_s("\n\nSorted marks:\n");
    for (int i = 0; i < n; i++)                     // цикл с параметром для вывода изменённого массива
        printf_s("%d mark: %d\n", i + 1, *(mas + i));

    return n;
}