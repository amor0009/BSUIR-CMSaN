#include <stdio.h>
#include <stdlib.h>
#define N 100					// размер массива

int main(void)
{
	int a[N][N];				// объявление двумерного массива a
	int n, m;					// объявление переменных для обозначения строк и столбцов двумерного массива
	int i, j;					// объявление переменных для обозначения индексов двумерного массива 
	int t1, t2, t3;				// объявление переменных для проверки введённых данных
	int ctr = 0;				// объявление и инициализация переменной для счётчика
	int k;						// объявление переменной для вывода порядка введённого элемента двумерного массива a
	int x;						// объявление переменной для замены мест элементов массива
	int n1 = 1;					// объявление и инициализация переменной для работы с сортировкой массива
	int cho;					// объявление переменной для выбора действия

	do							// цикл с постусловием для выбора действия (0. Попробовать ещё раз;  1. Закончить выполнение программы)
	{
		k = 0;
		printf("Enter the number of rows and columns of the array no less than 0 and no more than %3d: ", N);
		t1 = scanf_s(" %d", &n);

		if ((t1 != 1) || ((n <= 0) || (n > N)))			// условнй оператор if и цикл с постусловием для проверки введённого значения n
		{
			do
			{
				rewind(stdin);
				printf("\nYou have entered the wrong data,\nyou should to enter the number of rows and columns of the array no less than 0 and no more than %3d, try again please: ", N);
				t1 = scanf_s(" %d", &n);
				printf("\n");
			} while ((t1 != 1) || ((n <= 0) || (n > N)));
		}

		m = n;											// кол-во строк равняется кол-ву столбцов (для квадратной матрицы n-го порядка)

		printf("Enter the row of the array element(s):\n");

		for (i = 0; i < n1; i++)						// 2 цикла с параметром для работы с двумерным массивом a
			for (j = 0; j < n; j++)
			{
				printf(" %d. ", k + 1);
				t2 = scanf_s(" %d", &a[i][j]);
				k++;
				if (t2 != 1)							// условнй оператор if и цикл с постусловием для проверки введённых элементов двумерного массива a
				{
					do
					{
						rewind(stdin);
						printf("\nYou have entered the wrong data,\nyou should to enter the array element(s), try again please: \n");
						printf(" %d. ", k);
						t2 = scanf_s(" %d", &a[i][j]);
					} while (t2 != 1);
				}
			}

		printf("\nArray:\n");

		for (i = 0; i < n1; i++)						// 2 цикла с параметром для вывода двумерного массива a
			for (j = 0; j < n; j++)
				printf(" %3d", a[i][j]);


		for (i = 1; i < n; i++)							// 2 цикла с параметром для сортировки двумерного массива a по условию задачи 
		{
			x = a[i - 1][0];
			for (j = 0; j < m; j++)
			{
				a[i][j] = a[i - 1][j + 1];
				if (j == n - 1)							// условный оператор if для замены последнего элемента i-ой строки на первый элемент i-1-ой строки двумерного массива
					a[i][n - 1] = x;
			}
		}

		printf("\n\nSorted array:\n");

		for (i = 0; i < n; i++)							// 2 цикла с параметром для вывода отсортированного двумерного массива a
		{
			for (j = 0; j < m; j++)
			{
				printf(" %3d", a[i][j]);
				ctr++;
				if (ctr == m)							// условный оператор if для перехода на i-ую строку
					printf("\n");
			}
			ctr = 0;
		}

		printf("\n0. Try again!\n");
		printf("1. Finish the program!\n");
		printf("Your choice is: ");
		t3 = scanf_s(" %d", &cho);

		if ((t3 != 1) || ((cho < 0) || (cho > 1)))		// условный оператор if и цикл с постусловием для проверки введённого значения переменной cho (выбора лействия)
		{
			do
			{
				rewind(stdin);
				printf("\nYou have entered the wrong data,\nyou should to enter 0 or 1 to shoice the option, try again please: ");
				t3 = scanf_s(" %d", &cho);
				printf("\n");
			} while ((t3 != 1) || ((cho < 0) || (cho > 1)));
		}	

	} while(cho == 0);

	return 0;
}