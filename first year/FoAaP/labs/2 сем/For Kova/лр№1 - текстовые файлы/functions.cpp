#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ChoiceOption()																// ����� ��������
{
	int cho;
	printf("1. Use ready files.\n");
	printf("2. Create new files.\n");
	printf("Your choice is: ");
	scanf_s(" %d", &cho);
	while (cho > 2 || cho < 1)													// �������� �� ����
	{
		rewind(stdin);
		printf("The number of this option does not exist!\n");
		printf("Try again please.\n");
		scanf_s(" %d", &cho);
	}
	return cho;
}

int CheckFile(FILE* f)															// �������� ��� �������� �����
{
	if (f == NULL)
	{
		printf("ERROR");
		return 0;
	}
	return 1;
}

void CreateFile(const char* name)												// �������� ����� + ���� ������
{
	FILE* f;
	fopen_s(&f,name, "w");
	CheckFile(f);
	fclose(f);
}

void InputFile1(const char* name)												// ���� ������ � ������ ����
{
	int N;
	printf("Enter the num of strings in first file (f1.txt): ");
	scanf_s("%d", &N);
	while (N <= 0)																// �������� ��������� �������� ����������
	{
		rewind(stdin);
		printf("ERROR. Incorrect input!\n");
		printf("Try again please!\n");
		scanf_s("%d", &N);
	}
	char* str = (char*)calloc(255, sizeof(char));
	FILE* f1;
	fopen_s(&f1, name, "r+");
	CheckFile(f1);
	rewind(stdin);
	printf("\nEnter the text in the first file (f1.txt).\nPut a point(.) at the end of each sentence:\n ");
	for (int i = 0; i < N; i++)													// ���� ������
	{
		fgets(str, 255, stdin);
		fputs(str, f1);
	}
	rewind(f1);
	fclose(f1);
}

void InputFile2(const char* name)												// ���� ������ � ���� 2
{
	FILE* f2;
	fopen_s(&f2, name, "r+");
	CheckFile(f2);
	char* str = (char*)calloc(255, sizeof(char));
	printf("\nEnter the text in file 2 (f2.txt).\nYou have to enter words separated by commas(,): \n");
	fgets(str, 255, stdin);
	fputs(str, f2);
	fclose(f2);
}


 void UseReadyFiles()															// ��������������� �������� ������ f1 � f2
{
	 FILE* f1;
	 fopen_s(&f1, "f1.txt", "r");
	 CheckFile("f1.txt");
	 char* temp = (char*)calloc(255, sizeof(char));
	 int nums = CountOfStrOfFile("f1.txt");
	 printf("Your new text is : \n");
	 for (int i = 0; i < nums; i++)
	 {
		 fgets(temp, 255, f1);
		 ChangeFile(temp, "f2.txt", "g.txt");
	 }
	 free(temp);
	 fclose(f1);
}

void CreateNewFiles()															// ������� ����� � ������ �����
{
	CreateFile("f1.txt");
	CreateFile("f2.txt");
	CreateFile("g.txt");
	InputFile1("f1.txt");
	InputFile2("f2.txt");
	FILE* f1;
	fopen_s(&f1, "f1.txt", "r");
	CheckFile("f1.txt");
	char* temp = (char*)calloc(255, sizeof(char));
	int nums = CountOfStrOfFile("f1.txt");
	printf("Your new text is : \n");
	for (int i = 0; i < nums; i++)
	{
		fgets(temp, 255, f1);
		ChangeFile(temp,"f2.txt", "g.txt");
	}
	free(temp);
	fclose(f1);
}

void PrintFile(const char* name)												// ����� ������ �� �����
{
	char s;
	FILE* f;
	fopen_s(&f, name, "r");
	CheckFile(f);
	printf("\nFile:\n");
	while ((s = getc(f)) != EOF)
		printf("%c", s);
	fclose(f);
}

int CountOfStrOfFile(const char* name)											// ���������� ����� � ������ �����
{
	int cnt = 0;
	FILE* f;
	fopen_s(&f, name, "r");
	CheckFile(f);
	do 
	{
		char* str = (char*)calloc(255, sizeof(char));
		fgets(str, 255, f);
		if (feof(f)) 
			break;
		cnt++;
	} while (1);

	return cnt;
}

void ChangeFile(char* str, const char* file2, const char* file3)				// ������ ���� � ������ ����� 1
{
	FILE* f2;
	fopen_s(&f2, file2, "r");
	CheckFile(f2);
	FILE* g;
	fopen_s(&g, file3, "a");
	CheckFile(g);
	char* text = (char*)calloc(255, sizeof(char));
	char* sep = ",";															// ��������� �� ������ �����������									
	char* word = (char*)calloc(255, sizeof(char));								// ��������� ������ ��� ����� �� ������ ����� 1
	char* string = (char*)calloc(255, sizeof(char));							// ��������� ������ ��� ������ �� ����� 2
	int flag = 0;
	int j = 0;
	char* separ = (char*)calloc(255, sizeof(char));								// ��������� ������ ��� ����� ���������� ��� ������� �� ������ ����� 1
	for (int i = 0; i < strlen(str); i++)										// ���� ��� ������� �� ������
	{
		if (str[i] == ',' || str[i] == ';' || str[i] == ' ' || str[i] == '.')	// ���� ���� ������, ������ ����� ��� ��������� �������������
		{
			rewind(f2);															// ������������� ������� ������� ��� ������/����������
			fgets(string, 255, f2);												// ��������� ����� � ������ �� ����� 2 (f2.txt)
			char* word1 = strtok(string, sep);									// ��������� ������ � ��������� ������� ����� �� ����
			char* word2 = strtok(NULL, sep);									// ��������� ������� ����� �� ����
			separ[0] = str[i];
			separ[1] = '\0';
			j++;
			word[j] = '\0';														// ���������� ����-������ � ����� ����������� ����� �� ������ ����� 1
			while (word2 != NULL && word1[strlen(word1) - 1] != '\n')
			{
				if (strcmp(word, word1) == 0)									// ���������� ����� �� ������ ������� ����� � ������ ������ �� ����
				{
					strcat(text, word2);										// ��������� � ��������� ����� ������ ����� �� ����
					strcat(text, separ);										// ���������� � text ���� ���������� ��� ������
					flag = 1;
					break;
				}
				word1 = strtok(NULL, sep);										// ���� ����� �� �������, ���� ��������� ����
				word2 = strtok(NULL, sep);
			}
			if (flag == 0)														// ���� ����� �� �������, �� ��������� � text ����� �� ������ ����� 1
			{
				strcat(text, word);												// ���������� � text �� �� �����, ��� � � ������ �����
				strcat(text, separ);											// ���������� � text ���� ���������� ��� ������
			}

			free(word);															// ����������� ������ ��� ������ �����
			char* word = (char*)calloc(255, sizeof(char));
			free(separ);
			char* separ = (char*)calloc(255, sizeof(char));
			j = 0;																// ��� ������ ����� ����� � ������
			flag = 0;
		}
		else
		{
			word[j] = str[i];													// ������ ����� �� ������ ����� 1
			j++;
		}
	} 
	strcat(text, "\n");
	puts(text);																	// ����� ���������� ������
	fputs(text, g);																// ���������� ��������� ����� � ����� ���� g.txt
	free(string);
	free(text);
	fclose(f2);
	fclose(g);
}