#pragma once

#include <stdio.h>

int InputInfoInStruct(struct s1** inf);					// ������ ������ � ���������

void PrintStruct(struct s1* inf, int n);				// ����� ���������

void FindProduct(struct s1* inf, int n);				// ����� ���������� � �������� �� ��������

int CheckFile(FILE* f);									// �������� ��� �������� �����