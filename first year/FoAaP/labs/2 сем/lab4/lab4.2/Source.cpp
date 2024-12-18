#include "Header.h"

void Choice1(int* choice1, int* number)
{
	int n, num;
	printf("1. Enter data manually.");
	printf("\n2. Read information from a file.");
	printf("\nYour choice is ");
	scanf_s("%d", &n);
	printf("\n");
	while (n > 2 || n < 1)														// проверка введённой переменной
	{
		rewind(stdin);
		system("cls");
		printf("\nERROR. Try again please.\n");
		printf("\n1. Enter data manually.");
		printf("\n2. Read information from a file.");
		printf("\nYour choice is ");
		scanf_s("%d", &n);
		printf("\n");
	}

	if (n == 1)
	{
		do
		{
			rewind(stdin);
			printf("Enter the number of children you would like to enter: ");
			scanf_s("%d", &num);
			printf("\n");
		} while (num < 0);														// проверка введённой переменной
	}
	else
		num = 0;
	*number = num;
	*choice1 = n;
}

void ReadInfoFromFile(struct s1** children, int* sizeofstruct)					// чтение массива структур из текстового файла f.txt
{
	FILE* fp;																	// объявление перменных
	int size;																	// кол-во стрктур
	int file;																	// размер файла
	int sizestruct;
	int i = 0;

	fp = fopen("f.bin", "rb");
	CheckFile(fp);																// проверка открытия файла f.txt
	fseek(fp, 0, SEEK_END);
	file = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	size = file / sizeof(struct s1);
	//size = NumberOfStructs(fp);												// вычисление кол-во структур
	*children = (struct s1*)calloc(size, sizeof(struct s1));					// выделение динамической памяти
	rewind(fp);
	fread(*children, sizeof(struct s1), size, fp);
	//for (int i = 0; i < size; i++)
	//	fscanf(fp, "%s %s %d %s %s %d %d %s %s", (&((childre + i)->surname), &((childre + i)->name), &((childre+ i)->age), &((childre + i)->mas[0].ilness), &((childre + i)->mas[1].NameOfHospitalDoctor), &((childre + i)->mas[2].flag),
	//		&((childre + i)->mas[3].NumberOfHospital), &((childre + i)->mas[4].HospitalAdress), &((childre + i)->mas[5].NameOfDoctor)));		// чтение полей структуры

	fclose(fp);
	*sizeofstruct = size;
	//children = &childrens;
}

void InputInformationInFile(struct s1* children, int num, const char* name)						// запись массива структур в текстовый файл f.txt
{
	FILE* fp = fopen(name, "wb");
	CheckFile(fp);
	fwrite(children, sizeof(struct s1), num, fp);
	//for (int i = 0; i < num; i++)												// цикл для записис массива структур в текстовый файл
	//{
	//	fprintf(fp, "%s %s %d %s %s %d %d %s %s", children[i].surname, children[i].name, children[i].age, children[i].mas[0].ilness, children[i].mas[1].NameOfHospitalDoctor, children[i].mas[2].flag,
	//		children[i].mas[3].NumberOfHospital, children[i].mas[4].HospitalAdress, children[i].mas[5].NameOfDoctor);
	//	fprintf(fp, "\n");
	//}
	fclose(fp);
}

