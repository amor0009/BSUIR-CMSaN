#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int* a = 0;
	int n = 0;
	int cho = 2;
	do
	{
		system("cls");
		n = referees();
		a = a_memory(a, n);
		a_input(a, n);
		a_output(a, n);
		a = a_change(a, n);
		n = a_changed_output(a, n);
		a_average(a, n);
		cho = check();
	} while (cho == 0);
	// free(a);
	return 0;
}