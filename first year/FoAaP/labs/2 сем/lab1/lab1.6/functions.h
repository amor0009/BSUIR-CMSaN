#pragma once

#include <stdio.h>

int ChoiceOption();																// ����� �������� ��� ����������

int CheckFile(FILE* f);															// �������� ��� �������� �����

void CreateFile(const char* name);												// �������� �����

void InputFile1(const char* name);												// ���� ������� �����

void InputFile2(const char* name);												// ���� ������� �����

void UseReadyFiles();															// ��������������� �������� ������ f1 � f2

void CreateNewFiles();															// ������� ����� � ������ ����� ������

void PrintFile(const char* name);												// ����� ������ �� �����

int CountOfStrOfFile(const char* name);											// ���������� ����� � ������ �����

void ChangeFile(char* str, const char* file2, const char* file3);				// ������ ���� � ������ ����� 1