void InputStruct(struct s1** children, int num)									// ввод информации в массив структур 
{
	char c[] = "-";
	struct s1* inf;																// указатель на массив структур
	inf = (struct s1*)calloc(num, sizeof(struct s1));							// выделение памяти под массив структур
	if (inf == NULL)															// проверка на выделение памяти
	{
		printf("\nNo memory has been allocated for the array!\n");
		return;
	}

	for (int i = 0; i < num; i++)												// цикл ввода информации в n структур
	{
		rewind(stdin);
		printf("\nEnter the information about %d child.", i + 1);

		printf("\nEnter the surname of the child: ");
		fgets(inf[i].surname, N, stdin);
		DelEnter(inf[i].surname);
		rewind(stdin);

		printf("Enter the name of the child: ");
		fgets(inf[i].name, N, stdin);
		DelEnter(inf[i].name);
		rewind(stdin);

		printf("Enter the age of the child: ");
		scanf_s("%d", &inf[i].age);
		while (inf[i].age < 0)													// проверка введённой переменной
		{
			rewind(stdin);
			printf("\nERROR! You have entered the wrong data!\nTry again please.\nYour choice is ");
			scanf_s("%d", &inf[i].age);
		}
		rewind(stdin);

		printf("Enter the name of the ilness: ");
		fgets(inf[i].mas[0].ilness, N, stdin);
		DelEnter(inf[i].mas[0].ilness);
		rewind(stdin);

		printf("Enter the name of the hospital doctor: ");
		fgets(inf[i].mas[1].NameOfHospitalDoctor, N, stdin);
		DelEnter(inf[i].mas[1].NameOfHospitalDoctor);
		rewind(stdin);

		printf("Was this child in hospital?\n1. Yes.\n2. No.\nYour choice is ");
		scanf_s("%d", &inf[i].mas[2].flag);
		while (inf[i].mas[2].flag < 1 || inf[i].mas[2].flag > 2)				// проверка введённой переменной
		{
			rewind(stdin);
			printf("\nERROR! You have entered the wrong data!\nTry again please.\nYour choice is ");
			scanf_s("%d", &inf[i].mas[2].flag);
		}
		rewind(stdin);

		if (inf[i].mas[2].flag == 2)											// если ребёнок не лежал в больнице, то следующие поля не нежны	
		{
			inf[i].mas[3].NumberOfHospital = NULL;
			strcpy(inf[i].mas[4].HospitalAdress, c);
			strcpy(inf[i].mas[5].NameOfDoctor, c);
			continue;
		}

		printf("The number of hospital is ");
		scanf_s("%d", &inf[i].mas[3].NumberOfHospital);
		while (inf[i].mas[3].NumberOfHospital <= 0)								// проверка введённой переменной
		{
			rewind(stdin);
			printf("\nERROR! You have entered the wrong data!\nTry again please.\nYour choice is ");
			scanf_s("%d", &inf[i].mas[3].NumberOfHospital);
		}
		rewind(stdin);

		printf("Enter the adress of the hospital: ");
		fgets(inf[i].mas[4].HospitalAdress, K, stdin);
		DelEnter(inf[i].mas[4].HospitalAdress);
		rewind(stdin);

		printf("Enter the name of the child's doctor: ");
		fgets(inf[i].mas[5].NameOfDoctor, N, stdin);
		DelEnter(inf[i].mas[5].NameOfDoctor);
		rewind(stdin);
	}
	*children = inf;
}

void FindChildren(struct s1** ill, struct s1* children, int n, int* numb)		// поиск детей с данным заболеванием
{
	int flag = 0;
	int j = 0;
	int num = 0;
	struct s1* childilness = (struct s1*)calloc(n, sizeof(struct s1));			// выделение динамической памяти для сохранения информации о детях с данным заболеванием
	char* word = (char*)calloc(15, sizeof(char));								// выделение динамической памяти для ввода болезни								
	rewind(stdin);
	printf("\nEnter the ilness, please: ");
	fgets(word, 15, stdin);
	DelEnter(word);
	for (int i = 0; i < n; i++)													// цикл для прохождения по каждой структуре
		if (strcmp(word, children[i].mas[0].ilness) == 0)						// если ребёнок болел данной болезнью, то сохраняем инофрмацию о нём в новый массив структур
		{
			flag = 1;
			num = num + 1;														// кол-во структур в новом массиве структур
			strcpy(childilness[j].surname, children[i].surname);
			strcpy(childilness[j].name, children[i].name);
			childilness[j].age = children[i].age;
			strcpy(childilness[j].mas[0].ilness, children[i].mas[0].ilness);
			strcpy(childilness[j].mas[1].NameOfHospitalDoctor, children[i].mas[1].NameOfHospitalDoctor);
			childilness[j].mas[2].flag = children[i].mas[2].flag;
			if (children[i].mas[2].flag == 2)
			{
				j++;
				continue;
			}

			childilness[j].mas[3].NumberOfHospital = children[i].mas[3].NumberOfHospital;
			strcpy(childilness[j].mas[4].HospitalAdress, children[i].mas[4].HospitalAdress);
			strcpy(childilness[j].mas[5].NameOfDoctor, children[i].mas[5].NameOfDoctor);
			j++;
		}
	childilness = (struct s1*)realloc(childilness, (num * sizeof(struct s1)));	// уменьшение выделенной памяти под num структур

	if (flag == 0)																// если никто из детей не болел данной болезнью, то выводиться сообщение
	{
		printf("\nThere are not children were sicked with this ilness!!!!\n");
		return;
	}

	*ill = childilness;
	*numb = num;
}

