#include "functions.h"

//void InputInfoInStruct(struct s1** info)										// ввод информации в массив структур, хранящий информацию о всех городах
//{
//	struct s1* inf;
//	inf = (struct s1*)calloc(V, sizeof(struct s1));								// объявление и инициализация массива структур на V городов
//	if (inf == NULL)															// проверка на выделение памяти
//	{
//		printf("\nNo memory has been allocated for the array!\n");
//		return;
//	}
//
//	for (int i = 0; i < V; i++)													// цикл для ввода информации о V городах
//	{
//		rewind(stdin);
//		printf("\nEnter the information about %d city.", i + 1);
//
//		printf("\nEnter the name of the city: ");
//		fgets(inf[i].City, N, stdin);
//		DelEnter(inf[i].City);													// удаление \n с конца строки
//		rewind(stdin);
//
//		printf("Enter line: ");
//		scanf_s("%d", &inf[i].Line);
//		while (inf[i].Line < 0)													// проверка введённой переменной
//		{
//			rewind(stdin);
//			printf("\nERROR! You have entered the wrong data!\nTry again please.\nYour choice is ");
//			scanf_s("%d", &inf[i].Dist);
//		}
//		rewind(stdin);
//
//		printf("Enter the departure time: ");
//		for (int j = 0; j < t; j++)												// цикл для ввода t времён отправления
//		{
//			fgets(inf[i].Time1[j], N, stdin);
//			DelEnter(inf[i].Time1[j]);
//			rewind(stdin);
//		}
//		rewind(stdin);
//
//		printf("Enter the Time2: ");
//		for (int j = 0; j < t; j++)												// цикл для ввода t времён прибытия
//		{
//			fgets(inf[i].Time2[j], N, stdin);
//			DelEnter(inf[i].Time2[j]);
//			rewind(stdin);
//		}
//		rewind(stdin);
//
//		printf("Dist ");
//		scanf_s("%d", &inf[i].Dist);
//		while (inf[i].Dist < 0)													// проверка введённой переменной
//		{
//			rewind(stdin);
//			printf("\nERROR! You have entered the wrong data!\nTry again please.\nYour choice is ");
//			scanf_s("%d", &inf[i].Dist);
//		}
//		rewind(stdin);
//	}
//	*info = inf;																// сохранение массива структур
//}

//char* NameOfTheFile()
//{
//	char* name = (char*)calloc(N, sizeof(char));
//	printf("Enter the name of the file, you would like to save information about your trip in: ");
//	fgets(name, N, stdin);
//	DelEnter(name);													// удаление \n с конца строки
//	rewind(stdin);
//	return name;
//}

//void InputInformationInFileS1(struct s1* info)									// запись массива структур в текстовый файл f.txt
//{
//	FILE* fp = fopen("f.txt", "w");
//	CheckFile(fp);
//	for (int i = 0; i < V; i++)													// цикл для записи массива структур в текстовый файл f.txt 
//	{
//		fprintf(fp, "%s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d", info[i].City, info[i].Line, info[i].Time1[0], info[i].Time1[1], info[i].Time1[2],
//			info[i].Time1[3], info[i].Time1[4], info[i].Time1[5], info[i].Time1[6], info[i].Time1[7], info[i].Time1[8], info[i].Time1[9], info[i].Time2[0], info[i].Time2[1],
//			info[i].Time2[2], info[i].Time2[3], info[i].Time2[4], info[i].Time2[5], info[i].Time2[6], info[i].Time2[7], info[i].Time2[8], info[i].Time2[9], info[i].Dist);
//		fprintf(fp, "\n");
//	}
//	fclose(fp);
//}

