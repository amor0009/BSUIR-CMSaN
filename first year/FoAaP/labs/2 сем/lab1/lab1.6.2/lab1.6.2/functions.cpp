#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

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

int StrLen(char* mas)															// длина строки
{
	int i = 0;
	while (mas[i] != '\0')
		i++;
	i++;
	return i;
}

void CreateFile(const char* name)												// создание файла + ввод текста
{
	FILE* f;
	fopen_s(&f, name, "w");
	CheckFile(f);
	fclose(f);
}

void InputFile1(const char* name)
{
	int N;
	printf("Enter the num of strings in first file (f1.txt): ");
	scanf_s("%d", &N);
	while (N <= 0)
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
	for (int i = 0; i < N; i++)													// ввод текста
	{
		fgets(str, 255, stdin);
		fputs(str, f1);
	}
	rewind(f1);
	fclose(f1);
}

void InputFile2(const char* name)
{
	FILE* f2;
	fopen_s(&f2, name, "r+");
	CheckFile(f2);
	char* str = (char*)calloc(255, sizeof(char));
	printf("Enter the text in file 2 (f2.txt).\nYou have to enter words separated by commas(,): \n");
	fgets(str, 255, stdin);
	fputs(str, f2);
	fclose(f2);
}


void UseReadyFiles()															// воспользоваться готовыми фалами f1 и f2
{
	char* file1 = FileToStr("f1.txt");
	char* file2 = FileToStr("f2.txt");
	ChangeFile(file1, file2);
}

void CreateNewFiles()															// создать файлы и ввести текст
{
	CreateFile("f1.txt");
	CreateFile("f2.txt");
	char* file1 = FileToStr("f1.txt");
	char* file2 = FileToStr("f2.txt");
	ChangeFile(file1, file2);
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

int IsLetter(char c)															// является ли символ буквой
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	return 0;
}

void FindWordsInF2(char* mas, char** Word1, char** Word2, int* length1, int* length2)		// поиск слов (пар) во втором файле
{
	int CurrentWordIndex = 0;
	int i = 0;
	int FirstWordPos;
	int FirstWordLength;
	int SecondWordPos;
	int SecondWordLength;

	while (mas[i] != '\0')
	{
		while (mas[i] == ' ' || mas[i] == ',')
			i++;

		int isWord = 1;
		int SymbolPos = i;
		while (mas[i] != ' ' && mas[i] != '\0' && mas[i] != ',')
		{
			if (!IsLetter(mas[i]))
				isWord = 0;

			i++;
		}

		if (isWord)
		{
			CurrentWordIndex++;

			if (CurrentWordIndex == 1 || CurrentWordIndex % 2 == 1)				// нахождения первого слова из пары	
			{
				FirstWordPos = SymbolPos;
				FirstWordLength = i - SymbolPos + 1;
				char* word1 = (char*)calloc(FirstWordLength + 1, sizeof(char));
				word1 = GetWord(mas, FirstWordPos, FirstWordLength, word1);
				*Word1 = word1;
				*length1 = FirstWordLength;
			}
			else if (CurrentWordIndex % 2 == 0)									// нахождение второго слова из пары
			{
				SecondWordPos = SymbolPos;
				SecondWordLength = i - SymbolPos + 1;
				char* word2 = (char*)calloc(FirstWordLength + 1, sizeof(char));
				word2 = GetWord(mas, FirstWordPos, FirstWordLength, word2);
				*Word2 = word2;
				*length2 = SecondWordLength;
				break;
			}
		}
	}
}

char* GetWord(char* text, int WordPos, int WordLength, char* word)				// получение слова 
{
	int i = WordPos;
	int j = 0;

	while (text[i] != ' ' && text[i] != ',' && text[i] != '.' && text[i] != '\n' && text[i] != '\0')
	{
		word[j] = text[i];
		j++;
		i++;
	}
	return word;
}

int FindWord1InF1(char* string, char* wordToFind)								// нахождение позиции первого слова в тексте файла 1
{
	int i = 0;

	while (string[i] != '\0')
	{
		int isEquals = 1;

		for (int j = 0; wordToFind[j] != '\0' && string[i + j] != '\0'; j++)
			if (string[i + j] != wordToFind[j])
			{
				isEquals = 0;
				break;
			}

		if (isEquals)
			return i;

		i++;
	}

	return -1;
}

int FileToStrLen(char* text1)													// длина строки, с помещённым в неё текстом
{
	int i = 0;
	while (text1[i] != '\0')
		i++;
	return i;
}

int CountOfStrOfFile(const char* name)												// количество строк в тексте файла
{
	int cnt = 0;
	FILE* f;
	fopen_s(&f, name, "r");
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

void ChangeFile(char* text1, char* text2)										// замена слов в тексте файла 1
{
	int n;
	int j = 0;
	int WordPos;
	int length1, length2;
	char* Word1, * Word2;

	FindWordsInF2(text2, &Word1, &Word2, &length1, &length2);
	WordPos = FindWord1InF1(text1, Word1);

	for (int i = WordPos; i < (FileToStrLen(text1) - length1); i++)
		text1[i] = text1[i + length1];

	text1 = (char*)realloc(text1, (FileToStrLen(text1) - length1 + length2) * sizeof(char));					// изменение длины строки с текстом файла 1 на длину второго слова

	for (int i = (FileToStrLen(text1) - length2); i >= WordPos; i--)			// сдвиг строки влево для освобождения места для второго слова
		text1[i] = text1[i + length2];

	for (int i = WordPos; i < WordPos + length2; i++, j++)						// вставка второго слова в текст файла 1
	{
		text1[i] = Word2[j];
	}

	FILE* f;
	fopen_s(&f, "g.txt", "w+");
	CheckFile(f);

	n = CountOfStrOfFile(text1);

	char* str = (char*)calloc(255, sizeof(char));
	for (int i = 0; i < n; i++)													// ввод текста
		fputs(str, f);

	fclose(f);
}