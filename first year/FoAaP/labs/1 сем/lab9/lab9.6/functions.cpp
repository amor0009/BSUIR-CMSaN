#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int number_of_rows()                                                        // ввод кол-ва строк 
{
    int n;
    printf_s("Enter the number rows: ");
    while (scanf_s(" %d", &n) != 1 || n <= 0)                               // цикл с предусловием для проверки введёного значения n
    {
        rewind(stdin);                                                      // очистка буфера ввода
        printf_s("\nYou have entered the wrong data, try again please: ");
    }
    return n;
}

int number_of_symbols()                                                     // функция для ввода кол-ва символов в i-ой строке
{
    int m;
    printf_s("Enter the number of symbols you want to enter: ");
    while (scanf_s(" %d", &m) != 1 || m < 0)                                // цикл с предусловием для проверки введёного значения n
    {
        rewind(stdin);                                                      // очистка буфера ввода
        printf_s("\nYou have entered the wrong data, try again please: ");
    }
    m = m + 1;                                                              // ввод введённого кол-ва символов и + нуль-символ

    return m;
}

char** memory(int n, int m)                                                 // выделене динамической памяти
{
    char** mas = (char**)calloc(n, sizeof(char*));                          // выделение динамической памяти под массив указателей
    if (!mas)                                                               // проверка на выделение динамической памяти
        printf("\nAttention!!! Memory ERROR!\n");
    for (int i = 0; i < n; i++)
    {
        *(mas + i) = (char*)calloc(m, sizeof(char));                        // выделение динамической памяти под каждую строку
        if (! *(mas + i))                                                   // проверка на выделение динамической памяти
            printf("Memory ERROR!!!");
    }
    return mas;
}

void row_input(char* mas, int m)                                            // ввод строки 
{
    int c = 0;
    int i = 0;
    printf("\nPlease, enter the text( no more than %d symbols): \n", m - 1);
    rewind(stdin);
    while (--m > 0 && (c = getchar()) != EOF && c != '\n')
        mas[i++] = c;

    mas[i] = '\0';
}

void row_fgets_input(char* mas, int m)                                      // ввод строки с помощь fgets
{
    rewind(stdin);
    fgets(mas, m, stdin);                                                   // ввод каждого символа
}

char** text_input(char** mas, int n, int m)                                 // ввод текста (всехs строк)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nRow %d:", i + 1);
        row_input(mas[i], m);
    }
    return mas;
}

char** text_fgets_input(char** mas, int n, int m)                           // ввод текста( всех строк) с помощью fgets
{
    for (int i = 0; i < n; i++)
    {
        printf("\nRow %d:\n", i + 1);
        row_fgets_input(mas[i], m);
    }
    return mas;
}

int str_len(char* mas)                                                      // длина i-й строки
{
    int i = 0;
    while (mas[i] != '\0')
        i++;
    i++;                                                                    // учитываем нуль-символ
    return i;
}

void row_output(char* mas, int m)                                           // вывод строки
{
    m = str_len(mas);
    for (int i = 0; i < m - 1; i++)
        printf_s("%c", mas[i]);
    printf("\n");
}

void row_fgets_output(char* mas, int n)                                     // вывод строки с помощью puts
{
    printf("\nRow: \n");
    puts(mas);
}

void text_output(char** mas, int n, int m)                                  // вывода всех строк
{
    printf("\nText:\n");
    for (int i = 0; i < n; i++)
        row_output(mas[i], m);
}

void text_puts_output(char** mas, int n, int m)                             // вывода всех строк с помощью puts
{
    for (int i = 0; i < n; i++)
        puts(mas[i]);
}

char* changed_text(char* mas, int n)                                        // изменение текста (строчныеи прописные буквы)
{

    for (int i = 0; i < n - 1; i++)                                         // изменение первой буквы первого слова на прописную 
    {
        if (mas[i] >= 65 && mas[i] <= 90)                                   // если она является прописной, то ничего не делаем
        {
            while (mas[i + 1] != ' ' && mas[i + 1] != '\t' && mas[i + 1] != '\0')   // изменение букв на строчные конца слова  
            {
                if (mas[i + 1] >= 65 && mas[i + 1] <= 90)
                    mas[i + 1] += 32;
                i++;
            }
            break;
        }

        if (mas[i] >= 97 && mas[i] <= 122)                                  // если она является строчной, то меняем её на прописную
        {
            mas[i] -= 32;
            while (mas[i + 1] != ' ' && mas[i + 1] != '\t' && mas[i + 1] != '\0')   // изменение букв на строчные конца слова  
            {
                if (mas[i + 1] >= 65 && mas[i + 1] <= 90)
                    mas[i + 1] += 32;
                i++;
            }
            break;
        }
    }

    for (int i = 0; i < n - 1; i++)                                         // изменения для следующих слов
        if (mas[i] == ' ')
            for (int k = i + 1; k < n; k++)
                if (mas[k] != ' ' && mas[k] <= '0' && mas[k] >= '9' && mas[k] != '\0')
                {
                    if (mas[k] >= 97 && mas[k] <= 122)
                        mas[k] -= 32;

                    while (mas[k + 1] != ' ' && mas[k + 1] != '\t')         // изменение букв на строчные конца слова  
                    {
                        if (mas[k + 1] >= 65 && mas[k + 1] <= 90)
                            mas[k + 1] += 32;
                        k++;
                    }

                    break;
                }
    return mas;
}

