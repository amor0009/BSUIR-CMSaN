#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void main()
{
	struct s1* info;
	struct s2* product;
	int num;
	int n = InputInfoInStruct(&info);
	StructInFile2(info, n);
	StructFromFile2(&info, n);
	PrintStruct_s1(info, n);
	FindProduct(info, &product, n, &num);
	PrintStruct_s2(product, num);
	StructInFile1(info, num);
	free(product);
	free(info);
}