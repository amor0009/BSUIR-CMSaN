#pragma once

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define _NO_CRT_STDIO_INLINE
#define N 15
#define K 30
#define L 6

union info
{
	int flag;																	// находился ли ребёнок в больнице
	int NumberOfHospital;														// номер больницы
	char ilness[N];																// последнее перенесённое заболевание ребёнка
	char NameOfHospitalDoctor[N];												// имя участкового врача
	char HospitalAdress[K];														// адресс больницы
	char NameOfDoctor[N];														// имя лечащего врача
};

struct s1
{
	char surname[N];															// имя ребёнка
	char name[N];
	int age;																	// возраст ребёнка 
	union info mas[L];															// массив объединений
};

void Choice1(int* choice1, int* number);										// выбор действия

void ReadInfoFromFile(struct s1** s1, int* sizeofstruct);						// чтение массива структур из текстового файла f.txt

void InputInformationInFile(struct s1* children, int num, const char* name);		// запись массива структур в текстовый файл f.txt

void InputStruct(struct s1** children, int num);								// заполнение массива структур 

void FindChildren(struct s1** ill, struct s1* children, int num, int* numb);	// поиск всех детей с данным заболеванием

void PrintStruct_s1(struct s1* child, int n);									// вывод массива структуры

void CheckFile(FILE* fp);														// функция для проверки открытия файла

void qsortMedList(struct s1* ill, int n);										// разиение функции quicksort на отдельные

void qsortRecursion(struct s1* ill, int low, int high);

int patrition(struct s1* ill, int low, int high);								// функции для сортировки детей по имени

void swap(struct s1* list1, struct s1* list2);

void DelEnter(char str[]);														// удаление enter при вводе информации 

int NumberOfStructs(FILE* fp);													// кол-во структур в файле

int сhoice();																	// выбор действия над программой