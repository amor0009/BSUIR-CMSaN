#include "Header.h"

int main()
{
	do
	{
		system("cls");															// очистка командной строки
		struct s1* childrens;
		struct s1* ill;
		int cho1, number, numb, sizeofstruct;
		Choice1(&cho1, &number);												// выбор действия: писать самому или использовать готовыую информацию

		if (cho1 == 1)															// вводить информацию самому
		{
			InputStruct(&childrens, number);
			PrintStruct_s1(childrens, number);
			InputInformationInFile(childrens, number, "f.bin");
			FindChildren(&ill, childrens, number, &numb);
		}
		else																	// воспользоваться готовой информацией
		{
			ReadInfoFromFile(&childrens, &sizeofstruct);
			PrintStruct_s1(childrens, sizeofstruct);
			FindChildren(&ill, childrens, sizeofstruct, &numb);
		}
		qsortMedList(ill, numb);												// сортировка детей по алфавиту
		PrintStruct_s1(ill, numb);
		InputInformationInFile(ill, numb, "result.bin");						// сохранение списка детей с данным заболеванием, отсортированного по алфовиту, в бинарный файл result.bin
	} while (сhoice());
	return 0;
}