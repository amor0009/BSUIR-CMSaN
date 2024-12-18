#include "functions.h"
#include <stdlib.h>

int main()
{
	int opt = 2;
	do
	{
		system("cls");										// очистка окна вывода
		int n = number_of_symbols();
		char* mas = memory(n);
		//mas = text_input(mas, n);
		mas = text_input_fgets(mas, n);
		n = str_len(mas);
		mas = changed_text(mas, n);
		text_output(mas, n);
		opt = choice_option();                             // функция для выбора действия над прогрмммой
	} while (opt == 0);
	return 0;
}