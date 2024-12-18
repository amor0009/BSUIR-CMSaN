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

struct FILO* push1(struct FILO* h, char sym, int x)								// добавление элемента в голову стека
{
	struct FILO* temp = (struct FILO*)calloc(1, sizeof(struct FILO));
	temp->next = NULL;
	temp->x = x;
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

char* Input()																	// ввод математического выражения
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

	if (h == NULL)																// если в конце проверки голова пустая, то скобки расставлены верно;
		return 1;
	else																		// иначе скобки расставлены неверно
		return 0;
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

void del(char* string, int x)													// функция для удаления символа индекса x из строки
{   
	int i = x;
	while (*(string + i) != '\0') 
	{
		string[i] = string[i + 1];
		i++;
	}
}

int CheckAndReplace(struct FILO* h, char* string)							// функция проверки расстановки скобок в выражении и замена
{																			
	int n = strlen(string);                                                 // длина строки
	int fl = 0;                                                             // флаг для проверки правильности расстановки скобок, 0 - корректно, 1 - некорректно 

	for (int i = 0; i < n; i++)												// цикл по символам строки
	{   
		if (string[i] == '(' || string[i] == '[' || string[i] == '<' || string[i] == '{')                // если встретилась открывающая скобка
			h = push(h, string[i]);											// добавление открывающей скобки в стек
		else if (string[i] == ')' || string[i] == ']' || string[i] == '>' || string[i] == '}')			// если встретилась закрывающая скобка 
		{       
			if (h == NULL)													// если в стеке нет открывающих скобок
			{                                             
				del(string, i);                                             // удаление лишней закрывающей скобки
				i--;                                                        // уменьшение индекса, чтобы не пропустить следующий элемента
				n--;                                                        // уменьшение длины строки
				fl = 1;                                                     // изменение значение индикатора
			}
			else if (IsEquel(peek(h), string[i]) == 0)						// если тип закрывающей и открывающей скобок не совпадает
			{
				if (h->data == '(')
					string[i] = ')'; 										// замена закрывающей скобки на нужный тип
				else if (h->data == '[')
					string[i] = ']';
				else if (h->data == '{')
					string[i] = '}';
				else if (h->data == '<')
					string[i] = '>';
				fl = 1;                                                     // изменение значения индикатора
				h = pop(h);													// удаление открывающей скобки из стека
			}
			else 
				h = pop(h);													// удалить открывающую скобку из стека
		}
	}
	while (h != NULL)														// если в стеке остались лишние закрывающие скобки
	{                                                  
		fl = 1;                                                             // изменение значенмя флага
		del(string, h->x);                                                  // удаление скобки из строк
		h = pop(h);															// удаление скобки из стека
	}
	if (fl == 0)															// если замен, удалений не производилось
	{										
		puts("\nBracket placement is correct.");                              // вывод сообщения о том, что выражение корректно
		return 1;
	}
	else 
	{
		puts("\nBracket placement is incorrect.");							// вывести сообщение о том, что выражение некорректно
		if (string[0] == '\0') { printf("Expression is empty.\n"); }        // если были удалены все символы, вывод сообщения о том, что строка пустая
		else { printf("Corrected expression: %s\n", string); }              // вывести исправленное выражение
		return 0;
	}
}