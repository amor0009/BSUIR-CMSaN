#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct tree																		// ��������� ������
{
	int data;																	// ���� � �����������
	struct tree* left;															// ��������� �� ����� ���������
	struct tree* right;															// ��������� �� ������ ������
	struct tree* parent;														// ��������� �� ��������
};

void AddTree(struct tree** node, int a);										// ������� ���������� ��-�� � ������

void CreateTree(struct tree** node, int* arr);									// ������� �������� ������ � ������� ����� �� �������������� ������� arr

void PrintTree(struct tree* node);												// ������� ������ ������

void DelTree(struct tree* node);												// ������� �������� ������

void StraightObhod(struct tree* node);											// ������� ������� ������ � ������ ������

void SimmetrObhod(struct tree* node);											// ������� ������������� ������ � ������ ������

void ObratObhod(struct tree* node);												// ������� ��������� ������ � ������ ������

int EnterNumber();																// ������� ����� ����� (���-�� ���������)

int returnFunc();																// ������� ��� ����������� ����������������� ����

struct tree* InitialMenu(struct tree* node, int* arr);							// ���������������� ����

int* ReadInfoFromFile(int* arr);												// ������� ������ ����� � ������������� ������ �� ����� f.txt

void EnterInfoInFile();															// ������� ������ ����� � ���� f.txt

void PrintTreeLikeTree(struct tree* node, int level);							// ������� ������ ������ � ���� ������