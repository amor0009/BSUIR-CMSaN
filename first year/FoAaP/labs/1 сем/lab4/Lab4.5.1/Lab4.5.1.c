#include <stdio.h>
#include <stdlib.h>
#define N 100                           // размер массива

int main(void)
{
    int a[N];                           // объявление массива целых чисел a
    int i;                              // объявление переменных для обозначения индексов элементов массива a
    int n;                              // объявление переменной для ввода количества элементов массива a
    int i_min;                          // объявление переменной для значения индекса минимального значения элемента массива a
    int t1, t2, t3;                     // объявление переменной для проверки ввода через scanf_s()
    int kol;                            // объявление переменной для ввода количество удаляемых элементов массива a

    printf("\nEnter the number of array elements to delete no less than 0 and no more than %3d: ", N - 1);

    do                                  // цикл с постусловием для проверки введённого значения переменной kol (введено ли число)
    {
        rewind(stdin);
        t1 = scanf_s(" %d", &kol);
        if (t1 != 1)
            printf("\nYou have entered the wrong data,\nyou should to enter the number of array elements to delete no less than 0 and no more than %3d, try again please: ", N - 1);
    } while (t1 != 1);

    if ((kol < 0) || (kol > (N - 1)))     // условный оператор if и цикл с постусловием для проверки введённого значения переменной kol
    {
        do
        {
            rewind(stdin);
            printf("\nYou have entered the wrong data,\nyou should to the number of array elements to delete no less than 0 and no more than %3d, try again please: ", N - 1);
            t1 = scanf_s(" %d", &kol);

        } while ((kol < 0) || (kol > (N - 1)));
    }

    printf("\nEnter the number of array element(s) no less than %2d and no more than %3d: ", kol, N - 1);

    do                                  // цикл с постусловием для проверки введённого значения переменной n (ввелено ли число)
    {
        rewind(stdin);
        t2 = scanf_s(" %d", &n);
        if (t2 != 1)
            printf("\nYou have entered the wrong data type,\nyou should to enter the number of array element(s) no less than %2d and no more than %3d, try again please: ", kol, N - 1);

    } while (t2 != 1);

    if ((n <= kol) || (n > N))           // условный оператор if и цикл с постусловием для проверки введённого значения переменной n 
    {
        do
        {
            rewind(stdin);
            printf("\nYou have entered the wrong data,\nyou should to enter the number of array element(s) NO LESS than %2d and NO MORE than %3d, try again please: ", kol, N - 1);
            t2 = scanf_s(" %d", &n);

        } while ((n <= kol) || (n > N));
    }

    printf("\nEnter %d array element(s): \n", n);

    for (i = 0; i < n; i++)                             // цикл с параметром для ввода значения элментов массива a
    {
        do                                              // цикл с постусловием для проверки введённых значений элементам цикла
        {
            rewind(stdin);
            printf(" %d. ", i + 1);
            t3 = scanf_s(" %d", &a[i]);
            if (t3 != 1)
                printf("You have entered the wrong data type, try again please:\n");
        } while (t3 != 1);
    }

    printf("\nArray:\n");

    for (i = 0; i < n; i++)                             // цикл с параметром для вывода значений элеменетов массива a
        printf(" %4d", a[i]);

    printf("\n");

    i_min = 0;

    for (i = 1; i < kol + 1; i++)                       // цикл с параметром для сортировке массива a по условию
    {
        i_min = 0;
        for (int j = 0; j < (n - i + 1); j++)           // цикл с параметром для нахождения индекса наименьшего элемента массива
            if (a[j] < a[i_min])
                i_min = j;


        for (int k = i_min; k <= (n - i); k++)          // цикл с параметром для удаления наименьшего элемента массива(смещение влево)
            a[k] = a[k + 1];
    }

    printf("Sorted arrey: \n");

    for (int i = 0; i < n - kol; i++)                   // цикл с параметром для вывода отсортированного по условию задачи массива a
        printf(" %4d ", a[i]);

    return 0;
}