#include "functions.h"

//void InputInfoInStruct(struct s1** info)										// ���� ���������� � ������ ��������, �������� ���������� � ���� �������
//{
//	struct s1* inf;
//	inf = (struct s1*)calloc(V, sizeof(struct s1));								// ���������� � ������������� ������� �������� �� V �������
//	if (inf == NULL)															// �������� �� ��������� ������
//	{
//		printf("\nNo memory has been allocated for the array!\n");
//		return;
//	}
//
//	for (int i = 0; i < V; i++)													// ���� ��� ����� ���������� � V �������
//	{
//		rewind(stdin);
//		printf("\nEnter the information about %d city.", i + 1);
//
//		printf("\nEnter the name of the city: ");
//		fgets(inf[i].City, N, stdin);
//		DelEnter(inf[i].City);													// �������� \n � ����� ������
//		rewind(stdin);
//
//		printf("Enter line: ");
//		scanf_s("%d", &inf[i].Line);
//		while (inf[i].Line < 0)													// �������� �������� ����������
//		{
//			rewind(stdin);
//			printf("\nERROR! You have entered the wrong data!\nTry again please.\nYour choice is ");
//			scanf_s("%d", &inf[i].Dist);
//		}
//		rewind(stdin);
//
//		printf("Enter the departure time: ");
//		for (int j = 0; j < t; j++)												// ���� ��� ����� t ����� �����������
//		{
//			fgets(inf[i].Time1[j], N, stdin);
//			DelEnter(inf[i].Time1[j]);
//			rewind(stdin);
//		}
//		rewind(stdin);
//
//		printf("Enter the Time2: ");
//		for (int j = 0; j < t; j++)												// ���� ��� ����� t ����� ��������
//		{
//			fgets(inf[i].Time2[j], N, stdin);
//			DelEnter(inf[i].Time2[j]);
//			rewind(stdin);
//		}
//		rewind(stdin);
//
//		printf("Dist ");
//		scanf_s("%d", &inf[i].Dist);
//		while (inf[i].Dist < 0)													// �������� �������� ����������
//		{
//			rewind(stdin);
//			printf("\nERROR! You have entered the wrong data!\nTry again please.\nYour choice is ");
//			scanf_s("%d", &inf[i].Dist);
//		}
//		rewind(stdin);
//	}
//	*info = inf;																// ���������� ������� ��������
//}

//char* NameOfTheFile()
//{
//	char* name = (char*)calloc(N, sizeof(char));
//	printf("Enter the name of the file, you would like to save information about your trip in: ");
//	fgets(name, N, stdin);
//	DelEnter(name);													// �������� \n � ����� ������
//	rewind(stdin);
//	return name;
//}

//void InputInformationInFileS1(struct s1* info)									// ������ ������� �������� � ��������� ���� f.txt
//{
//	FILE* fp = fopen("f.txt", "w");
//	CheckFile(fp);
//	for (int i = 0; i < V; i++)													// ���� ��� ������ ������� �������� � ��������� ���� f.txt 
//	{
//		fprintf(fp, "%s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d", info[i].City, info[i].Line, info[i].Time1[0], info[i].Time1[1], info[i].Time1[2],
//			info[i].Time1[3], info[i].Time1[4], info[i].Time1[5], info[i].Time1[6], info[i].Time1[7], info[i].Time1[8], info[i].Time1[9], info[i].Time2[0], info[i].Time2[1],
//			info[i].Time2[2], info[i].Time2[3], info[i].Time2[4], info[i].Time2[5], info[i].Time2[6], info[i].Time2[7], info[i].Time2[8], info[i].Time2[9], info[i].Dist);
//		fprintf(fp, "\n");
//	}
//	fclose(fp);
//}

