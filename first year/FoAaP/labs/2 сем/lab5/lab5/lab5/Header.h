#pragma once

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct FILO																		// ���������� �����
{
	char data;																	// ���������� ��� �������� ������
	int x;
	struct FILO* next;															// ��������� �� ��������� ������� �����
};

struct FILO* push(struct FILO* h, char sym);									// ���������� �������� � ������ �����

struct FILO* push1(struct FILO* h, char sym, int x);							// ���������� �������� � ������ (� ������������ ������� � ������)

struct FILO* pop(struct FILO* h);												// �������� �������� ����� �� ������

int IsEmpty(struct FILO* h);													// ������� ��� �������� ������ ����� (������ ��)

char peek(struct FILO* h);														// ������� ������ �� ������ �����

int IsEquel(char a, char b);													// ������� ��� �������� ����������� ����� ������

char* Input();																	// ���� ��������������� ���������

int Check(struct FILO* h, char* string);										// �������� �������� ������������ ������ � ������� �������������� ���������

int choice();																	// ����� �������� ��� ����������

void del(char* string, int x);													// ������� ��� �������� ������� ������� x �� ������

int CheckAndReplace(struct FILO* h, char* string);								// ������� �������� ����������� ������ � ��������� � ������