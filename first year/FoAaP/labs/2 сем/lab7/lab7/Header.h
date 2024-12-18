#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct tree																		// структура дерева
{
	int data;																	// поле с информацией
	struct tree* left;															// указатель на левое поддерево
	struct tree* right;															// указатель на правое дерево
	struct tree* parent;														// указатель на родителя
};

void AddTree(struct tree** node, int a);										// функция добавления эл-та в дерево

void CreateTree(struct tree** node, int* arr);									// функция создания дерева с помощью чисел из целочисленного массива arr

void PrintTree(struct tree* node);												// функция вывода дерева

void DelTree(struct tree* node);												// функция удаления дерева

void StraightObhod(struct tree* node);											// функция прямого обхода и вывода дерева

void SimmetrObhod(struct tree* node);											// функция симметричного обхода и вывода дерева

void ObratObhod(struct tree* node);												// функция обратного обхода и вывода дерева

int EnterNumber();																// функция ввода числа (кол-ва элементов)

int returnFunc();																// функция для возвращения пользовательского меню

struct tree* InitialMenu(struct tree* node, int* arr);							// пользовательское меню

int* ReadInfoFromFile(int* arr);												// функция чтения чисел в целочисленный массив из файла f.txt

void EnterInfoInFile();															// функция записи чисел в файл f.txt

void PrintTreeLikeTree(struct tree* node, int level);							// функция вывода дерева в виде дерева