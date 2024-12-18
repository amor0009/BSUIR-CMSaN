#include "Header.h"

int main()
{
	struct tree* node = NULL;
	int* arr = (int*)calloc(1,sizeof(int));
	arr = ReadInfoFromFile(arr);
	node = InitialMenu(node, arr);
	free(arr);
	free(node);
}