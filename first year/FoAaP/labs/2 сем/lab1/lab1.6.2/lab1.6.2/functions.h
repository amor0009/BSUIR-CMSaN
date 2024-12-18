#pragma once

#include <stdio.h>

int ChoiceOption();																					// выбор действия(создавать файлы вручную / воспользоваться шотовыми

int CheckFile(FILE*);																				// проверка открытия файла

void CreateFile(const char* name);																	// создание файла

void UseReadyFiles();																				// воспользоваться готовыми фалами f1 и f2

void CreateNewFiles();																				// создать файлы f1 и f2 вручную

void PrintFile(const char* name);																	// вывести файл

int IsLetter(char c);																				// проверка на символ

void FindWordsInF2(char* mas, char** Word1, char** Word2, int* length1, int* length2);				// найти пару слов в файле f2

char* GetWord(char* text, int WordPos, int WordLength, char* word);									// получение слова из текста

int FindWord1InF1(const char* string, const char* wordToFind);										// нахождение первого слова из пары в файле f1

void ChangeFile(char* text1, char* text2);															// изменение текста файла f1 

int FileToStrLen(char* text1);																		// длина строки, с помещённым в неё текстом

int CountOfStrOfFile(char* text);																	// количество строк в тексте файла

void ChangeFile(char* text1, char* text2);															// замена слов в тексте файла 1#pragma once