void InputInformationInFileS2(struct s2* infoWay, int num)						// ������ ������� �������� � ��������� ���� result.txt
{
	FILE* fp = fopen("result.txt", "w");
	CheckFile(fp);
	if (num == 0)																// ���� �� �������� ��� ���������, �� ������ � ���� ����� ����� ��������� ���
	{
		fprintf(fp, "%s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s -> %d", infoWay[0].CityFrom, infoWay[0].TimeFrom[0], infoWay[0].TimeFrom[1], infoWay[0].TimeFrom[2],
			infoWay[0].TimeFrom[3], infoWay[0].TimeFrom[4], infoWay[0].TimeFrom[5], infoWay[0].TimeFrom[6], infoWay[0].TimeFrom[7], infoWay[0].TimeFrom[8], infoWay[0].TimeFrom[9], infoWay[0].CityTo, infoWay[0].TimeTo[0], infoWay[0].TimeTo[1],
			infoWay[0].TimeTo[2], infoWay[0].TimeTo[3], infoWay[0].TimeTo[4], infoWay[0].TimeTo[5], infoWay[0].TimeTo[6], infoWay[0].TimeTo[7], infoWay[0].TimeTo[8], infoWay[0].TimeTo[9], infoWay[0].Distance);
	}
	else if (num == 1)															// ���� �� �������� ���� 1 (����) ���������, �� ������ � ���� ����� ����� ��������� ���
	{
		fprintf(fp, "%s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s ->\n-> %s %s %s %s %s %s %s %s %s %s %s -> %d", infoWay[0].CityFrom, infoWay[0].TimeFrom[0], infoWay[0].TimeFrom[1], infoWay[0].TimeFrom[2],
			infoWay[0].TimeFrom[3], infoWay[0].TimeFrom[4], infoWay[0].TimeFrom[5], infoWay[0].TimeFrom[6], infoWay[0].TimeFrom[7], infoWay[0].TimeFrom[8], infoWay[0].TimeFrom[9], infoWay[0].Peresadki[0],
			infoWay[0].TimePeres1[0][0], infoWay[0].TimePeres1[0][1], infoWay[0].TimePeres1[0][2], infoWay[0].TimePeres1[0][3], infoWay[0].TimePeres1[0][4], infoWay[0].TimePeres1[0][5], infoWay[0].TimePeres1[0][6],
			infoWay[0].TimePeres1[0][7], infoWay[0].TimePeres1[0][8], infoWay[0].TimePeres1[0][9], infoWay[0].Peresadki[0], infoWay[0].TimePeres2[0][0], infoWay[0].TimePeres2[0][1], infoWay[0].TimePeres2[0][2],
			infoWay[0].TimePeres2[0][3], infoWay[0].TimePeres2[0][4], infoWay[0].TimePeres2[0][5], infoWay[0].TimePeres2[0][6], infoWay[0].TimePeres2[0][7], infoWay[0].TimePeres2[0][8], infoWay[0].TimePeres2[0][9],
			infoWay[0].CityTo, infoWay[0].TimeTo[0], infoWay[0].TimeTo[1], infoWay[0].TimeTo[2], infoWay[0].TimeTo[3], infoWay[0].TimeTo[4], infoWay[0].TimeTo[5], infoWay[0].TimeTo[6], infoWay[0].TimeTo[7],
			infoWay[0].TimeTo[8], infoWay[0].TimeTo[9], infoWay[0].Distance);
	}
	else																		// ���� �� �������� ����� 1 (�����) ���������, �� ������ � ���� ����� ����� ��������� ���
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

int CheckCity(struct s1* info,char* str)										// ��������, ���� �� �������� ����� � ������� ��������
{
	int flag = 0;																// ����� ���������� ������ ��� � ������� ��������
	for (int i = 0; i < V; i++)													// ���� ��� ������� �� ���� ��������� (�������) ������� ��������
		if (strcmp(info[i].City, str) == 0)
			flag = 1;															// ���� �������� ����� ������ � ������� �� ������� ��������, �� flag = 1
	if (flag == 0)
		printf("\nThere is no this city. Try again please!");
	return flag;
}

char* InputCityTo(struct s1* info)												// ���� �������� ������ (���������� ������), � ������� ������������ ����
{
	int flag;																	// ���� �� �������� ����� � ������� ��������
	char* StrCityTo;
	do
	{
		rewind(stdin);
		flag = 0;
		printf("\nEnter the city, where you are going: ");
		StrCityTo = (char*)calloc(N, sizeof(char));								// ��������� ������������ ������ ��� ����� �������� ������
		fgets(StrCityTo, N, stdin);
		DelEnter(StrCityTo);
		flag = CheckCity(info, StrCityTo);										// ��������, ���� �� �������� ����� � ������� ��������
	} while (!flag);															// ���� ������� ������ ���, �� ������������ ������ ����� �����
	
	return StrCityTo;
}

char* InputCityFrom(struct s1* info)											// ���� �������� ������ (���������� ������), �� �������� ���� ������������
{
	int flag;																	// ���� �� �������� ����� � ������� ��������
	char* StrCityFrom;
	do
	{
		rewind(stdin);
		flag = 0;
		printf("\nEnter the city, where you are coming from: ");
		StrCityFrom = (char*)calloc(N, sizeof(char));							// ��������� ������������ ������ ��� ����� �������� ������
		fgets(StrCityFrom, N, stdin);
		DelEnter(StrCityFrom);
		flag = CheckCity(info, StrCityFrom);									// ��������, ���� �� �������� ����� � ������� ��������
	} while (!flag);															// ���� ������� ������ ���, �� ������������ ������ ����� �����

	return StrCityFrom;
}

void CheckFile(FILE* fp)														// ������� ��� �������� �������� �����
{
	if (fp == NULL)																// �������� �������� �����
	{
		printf("ERROR");
		return;
	}
}

void DelEnter(char str[])														// �������� \n ��� ����� ���������� 
{
	int l = strlen(str);
	str[l - 1] = '\0';
}

void ReadInfoFromFile1(struct s1** info, int* n)								// ������ ���������� � ���� ������� � ������ �������� info
{
	FILE* fp = fopen("f.txt", "r");
	CheckFile(fp);
	int num = NumberOfStructs(fp);												// ����� ���-�� �������� � �����
	*info = (struct s1*)calloc(num , sizeof(struct s1));						// ��������� ������������ ������ ��� ������� ��������
	fseek(fp, 0, SEEK_SET);														// ������������� ������ �� ������ ����� f.txt

	for (int i = 0; i < num; i++)												// ���� ��� ������ ���������� � num ������� � ������ �������� �� ����� f.txt 
		fscanf(fp, "%s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d", &((*info + i)->City), &((*info + i)->Line), &((*info + i)->Time1[0]), &((*info + i)->Time1[1]), &((*info + i)->Time1[2]),
			&((*info + i)->Time1[3]), &((*info + i)->Time1[4]), &((*info + i)->Time1[5]), &((*info + i)->Time1[6]), &((*info + i)->Time1[7]), &((*info + i)->Time1[8]), &((*info + i)->Time1[9]),
			&((*info + i)->Time2[0]), &((*info + i)->Time2[1]), &((*info + i)->Time2[2]), &((*info + i)->Time2[3]), &((*info + i)->Time2[4]), &((*info + i)->Time2[5]), &((*info + i)->Time2[6]),
			&((*info + i)->Time2[7]), &((*info + i)->Time2[8]), &((*info + i)->Time2[9]), &((*info + i)->Dist));		// ������ ����� ���������
	fclose(fp);
	*n = num;
}

void PrintStruct_s1(struct s1* info, int n)										// ����� ������� ��������, ��������� ���������� � ���� �������
{
	printf("\nThe information about all cities:\n");
	printf("+----------------+-------+-------+----------+\n");
	printf("| %-14s | %-5s | %-5s | %-5s | \n", "City", "Time1", "Time2", "Distance");
	printf("+----------------+-------+-------+----------+\n");
	for (int i = 0; i < n; i++)													// ���� ��� ������ ���������� � ���� �������
	{
		printf("| %-14s | %-5s | %-5s | %-8d | \n", info[i].City, info[i].Time1[0], info[i].Time2[0], info[i].Dist);
		for (int j = 1; j < t; j++)												// ���� ��� ������ ������� �����
			printf("| \t\t | %-5s | %-5s | \t    | \n",info[i].Time1[j], info[i].Time2[j]);
		printf("+----------------+-------+-------+----------+\n");
	}
}

void PrintStruct_s2(struct s2* infoWay, int num)								// ����� ���������, �������� ���������� � ������� ������������
{
	if (num == 0)																// ���� ��������� ���, �� ����� ������ ����� ���������
	{
		printf("+----------------+----------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-15s | %-5s  | %-9s | \n", "CityFrom", "TimeFrom", "CityTo", "TimeTo", "Distance");
		printf("+----------------+----------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-15s | %-7s | %-9d | \n", infoWay[0].CityFrom, infoWay[0].TimeFrom[0], infoWay[0].CityTo, infoWay[0].TimeTo[0], infoWay[0].Distance);
		for (int j = 1; j < t; j++)												// ���� ��� ������ ������� �����
			printf("| \t\t | %-8s | \t\t      | %-7s | \t    | \n", infoWay[0].TimeFrom[j], infoWay[0].TimeTo[j]);
		printf("+----------------+----------+-----------------+---------+-----------+\n");
	}
	else if (num == 1)															// ���� ��������� 1 (����), �� ����� ������ ����� ���������
	{
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-14s | %-8s || %-8s | %-15s | %-6s  | %-9s | \n", "CityFrom", "TimeFrom", "Peresadka", "Time1", "Time2", "CityTo", "TimeTo", "Distance");
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-14s | %-8s || %-8s | %-15s | %-7s | %-9d | \n", infoWay[0].CityFrom, infoWay[0].TimeFrom[0], infoWay[0].Peresadki[0], infoWay[0].TimePeres1[0][0], infoWay[0].TimePeres2[0][0], infoWay[0].CityTo, infoWay[0].TimeTo[0], infoWay[0].Distance);
		for (int j = 1; j < t; j++)												// ���� ��� ������ ������� �����
			printf("| \t\t | %-8s | \t\t     | %-8s || %-8s | \t\t      | %-7s | \t    | \n", infoWay[0].TimeFrom[j], infoWay[0].TimePeres1[0][j], infoWay[0].TimePeres2[0][j], infoWay[0].TimeTo[j]);
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------+-----------+\n");
	}
	else if (num == 2)															// ���� ��������� 2 (���), �� ����� ������ ����� ���������
	{
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------++---------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-14s | %-8s || %-8s | %-15s | %-6s  || %-7s | %-15s | %-5s  | %-9s | \n", "CityFrom", "TimeFrom", "Peresadka1", "Time1", "Time2", "Peresadka2", "Time1", "Time2", "CityTo", "TimeTo", "Distance");
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------++---------+-----------------+---------+-----------+\n");
		printf("| %-14s | %-8s | %-14s | %-8s || %-8s | %-15s | %-7s || %-7s | %-15s | %-7s | %-9d | \n", infoWay[0].CityFrom, infoWay[0].TimeFrom[0], infoWay[0].Peresadki[0], infoWay[0].TimePeres1[0][0], infoWay[0].TimePeres2[0][0], infoWay[0].Peresadki[1], infoWay[0].TimePeres1[1][0], infoWay[0].TimePeres2[1][0], infoWay[0].CityTo, infoWay[0].TimeTo[0], infoWay[0].Distance);
		for (int j = 1; j < t; j++)												// ���� ��� ������ ������� �����
			printf("| \t\t | %-8s | \t\t     | %-8s || %-8s | \t\t      | %-7s || %-7s | \t\t      | %-7s | \t   | \n", infoWay[0].TimeFrom[j], infoWay[0].TimePeres1[0][j], infoWay[0].TimePeres2[0][j], infoWay[0].TimePeres1[1][j], infoWay[0].TimePeres2[1][j], infoWay[0].TimeTo[j]);
		printf("+----------------+----------+----------------+----------++----------+-----------------+---------++---------+-----------------+---------+-----------+\n");
	}
	else return;
}

int NumberOfStructs(FILE* fp)													// ����� ���-�� �������� � �����
{
	int i = 0;
	char str[256];
	while (fgets(str, 256, fp) != NULL)											// ��������� ������ �� ��� ���, ���� �� ����� �� �����
		i++;
	return i;
}

int returnFunc()																// ������� ��� ����������� ����������������� ����
{
	int choice;
	printf("\nEnter the any button to return the menu: ");
	scanf_s("%d", &choice);
	rewind(stdin);
	return 1;
}

struct s2* InitialMenu(int graph[V][V], struct s1* info, struct s2* infoWay, int n, int* num)					// ���������������� ����
{
	system("cls");
	printf("1.Enter information about the trip.\n");
	printf("2.Display information about all cities of the railway.\n");
	printf("3.Display information about your last trip.\n");
	printf("4.Save your trip way information in TXT file.\n");
	printf("5.Exit.\n");
	char* StrCityFrom = (char*)calloc(N, sizeof(char));							// ���������� � ��������� ������ ��� �������� �������� ������, �� �������� ���� ������������											
	char* StrCityTo = (char*)calloc(N, sizeof(char));							// ���������� � ��������� ������ ��� �������� �������� ������, � ������� ������������ ����
	int IndexFrom;																// ������ ������, �� �������� ���� ������������, � ������� ��������
	int IndexTo;																// ������ ������, � ������� ���� ������������, � ������� ��������
	int choice = getchar();														// ����� �����
	rewind(stdin);
	switch (choice)
	{
	case '1':																	// ���� ���������� � �������
		system("cls");															// ������� �������
		StrCityFrom = InputCityFrom(info);										// ���� �������� ������, �� �������� ���� ������������
		StrCityTo = InputCityTo(info);											// ���� �������� ������, � ������� ���� ������������
		strcpy(infoWay[0].CityFrom, StrCityFrom);								// ���������� �������� ������� � ���������, �������� ���������� � �������
		strcpy(infoWay[0].CityTo, StrCityTo);
		IndexFrom = find_city_index(info, StrCityFrom);							// ��������� ������� ������, �� �������� ���� ������������, � ������� ��������
		IndexTo = find_city_index(info, StrCityTo);								// ��������� ������� ������, � ������� ���� ������������, � ������� ��������
		infoWay = dijkstra(graph, IndexFrom, IndexTo, info, infoWay, num);		// ������� �������� ��� ��������� ���������� � �������� ���������, ���� ����� ����, ���������� ����������� ���� ����� ��������� � ���������� ������ ���������� � ���������
		returnFunc();															// ����������� � ���������������� ����
		infoWay = InitialMenu(graph, info, infoWay, n, num);					// ����� ����������������� ���� � ���������� ���������� � ���������
		break;
	case '2':																	// ����� ���������� � ���� �������
		system("cls");
		printf("The information about all cities:\n");
		PrintStruct_s1(info, n);												// ����� ������� ��������, ��������� ���������� � ���� �������
		returnFunc();
		infoWay = InitialMenu(graph, info, infoWay, n, num);
		break;
	case '3':																	// ����� ���������� � �������
		system("cls");
		printf("The information about your trip:\n");
		if (infoWay[0].CityFrom == NULL)										// ���� � �������� ����������� ���������� � ������, �� �������� ���� ������������, �� ��������� � ������� ���
		{
			printf("There is no information about your trip!\n");
			returnFunc();
			infoWay = InitialMenu(graph, info, infoWay, n, num);
			break;
		}
		else
			PrintStruct_s2(infoWay, *num);										// ����� ����� ���������, �������� ���������� � ������� ������������
		returnFunc();
		infoWay = InitialMenu(graph, info, infoWay, n, num);
		break;
	case '4':																	// ���������� ���������� � ������� ������������ � ��������� ����
		system("cls");
		InputInformationInFileS2(infoWay, *num);										// ������ ��������� � ��������� ����
		printf("TXT file is successfuly created. Name of this file is result.txt.\n");
		returnFunc();
		infoWay = InitialMenu(graph, info, infoWay, n, num);
		break;
	case '5':																	// ��������� ���������� ���������
		system("cls");
		printf("Thank you fo using our service. Goodbye!");
		break;
	default:																	// ��� ����� ������� ��������, ��������� ���������
		printf("There is no this option. Try again please!");
	}
	return infoWay;
}

int min_distance(int dist[], int visited[])										// ������� ��� ������ ������� ������� � ���������� ����������� �� ��������� �������
{
	int min = INT_MAX, min_index;												// ����������� ���������� ����������� �� ���������� ������� ����� - min, 

	for (int i = 0; i < V; i++)													// ���� ��� ����������� �� ���� �������
	{
		if (visited[i] == 0 && dist[i] <= min) 
		{
			min = dist[i];
			min_index = i;														// ���������� ������ �������� � ����������� �����������
		}
	}

	return min_index;
}

struct s2* dijkstra(int graph[V][V], int start, int end, struct s1* info, struct s2* infoWay, int* num)			// ������� ����������� �������� �������� � ������������ ��� ����� ������� ���������
{
	int dist[V];																// ������ ���������� �� ��������� �������
	int visited[V];																// ������ ���������� ������
	int prev[V];																// ������ ���������� ������ �� ����
	int number = -1;
	int numb = 0;
	for (int i = 0; i < V; i++)													// ���� ��� ������������� ���������� ��� ������� ������
	{
		dist[i] = INT_MAX;														// ������������� ���� ���������� ��� "�������������"
		visited[i] = 0;															// ������� ���� ������ ��� �� ����������
		prev[i] = -1;
	}
	dist[start] = 0;

	for (int i = 0; i < V - 1; i++)												// ����� ����������� ���� ��� ���� ������ �����
	{
		int u = min_distance(dist, visited);									// ����� ������� � ���������� ���������� ����� ������, ��� �� ���������� � ���������� ����
		visited[u] = 1;															// ������� ��������� ������� ��� ����������

		for (int v = 0; v < V; v++)												// ���������� ���������� �� ������� ������, �������� ������� ���������
		{
			if (visited[v] == 0 && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])	// ���� ������� ��� �� �������� � ���������� ����,
																											// ���� ����� �� ��������� ������� �� ������� �������,
																											// � ���������� �� ��������� �� ��������� �������
																											// ���� ��������� ����� ������ �������� ���������� �� ������� �������,
			{
				dist[v] = dist[u] + graph[u][v];								// �� ��������� ���������� �� ������� �������
				prev[v] = u;
			}
		}
	}

	if (dist[end] == INT_MAX)													// ���� ���������� �� ��������� ������ ������� ����� "�������������", �� ���� �� ������
	{
		printf("No path found.\n");
		exit(-1);
	}

	int current = end;															// ������� ��������� ���������� � ��������� ������ �������
	//int index = 0;												
	int IndexTransfer;															// ������ ������, ��� ����� ������������� ��������� ���������
	int nap;																	// �����������
	int ind = prev[current];													// ���������� ������������������ ���������� ������ �� ����
	int flag = 0;																// ����� �� �������� ����������

	if (info[start].Line == 8 || info[start].Line == 7 || info[end].Line == 8 || info[end].Line == 7)		// ���� ��������� ��� �������� ����� �������� �������-����������,��
		flag = 1;																// ���������� ���

	while (prev[current] != -1)													// ���� �� ������ ��� ������������������ ���������� ������ �� ��������
	{
		if (info[current].Line != info[prev[current]].Line)						// ���� ����� ������, �� 
			number = number + 1;												// +1 � ���-�� ��������� �� ��������

		current = prev[current];												// ���������� �� ����������� ������� �� ��������
	}

	numb = number;																// ��������� ���-�� ��������� �� ��������
	prev[current] = ind;														// ���������� ����������������� ���������� ������ �� ����
	if (number > 0)																// ���� ��������� ����, �� 
	{
		while (prev[current] != -1)												// ����� �������� �� ���� ������������������ ���������� ������ �� ��������
		{
			if (info[current].Line != info[prev[current]].Line)					// ���� ����� ������, ��
			{
				strcpy(infoWay[0].Peresadki[numb - 1], info[prev[current]].City);	// ��������� �������� ������, ��� �����-���������
				numb = numb - 1;												// ��������� ���-�� ��������
				if (numb == 0)													// ���� ���-�� ��������� == 0, �� ����������� ����
					break;
			}
			current = prev[current];											// ���������� �� ���������� ������� �� ��������
		}
	}
	printf("\n");
	IndexTransfer = find_city_index(info, infoWay[0].Peresadki[0]);				// �������� ������ ��������� ���������
	nap = napravl(info, start, IndexTransfer, end, number);						// ���������� ����������� (���� nap == 1, �� ������� �� ������, ���� == 0, �� � ������)
	infoWay = GetTime(info, infoWay, start, end, nap, number);					// ��������� ������ ������� ������� � ��������
	infoWay = GetTimeOfPeresadki(info, infoWay, nap, number);					// ��������� ������ ������� �������� � ������� �� ������� ���������
	infoWay[0].Distance = dist[end];											// ��������� ���������� ����� ��������� � �������� ��������
	*num = number;																// ��������� ���-�� ���������
	return infoWay;
}