void InputInformationInFileS2(struct s2* infoWay, int num)						// запись массива структур в текстовый файл result.txt
{
	FILE* fp = fopen("result.txt", "w");
	CheckFile(fp);
	if (num == 0)																// если на маршруте нет пересадок, то запись в файл будет иметь следующий вид
	{
		fprintf(fp, "%s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s -> %d", infoWay[0].CityFrom, infoWay[0].TimeFrom[0], infoWay[0].TimeFrom[1], infoWay[0].TimeFrom[2],
			infoWay[0].TimeFrom[3], infoWay[0].TimeFrom[4], infoWay[0].TimeFrom[5], infoWay[0].TimeFrom[6], infoWay[0].TimeFrom[7], infoWay[0].TimeFrom[8], infoWay[0].TimeFrom[9], infoWay[0].CityTo, infoWay[0].TimeTo[0], infoWay[0].TimeTo[1],
			infoWay[0].TimeTo[2], infoWay[0].TimeTo[3], infoWay[0].TimeTo[4], infoWay[0].TimeTo[5], infoWay[0].TimeTo[6], infoWay[0].TimeTo[7], infoWay[0].TimeTo[8], infoWay[0].TimeTo[9], infoWay[0].Distance);
	}
	else if (num == 1)															// если на маршруте есть 1 (одна) пересадка, то запись в файл будет иметь следующий вид
	{
		fprintf(fp, "%s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s -> %d", infoWay[0].CityFrom, infoWay[0].TimeFrom[0], infoWay[0].TimeFrom[1], infoWay[0].TimeFrom[2],
			infoWay[0].TimeFrom[3], infoWay[0].TimeFrom[4], infoWay[0].TimeFrom[5], infoWay[0].TimeFrom[6], infoWay[0].TimeFrom[7], infoWay[0].TimeFrom[8], infoWay[0].TimeFrom[9], infoWay[0].Peresadki[0],
			infoWay[0].TimePeres1[0][0], infoWay[0].TimePeres1[0][1], infoWay[0].TimePeres1[0][2], infoWay[0].TimePeres1[0][3], infoWay[0].TimePeres1[0][4], infoWay[0].TimePeres1[0][5], infoWay[0].TimePeres1[0][6],
			infoWay[0].TimePeres1[0][7], infoWay[0].TimePeres1[0][8], infoWay[0].TimePeres1[0][9], infoWay[0].Peresadki[0], infoWay[0].TimePeres2[0][0], infoWay[0].TimePeres2[0][1], infoWay[0].TimePeres2[0][2],
			infoWay[0].TimePeres2[0][3], infoWay[0].TimePeres2[0][4], infoWay[0].TimePeres2[0][5], infoWay[0].TimePeres2[0][6], infoWay[0].TimePeres2[0][7], infoWay[0].TimePeres2[0][8], infoWay[0].TimePeres2[0][9],
			infoWay[0].CityTo, infoWay[0].TimeTo[0], infoWay[0].TimeTo[1], infoWay[0].TimeTo[2], infoWay[0].TimeTo[3], infoWay[0].TimeTo[4], infoWay[0].TimeTo[5], infoWay[0].TimeTo[6], infoWay[0].TimeTo[7],
			infoWay[0].TimeTo[8], infoWay[0].TimeTo[9], infoWay[0].Distance);
	}
	else																		// если на маршруте более 1 (одной) пересадки, то запись в файл будет иметь следующий вид
	{	
		fprintf(fp, "%s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s -> %d", infoWay[0].CityFrom, infoWay[0].TimeFrom[0], infoWay[0].TimeFrom[1], infoWay[0].TimeFrom[2],
			infoWay[0].TimeFrom[3], infoWay[0].TimeFrom[4], infoWay[0].TimeFrom[5], infoWay[0].TimeFrom[6], infoWay[0].TimeFrom[7], infoWay[0].TimeFrom[8], infoWay[0].TimeFrom[9], infoWay[0].Peresadki[0],
			infoWay[0].TimePeres1[0][0], infoWay[0].TimePeres1[0][1], infoWay[0].TimePeres1[0][2], infoWay[0].TimePeres1[0][3], infoWay[0].TimePeres1[0][4], infoWay[0].TimePeres1[0][5], infoWay[0].TimePeres1[0][6],
			infoWay[0].TimePeres1[0][7], infoWay[0].TimePeres1[0][8], infoWay[0].TimePeres1[0][9], infoWay[0].Peresadki[0], infoWay[0].TimePeres2[0][0], infoWay[0].TimePeres2[0][1], infoWay[0].TimePeres2[0][2],
			infoWay[0].TimePeres2[0][3], infoWay[0].TimePeres2[0][4], infoWay[0].TimePeres2[0][5], infoWay[0].TimePeres2[0][6], infoWay[0].TimePeres2[0][7], infoWay[0].TimePeres2[0][8], infoWay[0].TimePeres2[0][9], infoWay[0].Peresadki[1],
			infoWay[0].TimePeres1[1][0], infoWay[0].TimePeres1[1][1], infoWay[0].TimePeres1[1][2], infoWay[0].TimePeres1[1][3], infoWay[0].TimePeres1[1][4], infoWay[0].TimePeres1[1][5], infoWay[0].TimePeres1[1][6],
			infoWay[0].TimePeres1[1][7], infoWay[0].TimePeres1[1][8], infoWay[0].TimePeres1[1][9], infoWay[0].Peresadki[1], infoWay[0].TimePeres2[1][0], infoWay[0].TimePeres2[1][1], infoWay[0].TimePeres2[1][2],
			infoWay[0].TimePeres2[1][3], infoWay[0].TimePeres2[1][4], infoWay[0].TimePeres2[1][5], infoWay[0].TimePeres2[1][6], infoWay[0].TimePeres2[1][7], infoWay[0].TimePeres2[1][8], infoWay[0].TimePeres2[1][9],
			infoWay[0].CityTo, infoWay[0].TimeTo[0], infoWay[0].TimeTo[1], infoWay[0].TimeTo[2], infoWay[0].TimeTo[3], infoWay[0].TimeTo[4], infoWay[0].TimeTo[5], infoWay[0].TimeTo[6], infoWay[0].TimeTo[7],
			infoWay[0].TimeTo[8], infoWay[0].TimeTo[9], infoWay[0].Distance);
	}
	fprintf(fp, "\n");
		
	fclose(fp);
}

