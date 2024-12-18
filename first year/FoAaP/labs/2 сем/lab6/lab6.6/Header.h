#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct LIST																		// ���������� ���������������� ������
{
	int data;																	// ���������� ��� �������� ����������
	struct Ring* tree;															// ��������� �� ������
	struct LIST* next;															// ��������� �� ��������� ������� ���������������� ������
	struct LIST* prev;															// ��������� �� ���������� ������� ���������������� ������
};

struct Ring																		// ���������� ����������������� ������
{
	int data;																	// ���������� ��� �������� ����������
	struct Ring* next;															// ��������� �� ��������� ������� ������
};

void CreationOfTheList(struct LIST** ptr, int x);								// ���������� �������� � ����� ���������������� �������

void push_after(struct LIST** ptr, int x);										// �������� �������� ���������������� �������

void pop_after(struct LIST** ptr);												// �������� ������� � ���������������� ������

void push(struct Ring** p);														// ���������� �������� � ������

struct Ring* pop(struct Ring* p);												// ������� ������� ����������������� ������

void PrintRing(struct Ring* p);													// �������� ��������� ������

void Menu(struct Ring** p, struct LIST** ptr, int x);