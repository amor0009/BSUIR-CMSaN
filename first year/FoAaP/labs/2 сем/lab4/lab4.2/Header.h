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
	int flag;																	// ��������� �� ������ � ��������
	int NumberOfHospital;														// ����� ��������
	char ilness[N];																// ��������� ����������� ����������� ������
	char NameOfHospitalDoctor[N];												// ��� ����������� �����
	char HospitalAdress[K];														// ������ ��������
	char NameOfDoctor[N];														// ��� �������� �����
};

struct s1
{
	char surname[N];															// ��� ������
	char name[N];
	int age;																	// ������� ������ 
	union info mas[L];															// ������ �����������
};

void Choice1(int* choice1, int* number);										// ����� ��������

void ReadInfoFromFile(struct s1** s1, int* sizeofstruct);						// ������ ������� �������� �� ���������� ����� f.txt

void InputInformationInFile(struct s1* children, int num, const char* name);		// ������ ������� �������� � ��������� ���� f.txt

void InputStruct(struct s1** children, int num);								// ���������� ������� �������� 

void FindChildren(struct s1** ill, struct s1* children, int num, int* numb);	// ����� ���� ����� � ������ ������������

void PrintStruct_s1(struct s1* child, int n);									// ����� ������� ���������

void CheckFile(FILE* fp);														// ������� ��� �������� �������� �����

void qsortMedList(struct s1* ill, int n);										// �������� ������� quicksort �� ���������

void qsortRecursion(struct s1* ill, int low, int high);

int patrition(struct s1* ill, int low, int high);								// ������� ��� ���������� ����� �� �����

void swap(struct s1* list1, struct s1* list2);

void DelEnter(char str[]);														// �������� enter ��� ����� ���������� 

int NumberOfStructs(FILE* fp);													// ���-�� �������� � �����

int �hoice();																	// ����� �������� ��� ����������