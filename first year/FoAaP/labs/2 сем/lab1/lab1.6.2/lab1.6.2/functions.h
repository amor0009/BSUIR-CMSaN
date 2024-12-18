#pragma once

#include <stdio.h>

int ChoiceOption();																					// ����� ��������(��������� ����� ������� / ��������������� ��������

int CheckFile(FILE*);																				// �������� �������� �����

void CreateFile(const char* name);																	// �������� �����

void UseReadyFiles();																				// ��������������� �������� ������ f1 � f2

void CreateNewFiles();																				// ������� ����� f1 � f2 �������

void PrintFile(const char* name);																	// ������� ����

int IsLetter(char c);																				// �������� �� ������

void FindWordsInF2(char* mas, char** Word1, char** Word2, int* length1, int* length2);				// ����� ���� ���� � ����� f2

char* GetWord(char* text, int WordPos, int WordLength, char* word);									// ��������� ����� �� ������

int FindWord1InF1(const char* string, const char* wordToFind);										// ���������� ������� ����� �� ���� � ����� f1

void ChangeFile(char* text1, char* text2);															// ��������� ������ ����� f1 

int FileToStrLen(char* text1);																		// ����� ������, � ���������� � �� �������

int CountOfStrOfFile(char* text);																	// ���������� ����� � ������ �����

void ChangeFile(char* text1, char* text2);															// ������ ���� � ������ ����� 1#pragma once