int CheckCity(struct s1* info,char* str)										// проверка, есть ли введённый город в массиве структур
{
	int flag = 0;																// пусть изначально города нет в массиве структур
	for (int i = 0; i < V; i++)													// цикл для прохода по всем элементам (городам) массива структур
		if (strcmp(info[i].City, str) == 0)
			flag = 1;															// если введённый город совпал с городом из массива структур, то flag = 1
	if (flag == 0)
		printf("\nThere is no this city. Try again please!");
	return flag;
}

char* InputCityTo(struct s1* info)												// ввод названия города (населённого пункта), в который пользователь едет
{
	int flag;																	// есть ли введённый город в массиве структур
	char* StrCityTo;
	do
	{
		rewind(stdin);
		flag = 0;
		printf("\nEnter the city, where you are going: ");
		StrCityTo = (char*)calloc(N, sizeof(char));								// выделение динамической памяти для ввода названия города
		fgets(StrCityTo, N, stdin);
		DelEnter(StrCityTo);
		flag = CheckCity(info, StrCityTo);										// проверка, есть ли введённый город в массиве структур
	} while (!flag);															// если данного города нет, то пользователь вводит город снова
	
	return StrCityTo;
}

char* InputCityFrom(struct s1* info)											// ввод названия города (населённого пункта), из которого едет пользователь
{
	int flag;																	// есть ли введённый город в массиве структур
	char* StrCityFrom;
	do
	{
		rewind(stdin);
		flag = 0;
		printf("\nEnter the city, where you are coming from: ");
		StrCityFrom = (char*)calloc(N, sizeof(char));							// выделение динамической памяти для ввода названия города
		fgets(StrCityFrom, N, stdin);
		DelEnter(StrCityFrom);
		flag = CheckCity(info, StrCityFrom);									// проверка, есть ли введённый город в массиве структур
	} while (!flag);															// если данного города нет, то пользователь вводит город снова

	return StrCityFrom;
}

void CheckFile(FILE* fp)														// функция для проверки открытия файла
{
	if (fp == NULL)																// проверка открытия файла
	{
		printf("ERROR");
		return;
	}
}