int find_city_index(struct s1* info, char* name)								// ������� ��� ��������� ������� ������ 
{
	for (int i = 0; i < V; i++)													// ���� ��� ����������� �� ���� ������� ������� ��������
	{
		if (strcmp(info[i].City, name) == 0)									// ���� ���� ����������, �� ���������� i, �� ���� ������ ������� ������ � ������� ��������
			return i;
	}
	return -1;																	// ����� ���������� -1
}

int napravl(struct s1* info, int index1, int index2, int end, int num)			// ����������� ����������� ������� ( �� ������ ��� � ������) ��� ������ ����������� ������� �����
{
	int dist1 = info[index1].Dist;												// ������ ���������� ��������� ������ ���������� ������, �� �������� ���� ������������
	int dist2;																	// ������ ����������
	int napravl;
	if (num == 0)																// ���� ������� ��������� ���, ��...																						
		dist2 = info[end].Dist;													// ������ ���������� ��������� ������ ���������� ������, � ������� ���� ������������
	else																		// ���� ������� ��������� ����, ��...
		dist2 = info[index2].Dist;												// ������ ��������� ��������� ������ ���������� ������, � ������� �������������� ��������� ��������� � ������ �������

	if ((dist1 - dist2) < 0)													// ���� �������� ������ ���������� < 0, �� 
		napravl = 1;															// ������� �� ������
	else
		napravl = 0;															// ������� � ������
	return napravl;
}

