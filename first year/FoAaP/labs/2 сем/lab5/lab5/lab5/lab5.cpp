#include "Header.h"

int main()
{
	struct FILO* h = NULL;
	do
	{
		system("cls");
		int n = 0;
		//struct FILO* h = NULL;
		char* str = (char*)calloc(70, sizeof(char));
		str = Input();
		n = Check(h, str);
		n = CheckAndReplace(h, str);
		free(str);
	} while (choice());
	return 0;
}