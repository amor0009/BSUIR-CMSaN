#pragma once

int n_rows(void);															// функция для ввода ко-ва строк матрицы

int m_columns(void);														// функция для ввода кол-ва столбцов матрицы

int** memory(int n, int m);													// функция для выделения динамической памяти

void input_row_random(int* mas, int n);										// функция для ввода строки случайных чисел

void input_row(int* mas, int n);											// функция для ввода строки с клавиатуры

void input_matr_random(int** matr, int n, int m);							// функция для ввода матрицы случайных чисел

void input_matr(int** matr, int n, int m);									// функция для ввода матрицы с клавиатуры

void print_row(int* mas, int n);											// функция для вывода строки матрицы

void print_matr(int** matr, int n, int m);									// функция для вывода матрицы

int modul(int a);															// функция для получения модуля элемента

int** changed_matr(int** mas, int* row, int* column);						// функция для изменения матрицы

int del_i_max_row(int** mas, int* row, int column, int i_max);				// функция для удаления(сдвиг строк матрицы) строки матрицы, на которой находится максимальный по модулю элемент

int del_j_max_column(int** mas, int row, int* column, int j_max);			// функция для удаления(сдвиг столбцов матрицы) столбца матрицы, на котором находится максимальный по модулю элемент

void choice_option1(int** mas, int n, int m);								// функция для выбора варианта ввода матрицы

int choice_option2(void);													// функция для выбора действия над программой

void free_mas(int** mas);													// функция для очистки буфера