struct s2* GetTime(struct s1* info, struct s2* infoWay, int indexFrom, int indexTo, int napravl, int num)					// ������� ���������� ������ ����� �������� � ������� 
{
	if (napravl == 0)															// ���� ������� � ������, ��
	{
		if (num == 0)															// ���� ���-�� ��������� == 0, ��
		{
			for (int i = 0; i < t; i++)											// ���� ��� ������ ������� �����
			{
				strcpy(infoWay[0].TimeFrom[i], info[indexFrom].Time2[i]);		// ��������� ����� ������� �� ���������� ������
				strcpy(infoWay[0].TimeTo[i], info[indexTo].Time2[i]);			// ��������� ����� �������� � �������� �����
			}
		}
		else																	// �����
		{
			for (int i = 0; i < t; i++)											// ���� ��� ������ ������� �����
			{
				strcpy(infoWay[0].TimeFrom[i], info[indexFrom].Time2[i]);		// ��������� ����� ������� �� ���������� ������ 
				strcpy(infoWay[0].TimeTo[i], info[indexTo].Time1[i]);			// ��������� ����� �������� � �������� ����� �������� ��������
			}
		}
	}
	else																		// ����� (������� �� ������), ��
	{
		if (num == 0)															// ���� ���-�� ��������� == 0, ��
		{
			for (int i = 0; i < t; i++)											// ���� ��� ������ ������� �����
			{
				strcpy(infoWay[0].TimeFrom[i], info[indexFrom].Time1[i]);		// ��������� ����� ������� �� ���������� ������
				strcpy(infoWay[0].TimeTo[i], info[indexTo].Time1[i]);			// ��������� ����� �������� � �������� �����
			}
		}
		else																	// �����
		{
			for (int i = 0; i < t; i++)											
			{
				strcpy(infoWay[0].TimeFrom[i], info[indexFrom].Time1[i]);		// ��������� ����� ������� �� ���������� ������ �������� ���������
				strcpy(infoWay[0].TimeTo[i], info[indexTo].Time2[i]);			// ��������� ����� �������� � �������� ����� 
			}
		}
	}
	return infoWay;
}

