#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(void) 
{
    int choice;
    choice = ChoiceOption();
    if (choice == 2)
        CreateNewFiles();
    else
        UseReadyFiles();
    return 0;
}