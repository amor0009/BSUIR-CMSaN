#include "functions.h"
#include <stdlib.h>
#include <string.h>

int main()
{
	int opt = 2;
	do 
	{
		system("cls");					// для очистки окна вывода
		int n = number_of_symbols();
		char* mas = memory(n);
		mas = text_input(mas, n);
		n = strlen(mas);
		mas = changed_text(mas, n);
		text_output(mas, n);
		opt = choice_option();
	} while (opt == 0);
	return 0;
}