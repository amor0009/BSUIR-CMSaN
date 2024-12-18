#pragma once

#include <stdio.h>

int InputInfoInStruct(struct s1** info);									// запись данных в структуру

void PrintStruct_s1(struct s1* inf, int n);									// вывод структуры

void PrintStruct_s2(struct s2* product, int num);							// вывод структуры

void FindProduct(struct s1* inf, struct s2** product, int n, int* number);	// поиск информации о продукте по названию

int CheckFile(FILE* f);														// проверка при открытии файла

void StructInFile1(struct s* info, int num);								// Перевод инфы из бинарного файла в массив структур

void StructFromFile2(struct s1** info, int n);								// чтение структуры из файла

void StructInFile2(struct s1* info, int n);									// запись структуры в файл