#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#define N 20

struct s1																		// шаблон структуры
{
	char name[N];																// наименование товара
	char country[N];															// название страны, импортирующей товар
	int volume;																	// объём экспорта данного товара
};

struct s2																		// шаблон структуры
{
	char name[N];																// наименование товара
	char country[N];															// название страны, импортирующей товар
	int volume;																	// объём экспорта данного товара
};

int InputInfoInStruct(struct s1** info)											// ввод информации массива структур
{

	struct s1* inf;																// указатель на массив структур
	int n;																		// кол-во товаров
	int i;
	printf("Enter the number of products: ");
	scanf_s("%d", &n);
	while (n <= 0)																// проверка
	{
		rewind(stdin);
		printf("\nERROR. You have entered the wrong data!\nTry again please.");
		scanf_s("%d", &n);
	}
	inf = (struct s1*)calloc(n, sizeof(struct s1));								// выделение памяти под массив структур
	if (inf == NULL)															// проверка на выделение памяти
	{
		printf("\nNo memory has been allocated for the array!\n");
		return 0;
	}
	for (i = 0; i < n; i++)														// цикл ввода структур в массив
	{
		rewind(stdin);
		printf("\nEnter the information about %2d product", i + 1);
		printf("\nEnter the name of the product: ");					
		gets(inf[i].name);														// ввод названия продукта
		printf("Enter the name of the country importing the product: ");
		gets(inf[i].country);													// ввод названия страны
		printf("Enter the batch volume in pieces: ");
		scanf_s("%d", &inf[i].volume);											// ввод объёма товара
		while (inf[i].volume < 0)												// проверка
		{
			rewind(stdin);
			printf("\nERROR! You have entered the wrong data!\nTry again please.");
			scanf_s("%d", &inf[i].volume);
		}
	}
	*info = inf;
	return n;
}

void PrintStruct_s1(struct s1 *inf, int n)										// вывод структуры
{
	int i;
	printf("\nThe entered information about products: ");
	printf("\n   NAME			 COUNTRY		VOLUME");
	for (i = 0; i < n; i++)														// цикл для вывода каждой структуры
	{
		printf("\n");
		printf("%8s\t\t", inf[i].name);
		printf("%8s\t\t", inf[i].country);
		printf("%5d", inf[i].volume);
	}
}

void PrintStruct_s2(struct s2* inf, int num)									// вывод структуры
{
	int i;
	printf("\nThe entered information about products: ");
	printf("\n   NAME			 COUNTRY		VOLUME");
	for (i = 0; i < num; i++)													// цикл для вывода каждой структуры
	{
		printf("\n");
		printf("%8s\t\t", inf[i].name);
		printf("%8s\t\t", inf[i].country);
		printf("%5d", inf[i].volume);
	}
}

void FindProduct(struct s1* inf, struct s2** product, int n, int* number)		// поиск нужных полей структуры и их вывод
{
	struct s2* prod;
	prod = (struct s2*)calloc(n, sizeof(struct s2));
	int num = 0;
	int flag = 0;
	int j = 0;

	printf("\n\nEnter the name of the product, information you would like to know: ");
	char* word = (char*)calloc(20, sizeof(char));								// выделение памяти для ввода слова
	rewind(stdin);
	gets(word);																	// ввод слова
	for (int i = 0; i < n; i++)
		if (strcmp(word, inf[i].name) == 0)										// сравниваем название продукта и ввод пользователя
		{
			flag = 1;
			num = num + 1;
			strcpy(prod[j].name, inf[i].name);
			strcpy(prod[j].country, inf[i].country);
			prod[j].volume = inf[i].volume;
			j++;
		}
	prod = (struct s2*)realloc(prod, (num * sizeof(struct s2)));

	if (flag == 0)
	{
		printf("\nThere is not this product!!!!\n");
		return;
	}
	*number = num;
	*product = prod;
}

int CheckFile(FILE* f)															// проверка при открытии файла
{
	if (f == NULL)
	{
		printf("ERROR");
		return 0;
	}
	return 1;
}



//void StructInFile1(struct s1* info, int n)										// запись структуры в файл
//{
//	FILE* fp;
//	fopen_s(&fp, "f.bin", "wb");
//	for (int i = 0; i < n; i++)
//		fwrite(&info[i], sizeof(struct s1), 1, fp);
//	fclose(fp);
//}
//
//
//void StructFromFile1(struct s1* info, int n)									// загрузка из файла структуры
//{
//	FILE* fp;
//	fopen_s(&fp, "f.bin", "rb");
//	free(info);																	// указатель на массив структур
//	fseek(fp, 0, SEEK_END);
//	int size = ftell(fp);
//	fseek(fp, 0, SEEK_SET);
//	int num = size / sizeof(struct s1);
//	info = (struct s1*)calloc(num, sizeof(struct s1));
//
//	for (int i = 0; i < num; i++) 
//		fread(&info[i], sizeof(struct s1), 1, fp);
//	fclose(fp);
//}


void StructFromFile2(struct s1** info, int n)									// Перевод инфы из бинарного файла в массив структур
{
	FILE* fp = fopen("f.bin", "rb");
	free(*info);
	*info = (struct s1*)calloc(n, sizeof(struct s1));
	for (int i = 0; i < n; i++)
	{
		fread(&((*info + i)->name), sizeof(char), N, fp);
		fread(&((*info + i)->country), sizeof(char), N, fp);
		fread(&((*info + i)->volume), sizeof(int), 1, fp);
	}
	fclose(fp);
}


void StructInFile2(struct s1* info, int n)										// Ввод инфы из массива структур в бинарный файл
{
	FILE* fp = fopen("f.bin", "wb");
	for (int i = 0; i < n; i++)
	{
		fwrite(info[i].name, sizeof(char), N, fp);
		fwrite(info[i].country, sizeof(char), N, fp);
		fwrite(&info[i].volume, sizeof(int), 1, fp);
	}
	fclose(fp);
}