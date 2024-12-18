#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int number_of_symbols()                                     // ввод кол-ва символов строки
{
    int n;
    printf_s("Enter the number of symbols you want to enter: ");
    while (scanf_s(" %d", &n) != 1 || n < 0)                // цикл с предусловием для проверки введёного значения n
    {
        rewind(stdin);                                      // очистка буфера ввода
        printf_s("\nYou have entered the wrong data, try again please: ");
    }
    n = n + 1;                                              // ввод введённого кол-ва символов и + нуль-символ

    return n;
}

char* memory(int n)                                         // выделение динамической памяти
{
    char* mas = (char*)calloc(n, sizeof(char));
    if (!mas)
        printf("\nAttention!!! Memory ERROR!\n");

    return mas;
}

char* text_input_fgets(char* mas, int n)                     // ввод строки с помощью fgets
{
    rewind(stdin);
    printf("\nPlease, enter the text( no more than %d symbols): \n", n - 1);
    fgets(mas, n, stdin);                                   // функция для ввода строк получает до n символов и + нуль-символ

    return mas;
}

char* text_input(char* mas, int n)                          // ввод строки
{
    int c = 0;
    int i = 0;
    printf("\nPlease, enter the text( no more than %d symbols): \n", n - 1);
    rewind(stdin);
    while (--n > 0 && (c = getchar()) != EOF && c != '\n')
        mas[i++] = c;

    mas[i] = '\0';
    return mas;
}

int str_len(char* mas)                                      // длина введённой строки
{
    int i = 0;
    while (mas[i] != '\0')
        i ++ ;
    i++;                                                    // учитываем нуль-символ
    return i;
}

void text_output(char* mas, int n)                          // вывод строки(текста)
{
    printf("\nText: \n");
    for (int i = 0; i < n - 1; i++)
        printf_s("%c", mas[i]);
}

char* changed_text(char* mas, int n)                       // изменение текста
{
    for (int i = 0; i < n; i++)                            // изменение первой буквы первого слова на прописную 
    {
        if (mas[i] >= 65 && mas[i] <= 90)                  // если она является прописной, то ничего не делаем
        {
            while (mas[i + 1] != '.' && mas[i + 1] != '!' && mas[i + 1] != '?' && mas[i + 1] != ' ' && mas[i + 1] != '\t')  // изменение букв на строчные конца слова  
            {
                if (mas[i + 1] >= 65 && mas[i + 1] <= 90)
                    mas[i + 1] += 32;
                i++;
            }
            break;
        }

        if (mas[i] >= 97 && mas[i] <= 122)                  // если она является строчной, то меняем её на прописную
        {
            mas[i] -= 32;
            while (mas[i + 1] != '.' && mas[i + 1] != '!' && mas[i + 1] != '?' && mas[i + 1] != ' ' && mas[i + 1] != '\t')  // изменение букв на строчные конца слова  
            {
                if (mas[i + 1] >= 65 && mas[i + 1] <= 90)
                    mas[i + 1] += 32;
                i++;
            }
            break;
        }
    }
    
    for (int i = 0; i < n; i++)                              // изменения для следующих слов
        if (mas[i] == '.' || mas[i] == '!' || mas[i] == '?')
            for (int k = i + 1; k < n; k++)
                if (mas[k] != '.' && mas[k] != '!' && mas[k] != '?' && mas[k] != ' ' && mas[k] != '\t')
                {
                    if (mas[k] >= 97 && mas[k] <= 122)
                        mas[k] -= 32;

                    while (mas[k + 1] != '.' && mas[k + 1] != '!' && mas[k + 1] != '?' && mas[k + 1] != ' ' && mas[k + 1] != '\t')  // изменение букв на строчные конца слова  
                    {
                        if (mas[k + 1] >= 65 && mas[k + 1] <= 90)
                            mas[k + 1] += 32;
                        k++;
                    }

                    break;
                }
    return mas;
}

int choice_option()                                                         // функция для выбора действия над программой
{
    int opt;                                                                // объявление переменной для выбора действия 
    printf("\n\n0. Try again");
    printf("\n1. Finish the programm");
    printf("\nYour choice is: ");

    while ((scanf_s(" %d", &opt) != 1) || ((opt < 0) || (opt > 1)))         // цикл с предусловием для проверки введённого значения переменной cho (выбора лействия)
    {
        rewind(stdin);
        printf("\nYou have entered the wrong data,\nyou should to enter 0 or 1 to choice the option, try again please: ");
    }

    printf("\nThank you for your choice!\n");

    if (opt == 1)                                                           // условный оператор if для вывода сообщения при конце программы
        printf("\nThank you for using my program!\nGood luck :)");

    printf("\n");
    return opt;
}