void DelEnter(char str[])														// удаление \n при вводе информации 
{
	int l = strlen(str);
	str[l - 1] = '\0';
}

void ReadInfoFromFile1(struct s1** info, int* n)								// чтение информации о всех городах в массив структур info
{
	FILE* fp = fopen("f.txt", "r");
	CheckFile(fp);
	int num = NumberOfStructs(fp);												// узнаём кол-во структур в файле
	*info = (struct s1*)calloc(num , sizeof(struct s1));						// выделение динамической памяти для массива структур
	fseek(fp, 0, SEEK_SET);														// устанавливаем курсор на начало файал f.txt

	for (int i = 0; i < num; i++)												// цикл для чтения информации о num городах в массив структур из файла f.txt 
		fscanf(fp, "%s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d", &((*info + i)->City), &((*info + i)->Line), &((*info + i)->Time1[0]), &((*info + i)->Time1[1]), &((*info + i)->Time1[2]),
			&((*info + i)->Time1[3]), &((*info + i)->Time1[4]), &((*info + i)->Time1[5]), &((*info + i)->Time1[6]), &((*info + i)->Time1[7]), &((*info + i)->Time1[8]), &((*info + i)->Time1[9]),
			&((*info + i)->Time2[0]), &((*info + i)->Time2[1]), &((*info + i)->Time2[2]), &((*info + i)->Time2[3]), &((*info + i)->Time2[4]), &((*info + i)->Time2[5]), &((*info + i)->Time2[6]),
			&((*info + i)->Time2[7]), &((*info + i)->Time2[8]), &((*info + i)->Time2[9]), &((*info + i)->Dist));		// чтение полей структуры
	fclose(fp);
	*n = num;
}

void PrintStruct_s1(struct s1* info, int n)										// вывод массива структур, хранящего информацию о всех городах
{
	printf("\nThe information about all cities:\n");
	printf("+----------------+-------+-------+----------+\n");
	printf("| %-14s | %-5s | %-5s | %-5s | \n", "City", "Time1", "Time2", "Distance");
	printf("+----------------+-------+-------+----------+\n");
	for (int i = 0; i < n; i++)													// цикл для вывода информации о всех городах
	{
		printf("| %-14s | %-5s | %-5s | %-8d | \n", info[i].City, info[i].Time1[0], info[i].Time2[0], info[i].Dist);
		for (int j = 1; j < t; j++)												// цикл для вывода массива времён
			printf("| \t\t | %-5s | %-5s | \t    | \n",info[i].Time1[j], info[i].Time2[j]);
		printf("+----------------+-------+-------+----------+\n");
	}
}

