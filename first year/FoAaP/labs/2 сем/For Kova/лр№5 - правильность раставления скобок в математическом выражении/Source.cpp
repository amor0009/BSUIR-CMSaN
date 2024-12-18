#include "Header.h"

struct FILO* push(struct FILO* h, char sym)										// добавление элемента в голову стека
{
	struct FILO* temp = (struct FILO*)calloc(1, sizeof(struct FILO));
	temp->next = NULL;
	temp->data = sym;

	if (h != NULL)																// если голова не пустая, то temp->next на голову и голова равняется temp
		temp->next = h;
	h = temp;
	return h;
}

struct FILO* pop(struct FILO* h)												// удаление элемента стека из головы
{
	if (h != NULL)
		h = h->next;
	return h;
}

int IsEmpty(struct FILO* h)														// функция для проверки головы стека (пустая ли)
{
	if (h == NULL)
		return 0;
	return 1;
}

char peek(struct FILO* h)														// достать символ из головы стека
{
	if (h == NULL)
	{
		printf("There is a mistake!!!");
		exit(-1);
	}
	char sym = h->data;
	return sym;
}

int IsEquel(char a, char b)														// функция для проверки соответсвия типов скобок
{
	if ((a == '(' && b == ')') || (a == '[' && b == ']') || (a == '{' && b == '}') || (a == '<' && b == '>'))
		return 1;
	return 0;

}

char* Input()															// ввод математического выражения
{
	printf("Enter the term, please: ");
	rewind(stdin);
	char* strin = (char*)calloc(30, sizeof(char));
	fgets(strin, 30, stdin);
	return strin;
}

int Check(struct FILO* h, char* string)											// проверка верности раставленных скобок в ведённом математическом выражении
{
	for (int i = 0; i < strlen(string); i++)									// цикл для прохождения по всем элементам математического выражения
	{

		if ((string[0] == ')' || string[0] == ']' || string[0] == '>' || string[0] == '}') && IsEmpty(h) == 0)		// если первая скобка закрывающаяся и стек пустой, то выражение не верно
		{
			printf("There is a mistake!");
			return 0;
		}

		if (string[i] == '(' || string[i] == '[' || string[i] == '<' || string[i] == '{')							// если элемент строки мат выражения - это открывающаяся скобка, то мы её добавляем в стек
			h = push(h, string[i]);

		if ((string[i] == ')' || string[i] == ']' || string[i] == '>' || string[i] == '}') && IsEquel(peek(h), string[i]) == 1)				// если элемент строки мат выражения - это закрывающая скобка, соответствующая типу скобки в стеке, то удаляем открывающуюся скобку из стека
			h = pop(h);
	}

	if (h == NULL)																// если в конце проверки голова пустая, то скобки расставлены верно
	{
		printf("Everything is good!");
		return 1;
	}
	else																		// иначе скобки расставлены неверно
	{
		printf("There is a mistake!");
		return 0;
	}
}

int choice()																	// функция для выбора действия над программой
{
	int choice;
	printf("\nEnter the 1 to repeat program or any button for exit.\n");
	printf("Your choice is ");
	scanf_s("%d", &choice);
	rewind(stdin);
	if (choice == 1)
		return 1;
	else
		return 0;
}