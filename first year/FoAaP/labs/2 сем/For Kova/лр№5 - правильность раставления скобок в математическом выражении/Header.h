#pragma once

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct FILO																		// объ€вление стека
{
	char data;																	// перемннна€ дл€ хранени€ скобок
	struct FILO* next;															// указатель на следующий элемент стека
};

struct FILO* push(struct FILO* h, char sym);									// добавление элемента в голову стека

struct FILO* pop(struct FILO* h);												// удаление элемента стека из головы

int IsEmpty(struct FILO* h);													// функци€ дл€ проверки головы стека (пуста€ ли)

char peek(struct FILO* h);														// достать символ из головы стека

int IsEquel(char a, char b);													// функци€ дл€ проверки соответсви€ типов скобок

char* Input();															// ввод математического выражени€

int Check(struct FILO* h, char* string);										// проверка верности раставленных скобок в ведЄнном математическом выражении

int choice();																	// выбор действи€ над программой