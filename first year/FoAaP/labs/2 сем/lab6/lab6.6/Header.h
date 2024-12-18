#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct LIST																		// объ€вление двунаправленного списка
{
	int data;																	// переменна€ дл€ хранени€ информации
	struct Ring* tree;															// указатель на кольцо
	struct LIST* next;															// указатель на следующий элемент двунаправленного списка
	struct LIST* prev;															// указатель на предыдущий элемент двунаправленного списка
};

struct Ring																		// объ€вление однонаправленного кольца
{
	int data;																	// переменна€ дл€ хранени€ информации
	struct Ring* next;															// указатель на следующий элемент кольца
};

void CreationOfTheList(struct LIST** ptr, int x);								// добавление элемента в конец однонаправленной очереди

void push_after(struct LIST** ptr, int x);										// удаление элемента однонапрваленной очереди

void pop_after(struct LIST** ptr);												// добавить элемент в однонапрваленное кольцо

void push(struct Ring** p);														// добавление элемента в кольцо

struct Ring* pop(struct Ring* p);												// удалить элемент однонапрваленного кольца

void PrintRing(struct Ring* p);													// просмотр элементов кольца

void Menu(struct Ring** p, struct LIST** ptr, int x);