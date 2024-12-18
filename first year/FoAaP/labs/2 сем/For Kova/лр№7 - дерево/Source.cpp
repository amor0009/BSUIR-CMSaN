#include "Header.h"

void AddTree(struct tree** node, int a)											// функция добавления элемента в дерево
{
	if ((*node) == NULL)														// если указатель на узел равен нулю, то...
	{
		(*node) = (struct tree*)calloc(1, sizeof(struct tree));
		(*node)->data = a;
		(*node)->left = NULL;
		(*node)->right = NULL;
	}
	else if (a < ((*node)->data))												// если же число меньше числа в узле, то идём влево
	{
		if ((*node)->left != NULL)
			AddTree(&((*node)->left), a);
		else
		{
			(*node)->left = (struct tree*)calloc(1, sizeof(struct tree));
			(*node)->left->left = NULL;
			(*node)->left->right = NULL;
			(*node)->left->data = a;
		}
	}

	if (a > ((*node)->data))													// если число больше числа в узле, то идём вправо
	{
		if ((*node)->right != NULL)
			AddTree(&((*node)->right), a);
		else
		{
			(*node)->right = (struct tree*)calloc(1, sizeof(struct tree));
			(*node)->right->right = NULL;
			(*node)->right->left = NULL;
			(*node)->right->data = a;
		}
	}
}

void CreateTree(struct tree** node, int* arr)									// функция создания дерева с помощью чисел из массива arr
{
	FILE* fp = fopen("f.txt", "r+");
	int num = NumberOfNum(fp);
	fclose(fp);
	for (int i = 0; i < num; i++)												// цикл для добавления в дерево num элементов
		AddTree(node, arr[i]);
}

void PrintTree(struct tree* node)												// функция для вывода дерева
{
	if (node != NULL)
	{
		printf("%4d ", node->data);
		PrintTree(node->left);
		PrintTree(node->right);
	}

}

void DelTree(struct tree* node)													// функция для удаления всего дерева
{
	if (node == NULL)
		return;
	DelTree(node->left);
	DelTree(node->right);
	free(node);
}

void StraightObhod(struct tree* node)											// функция прямого обхода дерева
{
	if (node == NULL)
		return;
	printf("%d ", node->data);
	StraightObhod(node->left);
	StraightObhod(node->right);
}

void SimmetrObhod(struct tree* node)											// функция симметричного обхода дерева
{
	if (node == NULL)
		return;
	SimmetrObhod(node->left);
	printf("%d ", node->data);
	SimmetrObhod(node->right);
}

void ObratObhod(struct tree* node)												// функция обратного обхода дерева
{
	if (node == NULL)
		return;
	ObratObhod(node->left);
	ObratObhod(node->right);
	printf("%d ", node->data);
}

int EnterNumber()																// функция ввода числа (кол-ва элементов)
{
	int a;
	printf("Enter the number: ");
	scanf_s("%d", &a);
	return a;
}

int returnFunc()																// функция для возвращения пользовательского меню
{
	int choice;
	printf("\nEnter the any button to return the menu: ");
	scanf_s("%d", &choice);
	rewind(stdin);
	return 1;
}

