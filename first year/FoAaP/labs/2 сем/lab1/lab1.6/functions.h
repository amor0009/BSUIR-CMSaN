#pragma once

#include <stdio.h>

int ChoiceOption();																// выбор действия над программой

int CheckFile(FILE* f);															// проверка при открытии файла

void CreateFile(const char* name);												// создание файла

void InputFile1(const char* name);												// ввод первого файла

void InputFile2(const char* name);												// ввод второго файла

void UseReadyFiles();															// воспользоваться готовыми фалами f1 и f2

void CreateNewFiles();															// создать файлы и ввести текст самому

void PrintFile(const char* name);												// вывод текста из файла

int CountOfStrOfFile(const char* name);											// количество строк в тексте файла

void ChangeFile(char* str, const char* file2, const char* file3);				// замена слов в тексте файла 1
