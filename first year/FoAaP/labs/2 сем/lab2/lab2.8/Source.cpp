#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct s1
{
    char name[20];
    char country[20];
    char hes[20];
}date;

int main()
{

    FILE* f;
    if ((f = fopen("D:\laba9.4\\hes.txt", "r")) == NULL)
    {
        puts("Ошибка открытия файла!");
        system("pause");
        return;
    }
    char per;
    int i;
    for (i = 0; i < 20; i++)
    {
        date.country[i] = '\0';
        date.hes[i] = '\0';
        date.name[i] = '\0';
    }
    while (per != '\n')
    {
        fscanf(f, "%c", &per);
        printf("%c", per);
    }
    char mas[20];
    int j = 0, k = 0;
    printf("\nВведите, пожалуйста, страну\n");
    for (i = 0; i < 20; i++)
        scanf("%c", mas[i]);
    i = 0;
    while (!feof(f))
    {
        while (date.name[i] != ' ')
        {
            fscanf(f, "%c", date.name[i]);
            i++;
        }
        i = 0;
        while (date.country[i] != ' ')
        {
            fscanf(f, "%c", date.country[i]);
            i++;
        }
        i = 0;
        while (date.hes[i] != ' ')
        {
            fscanf(f, "%c", date.hes[i]);
            i++;
        }
        i = 0;
        while (mas[i] != '\0')
        {
            if (mas[i] == date.country[i]) k++;
            i++;
        }
        if (i == k)
        {
            while (date.name[j] != '\0')
            {
                printf("%c", date.name[j]);
                j++;
            }
            j = 0;
            printf(" в количестве ");
            while (date.hes[j] != '\0')
            {
                printf("%c", date.hes[j]);
                j++;
            }

        }
    }
    fclose(f);
    return 0;