#pragma once

#include <stdio.h>

int InputInfoInStruct(struct s1** inf);					// запись данных в структуру

void PrintStruct(struct s1* inf, int n);				// вывод структуры

void FindProduct(struct s1* inf, int n);				// поиск информации о продукте по названию

int CheckFile(FILE* f);									// проверка при открытии файла