#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void main()
{
	struct s1* info;
	int n = InputInfoInStruct(&info);
	PrintStruct(info, n);
	FindProduct(info, n);
	printf("\n\n");
}