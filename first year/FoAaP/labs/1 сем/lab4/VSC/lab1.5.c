#include <stdio.h>
#include <stdlib.h>
#define N 100           // размер массива
#define kol 5           // количество наименьших элементов, которые необходмо удалить

int main(void)
{
    int a[N];           // объявление массива целых чисел a
    int i;              // объявление переменной для обозначения индексов элементов массива a
    int n;              // объявление переменной для введения количества элементов массива a
    int i_min;          // объявление переменной для значения индекса минимального значения элемента массива

    printf("\nEnter the number of array element(s) no less than %2d and no more than %3d: ", kol, N-1);
    scanf(" %d", &n);

    printf("\nEnter %d array elements (only integer numbers): \n", n);

    for(i=0; i < n; i++)                    // цикл для ввода значения элментов массива a
        scanf(" %d", &a[i]);
    
    printf("\nArray:\n");

    for(i=0; i < n; i++)                    // цикл для вывода значений элеменетов массива a
        printf(" %4d", a[i]);

    printf("\n");

    i_min=0;
 
    for(i=1; i<kol+1; i++)                  // цикл для определения соответствующих элементов массива
    {
        for(int j=0; j<n; j++)              // цикл для нахождения индекса наименьшего элемента массива
            if (a[j]<a[i_min])          
                i_min=j;
 
 
        for(int k=i_min; k<=(n-i); k++)     // цикл для удаления наименьшего элемента массива(смещение влево)
            a[k]=a[k+1];
    }

    printf("Sorted arrey: \n");

    for(int i=0; i<n-kol;i++)               // вывод отсортированного по условию задачи массива a
        printf(" %4d ",a[i]);

    return 0;
}