void PrintStruct_s2(struct s2* infoWay, int num)								// вывод структуры, хранящей информации о поездке пользователя
{
	if (num == 0)																// если пересадок нет, то форма вывода будет следующей
	{
		printf("+----------------+----------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-15s | %-5s  | %-9s | \n", "CityFrom", "TimeFrom", "CityTo", "TimeTo", "Distance");
		printf("+----------------+----------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-15s | %-7s | %-9d | \n", infoWay[0].CityFrom, infoWay[0].TimeFrom[0], infoWay[0].CityTo, infoWay[0].TimeTo[0], infoWay[0].Distance);
		for (int j = 1; j < t; j++)												// цикл для вывода массива времён
			printf("| \t\t | %-8s | \t\t      | %-7s | \t    | \n", infoWay[0].TimeFrom[j], infoWay[0].TimeTo[j]);
		printf("+----------------+----------+-----------------+---------+-----------+\n");
	}
	else if (num == 1)															// если пересадка 1 (одна), то форма вывода будет следующей
	{
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-14s | %-8s || %-8s | %-15s | %-6s  | %-9s | \n", "CityFrom", "TimeFrom", "Peresadka", "Time1", "Time2", "CityTo", "TimeTo", "Distance");
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-14s | %-8s || %-8s | %-15s | %-7s | %-9d | \n", infoWay[0].CityFrom, infoWay[0].TimeFrom[0], infoWay[0].Peresadki[0], infoWay[0].TimePeres1[0][0], infoWay[0].TimePeres2[0][0], infoWay[0].CityTo, infoWay[0].TimeTo[0], infoWay[0].Distance);
		for (int j = 1; j < t; j++)												// цикл для вывода массива времён
			printf("| \t\t | %-8s | \t\t     | %-8s || %-8s | \t\t      | %-7s | \t    | \n", infoWay[0].TimeFrom[j], infoWay[0].TimePeres1[0][j], infoWay[0].TimePeres2[0][j], infoWay[0].TimeTo[j]);
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------+-----------+\n");
	}
	else if (num == 2)															// если пересадок 2 (две), то форма вывода будет следующей
	{
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------++---------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-14s | %-8s || %-8s | %-15s | %-6s  || %-7s | %-15s | %-5s  | %-9s | \n", "CityFrom", "TimeFrom", "Peresadka1", "Time1", "Time2", "Peresadka2", "Time1", "Time2", "CityTo", "TimeTo", "Distance");
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------++---------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-14s | %-8s || %-8s | %-15s | %-7s || %-7s | %-15s | %-7s | %-9d | \n", infoWay[0].CityFrom, infoWay[0].TimeFrom[0], infoWay[0].Peresadki[0], infoWay[0].TimePeres1[0][0], infoWay[0].TimePeres2[0][0], infoWay[0].Peresadki[1], infoWay[0].TimePeres1[1][0], infoWay[0].TimePeres2[1][0], infoWay[0].CityTo, infoWay[0].TimeTo[0], infoWay[0].Distance);
		for (int j = 1; j < t; j++)												// цикл для вывода массива времён
			printf("| \t\t | %-8s | \t\t     | %-8s || %-8s | \t\t      | %-7s || %-7s | \t\t      | %-7s | \t   | \n", infoWay[0].TimeFrom[j], infoWay[0].TimePeres1[0][j], infoWay[0].TimePeres2[0][j], infoWay[0].TimePeres1[1][j], infoWay[0].TimePeres2[1][j], infoWay[0].TimeTo[j]);
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------++---------+-----------------+---------+-----------+\n");
	}
	else return;
}

int NumberOfStructs(FILE* fp)													// поиск кол-ва структур в файле
{
	int i = 0;
	char str[256];
	while (fgets(str, 256, fp) != NULL)											// считываем строки до тез пор, пока не дойдём до конца
		i++;
	return i;
}

int returnFunc()																// функция для возвращения пользовательского меню
{
	int choice;
	printf("\nEnter the any button to return the menu: ");
	scanf_s("%d", &choice);
	rewind(stdin);
	return 1;
}

