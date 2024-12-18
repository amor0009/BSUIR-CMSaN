#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int n_rows()                                                                // функция для ввода кол-ва строк матрицы(n)
{
    int n;
    printf_s("Enter the number of rows (n): ");
    while (scanf_s(" %d", &n) != 1 || n < 2)                                // цикл с предусловием для проверки введёного значения n
    {
        rewind(stdin);                                                      // очистка буфера ввода
        printf_s("You have entered the wrong data, try again please: ");
    }
    return n;
}

int m_columns()                                                             // функция для ввода кол-ва стобцов матрицы(m)
{
    int m;
    printf_s("Enter the number of columns (m): ");
    while (scanf_s(" %d", &m) != 1 || m < 2)                                // цикл с предусловием для проверки введёного значения n
    {
        rewind(stdin);                                                      // очистка буфера
        printf_s("You have entered the wrong data, try again please: ");
    }
    return m;
}

int** memory(int n, int m)                                                  // функция для выделения динамической памяти
{
    int** mas;
    mas = (int**)calloc(n, sizeof(int*));                                   // выделение динмаической памяти
    if (!mas)
        printf_s("Memory error!\n");                                        // проверка на выделение памяти

    for (int i = 0; i < n; i++)
    {
        *(mas + i) = (int*)calloc(m, sizeof(int));                          // *(mas + i) / mas[i]   выделение места под каждую строчку
        if (!*(mas + i))
            printf_s("Memory error!\n");                                    // проверка на выделение памяти
    }
    return mas;
}

void input_row_random(int* mas, int n)                                      // функция для ввода рандомных элементов строке матрицы
{
    for (int i = 0; i < n; i++)
        *(mas + i) = -50 + rand() % (50 + 50 + 1);                          // присваивание рандомных значений элементам матрицы
}

void input_row(int* mas, int n)                                             // функция для ввода элементов строки матрицы( с клавиатуры/ вручную)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d. ", i + 1);
        while (scanf_s("%d", (mas + i)) != 1)                               // проверка введённых элементов матрицы
        {
            rewind(stdin);
            printf_s("\nYou have entered the wrong data, try again please: \n");
            printf("%d. ", i + 1);
        }
    }
    printf("\n");
}

void input_matr_random(int** matr, int n, int m)                            // функция для ввода рандомных элементов матрицы
{
    int i;
    for (i = 0; i < n; i++)
        input_row_random(*(matr + i), m);
}

void input_matr(int** matr, int n, int m)                                   // функция для ввода элементов матрицы ( с клавиатуры/ вручную)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("\nRow %d:\n", i + 1);
        input_row(*(matr + i), m);
    }
}

void print_row(int* mas, int n)                                             // функция для вывода элементов строки матрицы, введённых вручную
{
    for (int i = 0; i < n; i++)
        printf("%6d", *(mas + i));                                          // m[i]
    printf("\n");
}


void print_matr(int** matr, int n, int m)                                   // функция для вывода элементов матрицы( как для введённых вручную, так и для рандомных)
{
    printf("\nArray:\n");
    for (int i = 0; i < n; i++)
        print_row(*(matr + i), m);

}

int modul(int a)                                                            // функция модуля числа 
{
    if (a >= 0)
        a = a;
    else
        a = (-1) * a;
    
    return a;
}

int del_i_max_row(int** mas, int* row, int column, int i_max)               // функция для удаления строки матрицы, на которой находился наибольший элемент массива
{
    for (int i = i_max; i < (*row) - 1; i++)
        for (int j = 0; j < column; j++)
            mas[i][j] = mas[i + 1][j];                                      // сдвиг элементов матрицы вверх 

    (*row)--;
    mas = (int**)realloc(mas, (*row) * sizeof(int*));                       // изменение кол-ва строк (размера матрицы)
    if (!mas)
        printf_s("Memory error!\n");                                        // проверка на выделение памяти

    return (*row);
}

int del_j_max_column(int** mas, int row, int* column, int j_max)            // функция для удаления столбца матрицы, на котором находился наибольший элемент массива 
{
    for (int i = 0; i < row; i++)
        for (int j = j_max; j < (*column) - 1; j++)
            mas[i][j] = mas[i][j + 1];                                      // сдвиг элементов матрицы влево

    (*column)--;
    for (int i = 0; i < row; i++)
    {
        *(mas + i) = (int*)realloc(*(mas + i), (*column) * sizeof(int));    // изменение кол-ва столбцов (размера матрицы)
        if (!*(mas + i))
            printf_s("Memory error!\n");                                    // проверка на выделение памяти
    }
   
    return *column;
}


int** changed_matr(int** mas, int* row, int* column)                        // функция для поиска наибольшего элемента массива и его индексов (+ сдвиги)
{
    int max = mas[0][0];
    int i_max;
    int j_max;

    for( int i = 0; i < (*row); i++)                                        // 2 цикла с параметром для работы с матрицей
        for (int j = 0; j < (*column); j++)
        {
            max = modul(max);                                               // присваиваем max значения модуля max 

            if (max < modul(mas[i][j]))                                     // условный оператор if для поиска наибольшего элемента матрицы и его индексов
            {
                max = mas[i][j];
                i_max = i;
                j_max = j;
            }
        }
    printf("\n\nModul of the max element: %d\n", modul(max));
    printf("\nIndex of the row of the max element: %d\n", i_max);
    printf("\nIndex of the column of the max element: %d\n", j_max);

    *row = del_i_max_row(mas, row, *column, i_max);                         // присваивание переменной изменённого кол-ва строк (сдвиг строк вверх) + вызов функции для удаления строки массива
    *column = del_j_max_column(mas, *row, column, j_max);                   // присваивание переменной изменённого кол-ва столбцов (сдвиг столбцов влево) + вызов функции для удаления столбца массива
    
    return mas;
}


void choice_option1(int** mas, int n, int m)                                // функция для выбора варианта ввода элементов массива 
{
    int opt1;
    printf("\n0. Enter element by yourself");
    printf("\n1. Enter random elements");
    printf("\nYour choice is: ");

    while ((scanf_s(" %d", &opt1) != 1) || ((opt1 < 0) || (opt1 > 1)))      // цикл с предусловием для проверки введённого значения переменной cho (выбора лействия)
    {
        rewind(stdin);
        printf("\nYou have entered the wrong data,\nyou should to enter 0 or 1 to choice the option, try again please: ");
    }

    if (opt1 == 0)                                                          // выбор варианта ввода
        input_matr(mas, n, m);
    else
        input_matr_random(mas, n, m);
}

int choice_option2()                                                        // функция для выбора действия над прогрмммой
{
    int opt2;                                                               // объявление переменной для выбора действия 
    printf("\n0. Try again");
    printf("\n1. Finish the programm");
    printf("\nYour choice is: ");

    while ((scanf_s(" %d", &opt2) != 1) || ((opt2 < 0) || (opt2 > 1)))      // цикл с предусловием для проверки введённого значения переменной cho (выбора лействия)
    {
        rewind(stdin);
        printf("\nYou have entered the wrong data,\nyou should to enter 0 or 1 to choice the option, try again please: ");
    }

    printf("\nThank you for your choice!\n");

    if (opt2 == 1)                                                          // условный оператор if для вывода сообщения при конце программы
        printf("\nThank you for using my program!\nGood luck :)");

    printf("\n");
    return opt2;
}

void free_mas(int** mas)                                                    // функция для очистки выделеннной памяти
{
    free(mas);
}