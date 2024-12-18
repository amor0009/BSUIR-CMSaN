#include "Header.h"

int main()
{
	do
	{
		system("cls");
		int n = 0;
		struct FILO* h = NULL;
		char* str = (char*)calloc(30, sizeof(char));
		str = Input();
		n = Check(h, str);
		free(str);
	} while (choice());
	return 0;
}