struct s2* InitialMenu(int graph[V][V], struct s1* info, struct s2* infoWay, int n, int* num)					// пользовательское меню
{
	system("cls");
	printf("1.Enter information about the trip.\n");
	printf("2.Display information about all cities of the railway.\n");
	printf("3.Display information about your last trip.\n");
	printf("4.Save your trip way information in TXT file.\n");
	printf("5.Exit.\n");
	char* StrCityFrom = (char*)calloc(N, sizeof(char));							// объявление и выделение памяти для хранения названия города, из которого едет пользователь											
	char* StrCityTo = (char*)calloc(N, sizeof(char));							// объявление и выделение памяти для хранения названия города, в который пользователь едет
	int IndexFrom;																// индекс города, из которого едет пользователь, в массиве структур
	int IndexTo;																// индекс города, в который едет пользователь, в массиве структур
	int choice = getchar();														// выбор опции
	rewind(stdin);
	switch (choice)
	{
	case '1':																	// ввод информации о поездке
		system("cls");															// очитска консоли
		StrCityFrom = InputCityFrom(info);										// ввод названия города, из которого едет пользователь
		StrCityTo = InputCityTo(info);											// ввод названия города, в который едет пользователь
		strcpy(infoWay[0].CityFrom, StrCityFrom);								// сохранение названий городов в структуру, хранящую информацию о поездке
		strcpy(infoWay[0].CityTo, StrCityTo);
		IndexFrom = find_city_index(info, StrCityFrom);							// получение индекса города, из которого едет пользователь, в массиве структур
		IndexTo = find_city_index(info, StrCityTo);								// получение индекса города, в который едет пользователь, в массиве структур
		infoWay = dijkstra(graph, IndexFrom, IndexTo, info, infoWay, num);		// алгорит Дейкстры для получения информации о станциях пересадок, если такие есть, нахождение кратчайшего пути между станциями и сохранение данной информации в структуру
		returnFunc();															// возвращение в пользовательское меню
		infoWay = InitialMenu(graph, info, infoWay, n, num);					// вывод пользовательского меню и сохранение информации в структуру
		break;
	case '2':																	// вывод информации о всех городах
		system("cls");
		printf("The information about all cities:\n");
		PrintStruct_s1(info, n);												// вывод массива структур, хранящего информацию о всех городах
		returnFunc();
		infoWay = InitialMenu(graph, info, infoWay, n, num);
		break;
	case '3':																	// вывод информации о поездке
		system("cls");
		printf("The information about your trip:\n");
		if (infoWay[0].CityFrom == NULL)										// если в стрктуре отсутствует инофрмация о городе, из которого едет пользователь, то информции о поездке нет
		{
			printf("There is no information about your trip!\n");
			returnFunc();
			infoWay = InitialMenu(graph, info, infoWay, n, num);
			break;
		}
		else
			PrintStruct_s2(infoWay, *num);										// иначе вывод структуры, хранящей информацию о поездке пользователя
		returnFunc();
		infoWay = InitialMenu(graph, info, infoWay, n, num);
		break;
	case '4':																	// сохранение информации о поездке пользователя в текстовый файл
		system("cls");
		InputInformationInFileS2(infoWay, *num);										// запись структуры в текстовый файл
		printf("TXT file is successfuly created. Name of this file is result.txt.\n");
		returnFunc();
		infoWay = InitialMenu(graph, info, infoWay, n, num);
		break;
	case '5':																	// закончить выполнение программы
		system("cls");
		printf("Thank you fo using our service. Goodbye!");
		break;
	default:																	// при вводе другого варианта, выводится сообщение
		printf("There is no this option. Try again please!");
	}
	return infoWay;
}

int min_distance(int dist[], int visited[])										// функция для поиска индекса вершины с наименьшим расстоянием от стартовой вершины
{
	int min = INT_MAX, min_index;												// изначальное расстояние принимается за бесконечно большое число - min, 

	for (int i = 0; i < V; i++)													// цикл для прохождения по всем городам
	{
		if (visited[i] == 0 && dist[i] <= min) 
		{
			min = dist[i];
			min_index = i;														// запоминаем индекс элемента с минимальным расстоянием
		}
	}

	return min_index;
}

struct s2* dijkstra(int graph[V][V], int start, int end, struct s1* info, struct s2* infoWay, int* num)			// функция реализующая алгоритм Дейкстры с модификацией для учёта станций пересадок
{
	int dist[V];																// массив расстояний от стартовой вершины
	int visited[V];																// массив посещенных вершин
	int prev[V];																// массив предыдущих вершин на пути
	int number = -1;
	int numb = 0;
	for (int i = 0; i < V; i++)													// цикл для инициализации переменных для каждого города
	{
		dist[i] = INT_MAX;														// инициализация всех расстояний как "бесконечность"
		visited[i] = 0;															// отметка всех вершин как не посещённых
		prev[i] = -1;
	}
	dist[start] = 0;

