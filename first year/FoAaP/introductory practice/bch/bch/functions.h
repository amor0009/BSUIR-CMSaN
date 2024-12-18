#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define N 20																	// ������ ��������� ����������
#define t 10																	// ���-�� ����� � �������� �����
#define V 32																	// ���-�� �������

struct s1																		// ���������� ���������, �������� ���������� � ������ (���������� ������)
{
	char City[N];																// �������� ������ (���������� ������)
	char Time1[t][N];															// ������ ����� ������� �� t ���������
	char Time2[t][N];															// ������ ����� �������� �� t ���������
	int Line;																	// ����� �������-�������� �����, �� ������� ���������� ����� (��������� �����)
	int Dist;																	// ���������� �� ������� ������ (���������� ������) �� ������	
};

struct s2																		// ���������� ���������, �������� ���������� � ������� ������������
{
	char CityFrom[N];															// �������� ������ (���������� ������), �� �������� ������������ ������������
	char CityTo[N];																// �������� ������ (���������� ������), � ������� ������������ ������������
	char Peresadki[3][N];														// ������ ������� ���������, ������������ ���-�� 3
	char TimePeres1[3][t][N];													// ������ ����� ����������� ������� �� ������� ���������
	char TimePeres2[3][t][N];													// ������ ����� ����������� ������� �� ������� ���������
	char TimeFrom[t][N];														// ������ ����� ����������� �� ������� ������ (���������� ������)
	char TimeTo[t][N];															// ������ ����� �������� � ������ ����� (��������� �����)
	int Distance;																// ���������� ����� ������� ����������� � ������� ��������
};

struct Edge																		// ��������� ��� �������� ���������� � ����� ����� ����� ��������
{
	int u;																		// ����� ������ �������
	int v;																		// ����� ������ �������
	int weight;																	// ��� ����� (���������� ����� ������� ��������)
};

//void InputInfoInStruct(struct s1** info);										// ���� ���������� � ������ ��������

//char* NameOfTheFile();														// ���� �������� �����

//void InputInformationInFileS1(struct s1* info);								// ������ ������� �������� � ��������� ���� f.txt

void InputInformationInFileS2(struct s2* infoWay, int num);						// ������ ���������, �������� ���������� � ������� ������������, � ��������� ���� result.txt

char* InputCityTo(struct s1* info);												// ���� �������� ������ (���������� ������), � ������� ������������ ������������

char* InputCityFrom(struct s1* info);											// ���� �������� ������ (���������� ������), �� �������� ������������ �����������												

void CheckFile(FILE* fp);														// ������� ��� �������� �������� �����

void DelEnter(char str[]);														// �������� enter ��� ����� ���������� � ��������� ���������� (char* str/char str[])

void ReadInfoFromFile1(struct s1** info, int* n);								// ������ � ������� ��������, ��������� ���������� � ���� �������, �� ���������� ����� f.txt

void PrintStruct_s1(struct s1* info, int n);									// ����� ������� ��������, ��������� ���������� � ���� �������

void PrintStruct_s2(struct s2* infoWay, int num);								// ����� ���������, �������� ���������� � ������� ������������

int NumberOfStructs(FILE* fp);													// ���������� ���-�� �������� � ��������� �����

int min_distance(int dist[], int visited[]);									// ����� ������������ ��������������� ���������

struct s2* dijkstra(int graph[V][V], int start, int end, struct s1* info, struct s2* infoWay, int* num);		// �������� �������� ��� ������ ����� � ��������� ����������� ���� � ������� ���������

int find_city_index(struct s1* info, char* name);																// ����� ������� ������ � ������� ��������, �������� ���������� � ���� �������

struct s2* InitialMenu(int graph[V][V], struct s1* info, struct s2* infoWay, int n, int* num);					// ���������������� ����

int returnFunc();																								// ����������� � ����������������� ����

int napravl(struct s1* info, int index1, int index2, int end, int num);											//	����� ����������� ������� (�� ������ ��� � ������)	

struct s2* GetTime(struct s1* info, struct s2* infoWay, int indexFrom, int indexTo, int napravl, int number);	// ������ ����� ������� � ��������

struct s2* GetTimeOfPeresadki(struct s1* info, struct s2* infoWay, int napravl, int number);					// ������ ����� ������� � �������� ������� ���������