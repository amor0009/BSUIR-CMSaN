#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ChoiceOption()																// выбор действия
{
	int cho;
	printf("1. Use ready files.\n");
	printf("2. Create new files.\n");
	printf("Your choice is: ");
	scanf_s(" %d", &cho);
	while (cho > 2 || cho < 1)													// проверка на ввод
	{
		rewind(stdin);
		printf("The number of this option does not exist!\n");
		printf("Try again please.\n");
		scanf_s(" %d", &cho);
	}
	return cho;
}

int CheckFile(FILE* f)															// проверка при открытии файла
{
	if (f == NULL)
	{
		printf("ERROR");
		return 0;
	}
	return 1;
}

void CreateFile(const char* name)												// создание файла + ввод текста
{
	FILE* f;
	fopen_s(&f,name, "w");
	CheckFile(f);
	fclose(f);
}

void InputFile1(const char* name)												// ввод текста в первый файл
{
	int N;
	printf("Enter the num of strings in first file (f1.txt): ");
	scanf_s("%d", &N);
	while (N <= 0)																// проверка введённого значения переменной
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
	for (int i = 0; i < N; i++)													// ввод текста
	{
		fgets(str, 255, stdin);
		fputs(str, f1);
	}
	rewind(f1);
	fclose(f1);
}

void InputFile2(const char* name)												// ввод текста в файл 2
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


 void UseReadyFiles()															// воспользоваться готовыми фалами f1 и f2
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

void CreateNewFiles()															// создать файлы и ввести текст
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

void PrintFile(const char* name)												// вывод текста из файла
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

int CountOfStrOfFile(const char* name)											// количество строк в тексте файла
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

void ChangeFile(char* str, const char* file2, const char* file3)				// замена слов в тексте файла 1
{
	FILE* f2;
	fopen_s(&f2, file2, "r");
	CheckFile(f2);
	FILE* g;
	fopen_s(&g, file3, "a");
	CheckFile(g);
	char* text = (char*)calloc(255, sizeof(char));
	char* sep = ",";															// указатель на символ разделитель									
	char* word = (char*)calloc(255, sizeof(char));								// выделение памяти для слова из текста файла 1
	char* string = (char*)calloc(255, sizeof(char));							// выделение памяти для текста из файла 2
	int flag = 0;
	int j = 0;
	char* separ = (char*)calloc(255, sizeof(char));								// выделение памяти для знака препинания или пробела из текста файла 1
	for (int i = 0; i < strlen(str); i++)										// цикл для прохода по строке
	{
		if (str[i] == ',' || str[i] == ';' || str[i] == ' ' || str[i] == '.')	// если сюда попали, значит слово для сравнения сформированно
		{
			rewind(f2);															// устанавливаем текущую позицию для записи/считывания
			fgets(string, 255, f2);												// считываем текст с парами из файла 2 (f2.txt)
			char* word1 = strtok(string, sep);									// разбиение строки и получение первого слова из пары
			char* word2 = strtok(NULL, sep);									// получение второго слова из пары
			separ[0] = str[i];
			separ[1] = '\0';
			j++;
			word[j] = '\0';														// записываем нуль-символ в конец полученного слова из текста файла 1
			while (word2 != NULL && word1[strlen(word1) - 1] != '\n')
			{
				if (strcmp(word, word1) == 0)									// сравниваем слова из текста первого файла с первым словом из пары
				{
					strcat(text, word2);										// добовляем в изменённый текст второе слово из пары
					strcat(text, separ);										// записываем в text знак препинания или пробел
					flag = 1;
					break;
				}
				word1 = strtok(NULL, sep);										// если слова не совпали, берём следующую пару
				word2 = strtok(NULL, sep);
			}
			if (flag == 0)														// если слова не совпали, то вписываем в text слово из текста файла 1
			{
				strcat(text, word);												// записываем в text то же слово, что и в первом файле
				strcat(text, separ);											// записываем в text знак препинания или пробел
			}

			free(word);															// освобождаем память для нового слово
			char* word = (char*)calloc(255, sizeof(char));
			free(separ);
			char* separ = (char*)calloc(255, sizeof(char));
			j = 0;																// для записи новго слова с начала
			flag = 0;
		}
		else
		{
			word[j] = str[i];													// запись слова из текста файла 1
			j++;
		}
	} 
	strcat(text, "\n");
	puts(text);																	// вывод изменённого текста
	fputs(text, g);																// записываем изменённый текст в новый файл g.txt
	free(string);
	free(text);
	fclose(f2);
	fclose(g);
}