	for (int i = 0; i < V - 1; i++)												// поиск кратчайшего пути для всех вершин графа
	{
		int u = min_distance(dist, visited);									// поиск вершины с наименьшей стоимостью среди вершин, ещё не включённых в кратчайший путь
		visited[u] = 1;															// отметка выбранной вершины как посещённой

		for (int v = 0; v < V; v++)												// обновление расстояний до смежных вершин, учитывая станции пересадок
		{
			if (visited[v] == 0 && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])	// Если вершина ещё не включена в кратчайший путь,
																											// есть ребро из выбранной вершины до смежной вершины,
																											// и расстояние от источника до выбранной вершины
																											// плюс стоимость ребра меньше текущего расстояния до смежной вершины,
			{
				dist[v] = dist[u] + graph[u][v];								// то обновляем расстояние до смежной вершины
				prev[v] = u;
			}
		}
	}

	if (dist[end] == INT_MAX)													// если расстояние до конечного города поездки равно "бесконечности", то путь не найден
	{
		printf("No path found.\n");
		exit(-1);
	}

	int current = end;															// текущее положение начинается с конечного города поездки
	//int index = 0;												
	int IndexTransfer;															// индекс города, где будет осуществленна ближайшая пересадка
	int nap;																	// направление
	int ind = prev[current];													// сохранение последовательности предыдущих вершин на пути
	int flag = 0;																// город не является пересадкой

	if (info[start].Line == 8 || info[start].Line == 7 || info[end].Line == 8 || info[end].Line == 7)		// если начальный или конечный город является городом-пересадкой,то
		flag = 1;																// обозначаем это

	while (prev[current] != -1)													// пока не пройдём всю последовательность предыдущих вершин на маршруте
	{
		if (info[current].Line != info[prev[current]].Line)						// если линии разные, то 
			number = number + 1;												// +1 к кол-ву пересадок на маршруте

		current = prev[current];												// становимся на предыдущиую вершину на маршруте
	}

	numb = number;																// сохраняем кол-во пересадок на маршруте
	prev[current] = ind;														// возвращаем последовательнось предыдущих вершин на пути
	if (number > 0)																// если пересадки есть, то 
	{
		while (prev[current] != -1)												// снова проходим по всей последовательности предыдущих вершин на маршруте
		{
			if (info[current].Line != info[prev[current]].Line)					// если линии разные, то
			{
				strcpy(infoWay[0].Peresadki[numb - 1], info[prev[current]].City);	// сохраняем название города, как город-пересадку
				numb = numb - 1;												// уменьшаем кол-во пресадок
				if (numb == 0)													// если кол-во пересадок == 0, то заканчиваем цикл
					break;
			}
			current = prev[current];											// становимся на предыдущую вершину на маршруте
		}
	}
	printf("\n");
	IndexTransfer = find_city_index(info, infoWay[0].Peresadki[0]);				// получаем индекс ближайшей пересадки
	nap = napravl(info, start, IndexTransfer, end, number);						// определяем напрваление (если nap == 1, то поездке от центра, если == 0, то к центру)
	infoWay = GetTime(info, infoWay, start, end, nap, number);					// считываем нужные времена отбытия и прибытия
	infoWay = GetTimeOfPeresadki(info, infoWay, nap, number);					// считываем нужные времена прибытия и отбытия со станций пересадок
	infoWay[0].Distance = dist[end];											// сохраняем расстояние между начальным и конечным городами
	*num = number;																// сохраняем кол-во пересадок
	return infoWay;
}

int find_city_index(struct s1* info, char* name)								// функция для получения индекса города 
{
	for (int i = 0; i < V; i++)													// цикл для прохождения по всем городам массива структур
	{
		if (strcmp(info[i].City, name) == 0)									// если есть совпадение, то возвращаем i, то есть индекс данного города в массиве структур
			return i;
	}
	return -1;																	// иначе возвращаем -1
}

int napravl(struct s1* info, int index1, int index2, int end, int num)			// определение напрваления поездки ( от центра или к центру) для чтения необходимых масивов времён
{
	int dist1 = info[index1].Dist;												// первое расстояние принимаем равным расстоянию города, из которого едет пользователь
	int dist2;																	// второе расстояние
	int napravl;
	if (num == 0)																// если станций пересадок нет, то...																						
		dist2 = info[end].Dist;													// второе расстояние принимаем равным расстоянию города, в который едет пользователь
	else																		// если станции пересадок есть, то...
		dist2 = info[index2].Dist;												// второе расстояни принимаем равным расстоянию города, в котором осуществляется ближайшая пересадка с начала поездки

	if ((dist1 - dist2) < 0)													// если разность данных расстояний < 0, то 
		napravl = 1;															// поездка от центра
	else
		napravl = 0;															// поездка к центру
	return napravl;
}

