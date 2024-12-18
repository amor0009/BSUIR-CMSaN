#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define N 20																	// размер строковых переменных
#define t 10																	// кол-во времён в массивах времён
#define V 32																	// кол-во городов

struct s1																		// объявление структуры, хранящей информацию о городе (населённого пункта)
{
	char City[N];																// название города (населённого пункта)
	char Time1[t][N];															// массив времён отбытия на t элементов
	char Time2[t][N];															// массив времён прибытия на t элементов
	int Line;																	// номер железно-дорожной линии, на которой расположен город (населённый пункт)
	int Dist;																	// расстояние от данного города (населённого пункта) до Минска	
};

struct s2																		// объявление структуры, хранящей информацию о поездке пользователя
{
	char CityFrom[N];															// название города (населённого пункта), из которого пользователь отправляется
	char CityTo[N];																// название города (населённого пункта), в который пользователь отправляется
	char Peresadki[3][N];														// массив станций пересадок, максимальное кол-во 3
	char TimePeres1[3][t][N];													// массив времён отправления поездов со станций пересадки
	char TimePeres2[3][t][N];													// массив времён отправления поездов со станций пересадки
	char TimeFrom[t][N];														// массив времён отправления из данного города (населённого пункта)
	char TimeTo[t][N];															// массив времён прибытия в данный город (населённый пункт)
	int Distance;																// расстояние между городом отправления и городои прибытия
};

struct Edge																		// структура для хранения информации о ребре между двумя городами
{
	int u;																		// номер первой станции
	int v;																		// номер второй станции
	int weight;																	// вес ребра (расстояние между данными городами)
};

//void InputInfoInStruct(struct s1** info);										// ввод информации в массив структур

//char* NameOfTheFile();														// ввод названия файла

//void InputInformationInFileS1(struct s1* info);								// запись массива структур в текстовый файл f.txt

void InputInformationInFileS2(struct s2* infoWay, int num);						// запись структуры, хранящей информацию о поездке пользователя, в текстовый файл result.txt

char* InputCityTo(struct s1* info);												// ввод названия города (населённого пункта), в который пользователь отправляется

char* InputCityFrom(struct s1* info);											// ввод названия города (населённого пункта), из которого пользователь отпраляется												

void CheckFile(FILE* fp);														// функция для проверки открытия файла

void DelEnter(char str[]);														// удаление enter при вводе информации в строковую переменную (char* str/char str[])

void ReadInfoFromFile1(struct s1** info, int* n);								// чтение и массива структур, хранящего информацию о всех городах, из текстового файла f.txt

void PrintStruct_s1(struct s1* info, int n);									// вывод массива структур, хранящего информацию о всех городах

void PrintStruct_s2(struct s2* infoWay, int num);								// вывод структуры, хранящей информацию о поездке пользователя

int NumberOfStructs(FILE* fp);													// нахождение кол-во структур в текстовом файле

int min_distance(int dist[], int visited[]);									// поиск минимального расстояниямежду станциями

struct s2* dijkstra(int graph[V][V], int start, int end, struct s1* info, struct s2* infoWay, int* num);		// алгоритм Дейкстры для обхода графа и нахожения кратчайшего пути и станций пересадок

int find_city_index(struct s1* info, char* name);																// поиск индекса города в массиве структур, хранящем информацию о всех городах

struct s2* InitialMenu(int graph[V][V], struct s1* info, struct s2* infoWay, int n, int* num);					// пользовательское меню

int returnFunc();																								// возвращение к пользовательскому меню

int napravl(struct s1* info, int index1, int index2, int end, int num);											//	поиск напрваления поездки (от Минска или к Минску)	

struct s2* GetTime(struct s1* info, struct s2* infoWay, int indexFrom, int indexTo, int napravl, int number);	// чтение времён отбытия и прибытия

struct s2* GetTimeOfPeresadki(struct s1* info, struct s2* infoWay, int napravl, int number);					// чтение времён отбытия и прибытия станций пересадок