struct s2* GetTimeOfPeresadki(struct s1* info, struct s2* infoWay, int napravl, int number)									// ������� ���������� ������ ����� �������� � ������� ������� ���������	
{
	if (napravl == 0)																										// ���� ������� � ������, ��
	{
		for (int j = 0; j < number; j++)																					// ���� ��� ����������� �� ���� �������-����������
			for (int i = 0; i < t; i++)																						// ���� ��� ������ ������� �����
			{
				if ((j == 1) && strcmp(info[0].City, infoWay[0].Peresadki[j]) == 0)											// ���� ������ ���������� �������� �����, ��
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);		// ��������� ����� �������� � �����-���������
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time1[i]);		// ��������� ����� ������� �� ������-���������
				}
				else if (j == 1)																							
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time1[i]);		// ��������� ������ ����� �������� � �����-���������
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time1[i]);		// ��������� ������ ����� ������� �� ������-���������
				}
				else if ((j == 0) && strcmp(info[8].City, infoWay[0].Peresadki[j]) == 0)									// ���� ������ ���������� �������� ����� ����, �� 
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);		// ��������� ����� �������� � �����-���������
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);		// ��������� ����� ������� �� ������-���������
				}
				else
				{
					strcpy(infoWay[0].TimePeres1[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time2[i]);		// ��������� ����� �������� � �����-���������
					strcpy(infoWay[0].TimePeres2[j][i], info[find_city_index(info, infoWay[0].Peresadki[j])].Time1[i]);		// ��������� ����� ������� �� ������-���������
				}
			}
	}
	else																													// ����� (������� �� ������), ��
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