char** changed_text1(char** mas, int n, int m)                              // изменение всех строк текста (прописные и строчные буквы)
{
    for (int i = 0; i < n; i++)
        mas[i] = changed_text(mas[i], m);
    return mas;
}

int sum_salary(char* mas)                                                   // сумма всех зарплат 
{
    int n;
    int sum = 0;
    int m = str_len(mas);
    for (int j = 0; j < m - 1; j++)
    {
        n = 0;
        while (mas[j] >= '0' && mas[j] <= '9')
        {
            n = 10 * n + (mas[j] - '0');                                    // составление i-ой зарплаты
            j++;
        }
        sum = sum + n;                                                      // сумма всех зарплат
    }
    return sum;
}

char** changed_text2(char** mas, int n, int m)                              // сортировка строк текста по алфавиту
{
    char* temp;
    int noSwap = 0;

    for (int k = 0; k < n - 1; k++)                                         // цикл для повторения цикла i
        for (int i = 0; i < n - 1 - k; i++)                                 // цикл для прохождения по строкам mas
        {
            noSwap = 0;
            for (int j = 0; j < str_len(mas[i]) - 1; j++)                   // цикл для прохождения по символам строк mas
            {
                while (mas[i][j] == mas[i + 1][j])                          // доходим до неравных символов
                    j++;

                if (mas[i][j] - mas[i + 1][j] > 0)                          // сравниваем символы по алфавиту и меняем их местами
                {
                    temp = mas[i];
                    mas[i] = mas[i + 1];
                    mas[i + 1] = temp;
                    noSwap = 1;
                    break;
                }

                if (noSwap == 0)                                            // флажок для переходя на следующую строку 
                    break;
            }
        }
    return mas;
}

char** changed_text3(char** mas, int n, int m)                              // сортировка строк текста по возрастанию общей суммы з\п
{
    char* temp;
 
    int noSwap = 0;

     for (int i = 0; i < n - 1; i++)                                        // цикл для прохождения по строкам mas
     {
         for (int j = 0; j < n - i; j++)                                    // цикл для прохождения по символам строк mas
             if (sum_salary(mas[j]) > sum_salary(mas[j + 1]))               // сравниваем символы по алфавиту и меняем их местами
             {
                 temp = mas[j];
                 mas[j] = mas[j + 1];
                 mas[j + 1] = temp;
                 noSwap = 1;
                 break;
             }
         if (noSwap == 0)                                                   // 
             break;
     }
    return mas;
}

char** choice_option1_and_changing(char** mas, int n, int m)                // функция для выбора действия над программой
{
    int opt1;                                                               // объявление переменной для выбора действия 
    printf("\n\n0. Sort in alphabet order");
    printf("\n1. Sort in salary order");
    printf("\nYour choice is: ");

    while ((scanf_s(" %d", &opt1) != 1) || ((opt1 < 0) || (opt1 > 1)))      // цикл с предусловием для проверки введённого значения переменной cho (выбора лействия)
    {
        rewind(stdin);
        printf("\nYou have entered the wrong data,\nyou should to enter 0 or 1 to choice the option, try again please: ");
    }

    if (opt1 == 0)                                                          // выполнение сортировки по одному из условий
    {
        mas = changed_text2(mas, n, m);
    }
    else if (opt1 == 1)
    {
        mas = changed_text3(mas, n, m);
    }

    printf("\n");
    return mas;
}

int choice_option2()                                                        // функция для выбора условия сортировки
{
    int opt2;                                                               // объявление переменной для выбора действия 
    printf("\n\n0. Try again");
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

int sum(int k, ...)                                                         // сумма с помощью функции с переменным кол-вом аргументов
{
    int sum = 0;
    int* p = &k;
    while (k--)
    {
        p++;
        sum += *p;
    }
    return sum;
}

int fib(int n)                                                              // вычисления чисел Фибоначи (рекурсия)
{
    if (n < 3)
        return 1;
    else
        return (fib(n - 2) + fib(n - 1));
}