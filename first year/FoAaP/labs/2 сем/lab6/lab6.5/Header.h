#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct LIST																		// ��������� ����������. ������
{
	int data;																	// ��������. ����
	struct LIST* next;															// ��������� �� ��������� ������� ������
	struct Ring* ring;															// ��������� �� ������
};

struct Ring																		// ��������� ���������. ������
{
	int data;																	// ��������. ����
	struct Ring* next;															// ����. �� ����. ������� ������
	struct Ring* prev;															// ����. �� ���������� ������� ������
};

void PushHead(struct LIST** head, struct LIST** tail, int x);					// ������� ���������� � ������ ������

void PopHead(struct LIST** head, struct LIST** tail);							// ������� �������� � ������ ������

void PushTail(struct LIST** head, struct LIST** tail, int x);					// ������� ���������� �������� � ����� ������

void PopTail(struct LIST** head, struct LIST** tail);							// ������� �������� �������� � ������ ������

struct Ring* pushRing(struct Ring* p, int x);									// ������� ���������� �������� � ������

struct Ring* popRing(struct Ring* p);											// ������� �������� �������� ������
	
void PrintRing1(struct Ring* p);												// ������� ������ ������ 1

void PrintRing2(struct Ring* p);												// ������� ������ ������ 2

int Number();																	// ������� ����� ���-�� �����

int EnterNumber(int i);															// ������� ����� �����

int NumberOfCurrentList();														// ������� ����� ������ �������� �������� ������

struct LIST* FindAndPushCurrentList(struct LIST* head, int position);			// ������� ���������� �������� ������ � ���������� �������� � ��� ������

struct LIST* FindAndPopCurrentList(struct LIST* head, int position);			// ������� ���������� �������� �������� ������ � �������� �������� ��� ������

void FindAndPrintRingCurrentList(struct LIST* head, int position);				// ������� ���������� �������� ��-�� ������ � ����� ��� ������

int returnFunc();																// ������� ��� ����������� ����������������� ����

void InitialMenu(struct LIST** head, struct LIST** tail);						// ���������������� ����

int NumberOfLists(struct LIST* head);											// ������� ���������� ���-�� ��-�� ������

int NumberOfElementsInRing(struct Ring* ring);									// ������� ���������� ���-�� ��-�� � ������

struct LIST* FindCurrentList(struct LIST* head, int position);					// ������� ���������� �������� �������� ������

int TakeData(struct Ring* p);													// ������� ������ ���������� � ���. ���� ������

void removeElement(struct LIST** head, struct LIST** tail);						// ������� ������������� ��������� ������ �� ���������