void PrintStruct_s1(struct s1* child, int n)									// вывод структуры
{
	printf("\nThe information about children:\n");
	printf("+-----------------+-----------------+-------+----------------------+-----------------+-------------+---------------------------+----------------------+\n");
	printf("| %-15s | %-15s | %-5s | %-20s | %-15s | %-5s | %-25s | %-20s | \n", "Surname", "Name", "Age", "Illness", "DistrictDoctor", "NumHospital", "Address", "Therapist");
	printf("+-----------------+-----------------+-------+----------------------+-----------------+-------------+---------------------------+----------------------+\n");
	for (int i = 0; i < n; i++)
	{
		printf("| %-15s | %-15s | %-5d | %-20s | %-15s | %-11d | %-25s | %-20s | \n", child[i].surname, child[i].name, child[i].age, child[i].mas[0].ilness, child[i].mas[1].NameOfHospitalDoctor, child[i].mas[3].NumberOfHospital, child[i].mas[4].HospitalAdress, child[i].mas[5].NameOfDoctor);
		printf("+-----------------+-----------------+-------+----------------------+-----------------+-------------+---------------------------+----------------------+\n");
	}
}

void CheckFile(FILE* fp)														// функция для проверки открытия файла
{
	if (fp == NULL)																// проверка открытия файла
	{
		printf("ERROR");
		return;
	}
}

void qsortMedList(struct s1* ill, int n) 
{
	qsortRecursion(ill, 0, n - 1);
}

void qsortRecursion(struct s1* ill, int low, int high) 
{
	if (low < high) 
	{
		int pivot_index = patrition(ill, low, high);							//функкция опорного элемента
		qsortRecursion(ill, low, pivot_index - 1);								//рекурсия сортировки от low до pivot_index - 1
		qsortRecursion(ill, pivot_index + 1, high);								//рукурсия сортировки от pivot_index + 1 до high
	}
}

int patrition(struct s1* ill, int low, int high) 
{
	int i = low;
	char* pivot_value = ill[high].surname;										//определение опорного элемента
	for (int j = low; j <= high; j++) 
	{
		if (strcmp(ill[j].surname, pivot_value) < 0) {							//если 1-ая фамилия меньше по алфавиту 2-ой
			swap(&ill[i], &ill[j]);												//поменять местами элементы
			i++;
		}
	}
	swap(&ill[i], &ill[high]);													//поменять местами элемент с индексом i и опорный элемент
	return i;
}

void swap(struct s1* list1, struct s1* list2) 
{
	struct s1 buffer = *list1;
	*list1 = *list2;
	*list2 = buffer;
}

void DelEnter(char str[])														// удаление enter при вводе информации 
{
	int n = strlen(str);
	str[n -1] = '\0';
}

int NumberOfStructs(FILE* fp)
{
	int i = 0;
	char str[256];
	while (fgets(str, 256, fp) != NULL)
		i++;
	return i;
}

int сhoice()																	// выбор действия над программой
{
	int choice;
	printf("\nEnter the 1 to repeat program or any button for exit.\n");
	printf("Your choise is ");
	scanf_s("%d", &choice);
	if (choice == 1)
		return 1;
	else
		return 0;
}