#include "functions.h"
#include <stdlib.h>
#include "functions.h"

int main()
{
	int opt1, opt2 = 2;
	do
	{
		system("cls");																// очистка окна вывода
		int n = number_of_rows();													// ввод кол-ва строк текста
		int m = number_of_symbols();												// ввод кол-ва символов строки
		char** text = memory(n, m);                                                 // выделене динамической памяти
		text = text_input(text, n, m);												// ввод текста (всех строк)		
		text = changed_text1(text, n, m);											// изменение строчных и прописных букв
		text = choice_option1_and_changing(text, n, m);								// выбор сортировки и её выполнение
		text_output(text, n, m);													// вывод текста
		opt2 = choice_option2();                                                    // функция для выбора действия над программой
	} while (opt2 == 0);
	return 0;
}