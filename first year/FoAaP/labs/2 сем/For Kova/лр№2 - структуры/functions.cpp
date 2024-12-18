#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

struct s1																		// шаблон структуры
{
	char* name;
	char* country;
	int volume;
};

int InputInfoInStruct(struct s1 ** info)
{

	struct s1 *inf;																// указатель на массив структур
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
		inf[i].name = (char*)calloc(50, sizeof(char));							// выделение памяти для названия продукта
		gets(inf[i].name);														// ввод названия продукта
		printf("Enter the name of the country importing the product: ");
		inf[i].country = (char*)calloc(50, sizeof(char));						// выделение памяти для названия страны
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

void PrintStruct(struct s1* inf, int n)											// вывод структуры
{
	int i;
	printf("\nThe entered information about products: ");
	printf("\n NAME			COUNTRY			VOLUME");
	for (i = 0; i < n; i++)														// цикл для вывода каждой структуры
	{
		printf("\n");
		printf("%s\t\t\t%s\t\t\t%d", inf[i].name, inf[i].country, inf[i].volume);

	}
}

void FindProduct(struct s1* inf, int n)											// поиск нужных полей структуры и их вывод
{
	int sum = 0;
	int flag = 0;
	printf("\n\nEnter the name of the product, information you would like to know: ");
	char* word = (char*)calloc(50,sizeof(char));								// выделение памяти для ввода слова
	rewind(stdin);
	gets(word);																	// ввод слова
	printf("Countries: ");
	for (int i = 0; i < n; i++)
		if (strcmp(word, inf[i].name) == 0)										// сравниваем название продукта и ввод пользователя
		{
			flag = 1;
			printf("%8s ", inf[i].country);
			sum = sum + inf[i].volume;											// получение общего объёма
		}

	if (flag == 0)
		printf("\nThere is not this product!!!!\n");

	printf("\nGeneral volume of this product is: %d", sum);

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