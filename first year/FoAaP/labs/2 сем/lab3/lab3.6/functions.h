#pragma once

#include <stdio.h>

int InputInfoInStruct(struct s1** info);									// ������ ������ � ���������

void PrintStruct_s1(struct s1* inf, int n);									// ����� ���������

void PrintStruct_s2(struct s2* product, int num);							// ����� ���������

void FindProduct(struct s1* inf, struct s2** product, int n, int* number);	// ����� ���������� � �������� �� ��������

int CheckFile(FILE* f);														// �������� ��� �������� �����

void StructInFile1(struct s* info, int num);								// ������� ���� �� ��������� ����� � ������ ��������

void StructFromFile2(struct s1** info, int n);								// ������ ��������� �� �����

void StructInFile2(struct s1* info, int n);									// ������ ��������� � ����