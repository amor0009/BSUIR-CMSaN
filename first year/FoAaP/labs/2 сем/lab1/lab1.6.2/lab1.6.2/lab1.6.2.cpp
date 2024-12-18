#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void main(int argc, char** argv)
{
	int choice = ChoiceOption();
	if (argc < 1)
		return;
	if (choice == 1)
		UseReadyFiles();
	if (choice == 2)
		CreateNewFiles();

	PrintFile("g.txt");
}