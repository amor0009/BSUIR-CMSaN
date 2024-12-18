#pragma once

int number_of_rows();                                                        // ввод кол-ва строк 

int number_of_symbols();                                                     // функция для ввода кол-ва символов в i-ой строке

char** memory(int n, int m);                                                 // выделене динамической памяти

void row_input(char* mas, int m);                                            // ввод строки 

void row_fgets_input(char* mas, int m);                                      // ввод строки с помощь fgets

char** text_input(char** mas, int n, int m);                                 // ввод текста (всехs строк)

char** text_fgets_input(char** mas, int n, int m);                           // ввод текста( всех строк) с помощью fgets

int str_len(char* mas);                                                      // длина i-й строки

void row_output(char* mas, int n);                                           // вывод строки

void row_fgets_output(char* mas, int n);                                     // вывод строки с помощью puts

void text_output(char** mas, int n, int m);                                  // вывода всех строк

void text_puts_output(char** mas, int n, int m);                             // вывода всех строк с помощью puts

char* changed_text(char* mas, int n);										 // изменение текста

char** changed_text1(char** mas, int m, int n);                              // изменение текста

int sum_salary(char* mas);													 // функция для перевода символов в число и их суммы

char** changed_text2(char** mas, int n, int m);                              // сортировка строк текста по алфавиту

char** changed_text3(char** mas, int n, int m);								 // сортировка строк текста по сумме всех зарплат

char** choice_option1_and_changing(char** mas, int n, int m);				 // выбор условия сортировки и её выполнение

int choice_option2();                                                        // функция для выбора действия над программой

int sum(int k, ...);                                                         // сумма с помощью функции с переменным кол-вом аргументов

int fib(int n);                                                              // вычисления чисел Фибоначи (рекурсия)