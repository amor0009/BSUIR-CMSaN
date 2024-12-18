#pragma once

int number_of_symbols();							// функция для ввода кол-ва символов строки

char* memory(int n);								// функция для выделения динамической памяти

char* text_input_fgets(char* mas, int n);			// функция для ввода строки с помощью gets

char* text_input(char* mas, int n);					// функция для ввода строки

int str_len(char* mas);								// функция для вычисления длины строки

void text_output(char* mas, int n);					// функция для вывода строки

char* changed_text(char* mas, int n);				// функция для изменения строки

int choice_option();								// функция для выбора действия над прогрмммой