struct s2* GetTime(struct s1* info, struct s2* infoWay, int indexFrom, int indexTo, int napravl, int num)					// функция сохранения нужных времён прибытия и отбытия 
{
	if (napravl == 0)															// ЕСЛИ поездке к центру, то
	{
		if (num == 0)															// если кол-во пересадок == 0, то
		{
			for (int i = 0; i < t; i++)											// цикл для чтения массива времён
			{
				strcpy(infoWay[0].TimeFrom[i], info[indexFrom].Time2[i]);		// считываем время отбытия из начального города
				strcpy(infoWay[0].TimeTo[i], info[indexTo].Time2[i]);			// считываем время прибытия в конечный город
			}
		}
		else																	// иначе
		{
			for (int i = 0; i < t; i++)											// цикл для чтения массива времён
			{
				strcpy(infoWay[0].TimeFrom[i], info[indexFrom].Time2[i]);		// считываем время отбытия из начального города 
				strcpy(infoWay[0].TimeTo[i], info[indexTo].Time1[i]);			// считываем время прибытия в конечный город учитывая пересдку
			}
		}
	}
	else																		// ИНАЧЕ (поездка от центра), то
	{
		if (num == 0)															// если кол-во пересадок == 0, то
		{
			for (int i = 0; i < t; i++)											// цикл для чтения массива времён
			{
				strcpy(infoWay[0].TimeFrom[i], info[indexFrom].Time1[i]);		// считываем время отбытия из начального города
				strcpy(infoWay[0].TimeTo[i], info[indexTo].Time1[i]);			// считываем время прибытия в конечный город
			}
		}
		else																	// иначе
		{
			for (int i = 0; i < t; i++)											
			{
				strcpy(infoWay[0].TimeFrom[i], info[indexFrom].Time1[i]);		// считываем время отбытия из начального города учитывая пересадку
				strcpy(infoWay[0].TimeTo[i], info[indexTo].Time2[i]);			// считываем время прибытия в конечный город 
			}
		}
	}
	return infoWay;
}

struct s2* GetTimeOfPeresadki(struct s1* info, struct s2* infoWay, int napravl, int number)									// функция сохранения нужных времён прибытия и отбытия станций пересадок	
{
	if (napravl == 0)																										// ЕСЛИ поездке к центру, то
	{
		for (int j = 0; j < number; j++)																					// цикл для прохождения по всем городам-пересадкам
			for (int i = 0; i < t; i++)																						// цикл для чтения массива времён
			{
				if ((j == 1) && strcmp(info[0].City, infoWay[0].Peresadki[j]) == 0)											// если второй пересадкой является Минск, то
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);		// считываем время прибытия в город-пересадку
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time1[i]);		// считываем время отбытия из города-пересадки
				}
				else if (j == 1)																							
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time1[i]);		// считываем нужное время прибытия в город-пересадку
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time1[i]);		// считываем нужное время отбытия из города-пересадки
				}
				else if ((j == 0) && strcmp(info[8].City, infoWay[0].Peresadki[j]) == 0)									// если первой пересадкой является город Орша, то 
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);		// считываем время прибытия в город-пересадку
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);		// считываем время отбытия из города-пересадки
				}
				else
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);		// считываем время прибытия в город-пересадку
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time1[i]);		// считываем время отбытия из города-пересадки
				}
			}
	}
	else																													// ИНАЧЕ (поездка от центра), то
	{
		for (int j = 0; j < number; j++)
			for (int i = 0; i < t; i++)
			{
				if ((j == 1) && strcmp(info[0].City, infoWay[0].Peresadki[j]) == 0)
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time1[i]);
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time1[i]);
				}
				else if (j == 1)
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);
				}
				else if ((j == 0) && strcmp(info[8].City, infoWay[0].Peresadki[j]) == 0)
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);
				}
				else
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time1[i]);
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);
				}
			}
	}

	return infoWay;
}