struct tree* InitialMenu(struct tree* node, int* arr)							// пользовательское меню
{
	system("cls");
	printf("1.Create tree, using information from file.\n");
	printf("2.Enter information in file.\n");
	printf("3.Add tree element.\n");
	printf("4.Delete tree.\n");
	printf("5.Print tree's data.\n");
	printf("6.Straight obhod.\n");
	printf("7.Simmetrichniy obhod.\n");
	printf("8.Obratniy obhod.\n");	
	printf("9.Exit.\n");
	int a;
	int choice = getchar();														// выбор опции
	rewind(stdin);
	switch (choice)
	{
	case '1':																	// создание дерева с помощью чисел из файла f.txt
		system("cls");															// очистка консоли
		CreateTree(&node, arr);
		returnFunc();
		node = InitialMenu(node, arr);											// возвращение пользовательского меню
		break;
	case '2':																	// добавления чисел в файл f.txt
		system("cls");
		EnterInfoInFile();
		arr = ReadInfoFromFile(arr);
		returnFunc();
		node = InitialMenu(node, arr);
		break;
	case '3':																	// добавление элемента в дерево										
		system("cls");															
		a = EnterNumber();
		AddTree(&node, a);
		returnFunc();															
		node = InitialMenu(node, arr);					
		break;
	case '4':																	// удаление дерева							
		system("cls");
		DelTree(node);
		node = NULL;
		returnFunc();
		node = InitialMenu(node, arr);
		break;
	case '5':																	// вывод дерева															
		system("cls");
		PrintTreeLikeTree(node, 0);
		returnFunc();
		node = InitialMenu(node, arr);
		break;
	case '6':																	// прямой обход и вывод дерева					
		system("cls");
		StraightObhod(node);
		printf("\n\n");
		PrintTreeLikeTree(node, 0);
		returnFunc();
		node = InitialMenu(node, arr);
		break;
	case '7':																	// симметричный обход и вывод дерева			
		system("cls");
		SimmetrObhod(node);
		printf("\n\n");
		PrintTreeLikeTree(node, 0);
		returnFunc();
		node = InitialMenu(node, arr);
		break;
	case '8':																	// обратный обход и вывод дерева												
		system("cls");
		ObratObhod(node);
		printf("\n\n");
		PrintTreeLikeTree(node, 0);
		returnFunc();
		node = InitialMenu(node, arr);
		break;
	case '9':																	// закончить выполнение программы
		system("cls");
		printf("Thank you for using our service. Goodbye!");
		break;
	default:																	// при вводе другого варианта, выводится сообщение
		printf("There is no this option. Try again please!");
	}
	return node;
}

int* ReadInfoFromFile(int* arr)													// функция чтения чисел в целочисленный массив из файла f.txt
{
	FILE* fp = fopen("f.txt", "r+");
	if (fp == NULL)
	{
		printf("Can not open file f.txt.\n");
		return;
	}
	int num = NumberOfNum(fp);
	arr = (int*)realloc(arr, num*sizeof(int));
	for(int i = 0; i < num; i++)
	{
		if (fscanf(fp, "%d", &arr[i]) != 1)
		{
			printf("ERROR while reading file f.txt!\n");
			return;
		}
	}
	fclose(fp);
	return arr;
}

int NumberOfNum(FILE* fp)														// поиск кол-ва структур в файле
{
	int i = 0;
	char str[256];
	while (fgets(str, 256, fp) != NULL)											// считываем строки до тез пор, пока не дойдём до конца
		i++;
	fseek(fp, 0, SEEK_SET);
	return i;
}

void EnterInfoInFile()														// запись чисел в файл f.txt
{
	int num;
	int n;
	FILE* fp = fopen("f.txt", "w");
	if (fp == NULL)
	{
		printf("Can not create file f.txt.\n");
		return;
	}
	printf("How mach number do you want to enter?\n");
	scanf("%d", &num);
	while (num <= 0)
	{
		rewind(stdin);
		printf("ERROR!\n");
		scanf("%d", &num);
	}

	for (int i = 0; i < num; i++)
	{
		rewind(stdin);
		printf("Please enter number %d.\n", i + 1);
		scanf("%d", &n);
		fprintf(fp, "%d\n", n);
	}
	fclose(fp);
}

void PrintTreeLikeTree(struct tree* node, int level)							// вывод дерева в виде дерева
{
	if (node == NULL) 
		return;

	PrintTreeLikeTree(node->right, level + 1);									// выводим правое поддерево
	printf("\n");																// переходим на новую строку
	for (int i = 0; i < level; i++) 
		printf("   ");															// выравниваем по отступам

	printf("%d", node->data);													// выводим значение узла
	PrintTreeLikeTree(node->left, level + 1);									// выводим левое поддерево
}