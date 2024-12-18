#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct LIST																		// структура однонапрвл. списка
{
	int data;																	// информац. поле
	struct LIST* next;															// указатель на следующий элемент списка
	struct Ring* ring;															// указатель на кольцо
};

struct Ring																		// структура двунапрвл. кольца
{
	int data;																	// информац. поле
	struct Ring* next;															// указ. на след. элемент кольца
	struct Ring* prev;															// указ. на предыдущий элемент кольца
};

void PushHead(struct LIST** head, struct LIST** tail, int x);					// функция добавления в голову списка

void PopHead(struct LIST** head, struct LIST** tail);							// функция удаление с головы списка

void PushTail(struct LIST** head, struct LIST** tail, int x);					// функция добавление элемента в хвост списка

void PopTail(struct LIST** head, struct LIST** tail);							// функция удаление элемента с хвоста списка

struct Ring* pushRing(struct Ring* p, int x);									// функция добавление элемента в кольцо

struct Ring* popRing(struct Ring* p);											// функция удаление элемента кольца
	
void PrintRing1(struct Ring* p);												// функция вывода кольца 1

void PrintRing2(struct Ring* p);												// функция вывода кольца 2

int Number();																	// функция ввода кол-ва чисел

int EnterNumber(int i);															// функция ввода числа

int NumberOfCurrentList();														// функция ввода индека текущего элемента списка

struct LIST* FindAndPushCurrentList(struct LIST* head, int position);			// функция нахождения текущего списка и добавления элемента в его кольцо

struct LIST* FindAndPopCurrentList(struct LIST* head, int position);			// функция нахождения текущего элемента списка и удаления элемента его кольца

void FindAndPrintRingCurrentList(struct LIST* head, int position);				// функция нахождения текущего эл-та списка и вывод его кольца

int returnFunc();																// функция для возвращения пользовательского меню

void InitialMenu(struct LIST** head, struct LIST** tail);						// пользовательское меню

int NumberOfLists(struct LIST* head);											// функция нахождения кол-ва эл-ов списка

int NumberOfElementsInRing(struct Ring* ring);									// функция нахождения кол-ва эл-ов в кольце

struct LIST* FindCurrentList(struct LIST* head, int position);					// функция нахождения текущего элемента списка

int TakeData(struct Ring* p);													// функция взятия информацию с инф. поля кольца

void removeElement(struct LIST** head, struct LIST** tail);						// функция распределения элементов кольца по остальным