#include "functions.h"
#include <stdlib.h>

int main()
{
	int n, m;
	int** mas;
	int opt2;
	do
	{
		system("cls");			// очистка консоли(окна вывода) от предыдущего вывода
		n = n_rows();
		m = m_columns();
		mas = memory(n, m);
		choice_option1(mas, n, m);
		print_matr(mas, n, m);
		mas = changed_matr(mas, &n, &m);
		print_matr(mas, n, m);
		// free_mas(mas);
		opt2 = choice_option2();
	} while (opt2 == 0);
	return 0;
}