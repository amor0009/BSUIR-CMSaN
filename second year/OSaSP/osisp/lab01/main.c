#define _DEFAULT_SOURCE

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

//Описание какой-то своей сортировки, т.к. alphasort из функции scandir выполняет сортировку согласно стандарту
int ownSort(const struct dirent** e1, const struct dirent** e2)
{
    return strcoll((*e2)->d_name, (*e1)->d_name);
}

//Основная функция обхода дерева каталога
void Dirwalk(char* directory, const int* options)
{
    struct dirent** namelist;
    int count;
    
    //Проверка на флаг -s для вывода согласно сортировке
    if(options[3] == 1)
        count = scandir(directory, &namelist, NULL, alphasort);
    else
        count = scandir(directory, &namelist, NULL, ownSort);

    //Отлов возврата ошибки
    if(count == -1){
        perror("Scandir error");
        return;
    }

    //Цикл выводящий файлы и вызывающий Dirwalk для каждого каталога внутри
    for (int i = 0; i < count; i++){

        char* name = namelist[i]->d_name;
        unsigned char type = namelist[i]->d_type;  
        
        //Игнорирование каталогов . и .. , отсутствие приводит к бесконечному циклу
        if(!(strcmp(name, ".") && strcmp(name, "..")))
            continue;

        //Вывод согласно флагам -f -d -l
        if((options[0] && (type == DT_LNK))
        || (options[1] && (type == DT_DIR))
        || (options[2] && (type == DT_REG))
        || !(options[0] || options[1] || options[2]))
            printf("%s/%s\n", directory, name);

        //Проверка на каталог и рекурсивный вызов Dirwalk
        if(type == DT_DIR){
            char newName[1024];

            strcpy(newName, directory);
            strcat(newName, "/");
            strcat(newName, name);

            Dirwalk(newName, options);
        }
         
    }
    
    return;
}

int main(int argc, char **argv)
{

    int flags[4] = { 0 };
    int c;
    
    //Валидация аргументов командной строки
    while((c = getopt(argc, argv, "ldfs")) != -1)
    {
        switch (c)
        {
        case 'l': flags[0] = 1; break;
        case 'd': flags[1] = 1; break;
        case 'f': flags[2] = 1; break;
        case 's': flags[3] = 1; break;
        default: break;
        }
    }

    char* directory;

    //Обнаружение отсутствия/присутствия пути к файлу в аргументах
    if(argv[argc-1][0] == '-' || argc == 1)
        directory = ".";
    else
        directory = argv[argc-1];

    Dirwalk(directory, flags);

    return 0;
}