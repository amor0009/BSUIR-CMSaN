#include <stdio.h>
#include <stdlib.h>
#define N 100                           // размер массива

int main(void)
{
    int a[N];                           // объявление массива целых чисел a
    int i;                              // объявление переменных для обозначения индексов элементов массива a
    int n;                              // объявление переменной для ввода количества элементов массива a
    int i_min;                          // объявление переменной для значения индекса минимального значения элемента массива a
    int t1, t2, t3, t4;                 // объявление переменной для проверки ввода через scanf_s()
    int kol;                            // объявление переменной для ввода количество удаляемых элементов массива a
    int cho;                            // объявление переменной для выбора действия (0.Попробовать ещё раз; 1. Закончить выполнение программы)

    do                                  // цикл с постусловием для выбора действия (0.Попробовать ещё раз; 1. Закончить выполнение программы)
    {
        printf("\nEnter the number of array elements to delete no less than 0 and no more than %3d: ", N - 1);
        t1 = scanf_s(" %d", &kol);

        if ((t1 != 1) || (kol < 0) || (kol > (N - 1)))                      // условный оператор if и цикл с постусловием для проверки введённого значения переменной kol
        {
            do
            {
                rewind(stdin);
                printf("\nYou have entered the wrong data,\nyou should to enter the number of array elements to delete no less than 0 and no more than %3d, try again please: ", N - 1);
                t1 = scanf_s(" %d", &kol);
            } while ((t1 != 1) || (kol < 0) || (kol > (N - 1)));
        }

        printf("\nEnter the number of array element(s) no less than %2d and no more than %3d: ", kol, N);
        t2 = scanf_s(" %d", &n);

        if ((t2 != 1) || ((n < kol) || (n > N)))                            // условный оператор if и цикл с постусловием для проверки введённого значения переменной n
        {
            do
            {
                rewind(stdin);
                printf("\nYou have entered the wrong data type,\nyou should to enter the number of array element(s) no less than %2d and no more than %3d, try again please: ", kol, N);
                t2 = scanf_s(" %d", &n);
            } while ((t2 != 1) || ((n < kol) || (n > N)));
        }

        printf("\nEnter %d array element(s): \n", n);

        for (i = 0; i < n; i++)                                             // цикл с параметром для ввода значения элментов массива a
        {
            printf(" %d. ", i + 1);
            t3 = scanf_s(" %d", &a[i]);
            if (t3 != 1)
            {
                do                                                          // цикл с постусловием для проверки введённых значений элементам массива a
                {
                    rewind(stdin);
                    printf("You have entered the wrong data type, try again please: ");
                    printf(" %d. ", i + 1);
                    t3 = scanf_s(" %d", &a[i]);
                } while (t3 != 1);
            }
        }

        printf("\nArray:\n");

        for (i = 0; i < n; i++)                                             // цикл с параметром для вывода значений элеменетов массива a
            printf(" %4d", a[i]);

        printf("\n");

        i_min = 0;

        for (i = 1; i < kol + 1; i++)                                       // цикл с параметром для сортировке массива a по условию
        {
            i_min = 0;
            for (int j = 0; j < (n - i + 1); j++)                           // цикл с параметром для нахождения индекса наименьшего элемента массива
                if (a[j] < a[i_min])
                    i_min = j;


            for (int k = i_min; k <= (n - i); k++)                          // цикл с параметром для удаления наименьшего элемента массива(смещение влево)
                a[k] = a[k + 1];
        }

        printf("Sorted arrey: \n");

        for (int i = 0; i < n - kol; i++)                                   // цикл с параметром для вывода отсортированного по условию задачи массива a
            printf(" %4d ", a[i]);

        printf("\n0. Try again!");
        printf("\n1. Finish the program!");
        printf("\nYour choice is: ");
        t4 = scanf_s(" %d", &cho);
        if((t4 != 1) || ((cho > 1) || (cho < 0)))                           // // условный оператор if и цикл с постусловием для проверки введённого значения переменной cho
            do
            {
                rewind(stdin);
                printf("You have entered the wrong data type, try again please: ");
                t4 = scanf_s(" %d", &cho);
            } while ((t4 != 1) || ((cho > 1) || (cho < 0)));

    } while (cho == 0);

    return 0;
}