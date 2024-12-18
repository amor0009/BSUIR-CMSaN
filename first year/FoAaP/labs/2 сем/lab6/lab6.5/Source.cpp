#include "Header.h"

void PushHead(struct LIST** head, struct LIST** tail, int x)					// функция добавления в голову списка
{
	struct LIST* temp;
	temp = (struct LIST*)calloc(1, sizeof(struct LIST));
	temp->ring = NULL;
	temp->next = NULL;
	temp->data = x;
	if (*head == NULL)															// если голова пустая
	{
		*head = temp;
		*tail = temp;
	}
	else																		// если голова не пустая
	{
		temp->next = *head;
		*head = temp;
	}
}

void PopHead(struct LIST** head, struct LIST** tail)							// функция удаление с головы списка
{
	if (*head != NULL)															// если голова не пустая
	{
		struct LIST* temp;
		temp = (struct LIST*)calloc(1, sizeof(struct LIST));
		*head = (*head)->next;
	}
	else																		// если голова пустая
		tail = NULL;
}

void PushTail(struct LIST** head, struct LIST** tail, int x)					// функция добавление элемента в хвост списка
{
	struct LIST* temp;
	temp = (struct LIST*)calloc(1, sizeof(struct LIST));
	temp->next = NULL;
	temp->data = x;
	if (*head == NULL)															// если голова пустая
	{
		*head = temp;
		*tail = temp;
	}
	else																		// иначе
	{
		(*tail)->next = temp;
		(*tail) = temp;
	}
}

void PopTail(struct LIST** head, struct LIST** tail)							// функция удаление элемента с хвоста списка
{
	struct LIST* temp;
	temp = (*head);
	if ((*tail) != (*head))														// если хвост не равняется голове
	{
		while (temp->next != (*tail))											// пока не дойдём до хвоста
			temp = temp->next;
		*tail = temp;
		(*tail)->next = NULL;
	}
	else																		// иначе
	{
		*tail = NULL;
		*head = NULL;
	}
}

struct Ring* pushRing(struct Ring* p, int x)									// функция добавление элемента в кольцо
{
	struct Ring* temp = (struct Ring*)calloc(1, sizeof(struct Ring));
	temp->next = NULL;
	temp->prev = NULL;
	temp->data = x;
	if (p == NULL)																// если кольцо пустое
	{
		temp->next = temp;
		temp->prev = temp;
		p = temp;
	}
	else																		// иначе
	{
		temp->next = p->next;
		p->next->prev = temp;
		p->next = temp;
		temp->prev = p;
		p = temp;
	}
	return p;
}

struct Ring* popRing(struct Ring* p)											// функция удаление элемента кольца
{
	if (p == NULL)																// если кольцо пустое
	{
		printf("Empty\n");
		return NULL;
	}
	if (p == p->next)															// если кольцо состоит из одного элемента
	{
		free(p);
		return NULL;
	}
	else																		// иначе
	{
		struct Ring* temp = (struct Ring*)calloc(1, sizeof(struct Ring));
		temp = p->next;
		p->next = temp->next;
		temp->next->prev = p;
		free(temp);
		return p;
	}
}

//struct Ring* popAllRing(struct Ring* p)
//{
//	int number = NumberOfElementsInRing(p);
//	for (int i = 0; i < number; i++)
//		popRing(p);
//	p = NULL;
//	return p;
//}

void PrintRing1(struct Ring* p)													// функция вывода кольца 1
{
	struct Ring* temp = (struct Ring*)calloc(1, sizeof(struct Ring));
	temp = p;
	if (p == NULL)																// если кольцо пустое
		printf("Empty\n");
	else																		// иначе
	{
		printf("Ring's elements: ");
		do
		{
			printf("%d ", temp->data);
			temp = temp->next;
		} while (temp != p);													// пока временный указатель не станет на начало кольца
	}
}

void PrintRing2(struct Ring* p)													// функция вывода кольца 2
{
	struct Ring* temp = (struct Ring*)calloc(1, sizeof(struct Ring));
	temp = p;
	if (p == NULL)
		printf("Empty\n");
	else
	{
		printf("Ring's elements: ");
		do
		{
			printf("%d ", temp->data);
			temp = temp->prev;
		} while (temp != p);
	}
}

int Number()																	// функция ввода кол-ва чисел
{
	int num;
	printf("Enter the number of elements you would like to enter: ");
	scanf("%d", &num);
	while (num <= 0)															// проверка
	{
		rewind(stdin);
		printf("\nYou have entered the wrong data.\nTry again please.\n");
		scanf("%d", &num);
	}
	return num;
}

int EnterNumber(int i)															// функция ввода числа
{
	int num;
	printf("Enter the %d number: ", i);
	scanf("%d", &num);
	printf("\n");
	return num;
}

int NumberOfCurrentList()														// функция ввода индека текущего элемента списка
{
	int position;
	printf("Enter the number of element of the LIST to work with elements in RING: ");
	scanf("%d", &position);
	printf("\n");
	while (position <= 0)
	{
		rewind(stdin);
		printf("\nYou have entered the wrong data.\nTry again please.\n");
		scanf("%d", &position);
	}
	return position;
}

struct LIST* FindAndPushCurrentList(struct LIST* head, int position)			// функция нахождения текущего списка и добавления элемента в его кольцо
{
	struct LIST* prev_node = NULL;
	struct LIST* current_node = head;
	int i = 1;

	if (position > NumberOfLists(head))											// если индекс текущего элемента списка больше кол-ва элементов списка
	{
		printf("There is no that list's element\n");
		return;
	}

	while (i != position)														// получение текущего элемента списка
	{
		prev_node = current_node;
		current_node = current_node->next;
		i++;
	}
	
	int a = EnterNumber(1);
	current_node->ring = pushRing(current_node->ring, a);						// добавление элемента в кольцо текущего списка
	return head;
}

struct LIST* FindCurrentList(struct LIST* head, int position)					// функция нахождения текущего элемента списка
{
	struct LIST* prev_node = NULL;
	struct LIST* current_node = head;
	int i = 1;

	if (position > NumberOfLists(head))
	{
		printf("There is no that list's element\n");
		return;
	}

	while (i != position)
	{
		prev_node = current_node;
		current_node = current_node->next;
		i++;
	}

	return current_node;
}

struct LIST* FindAndPopCurrentList(struct LIST* head, int position)				// функция нахождения текущего элемента списка и удаления элемента его кольца
{
	struct LIST* prev_node = NULL;
	struct LIST* current_node = head;
	int i = 1;

	if (position > NumberOfLists(head))
	{
		printf("There is no that list's element");
		return;
	}

	while (i != position)
	{
		prev_node = current_node;
		current_node = current_node->next;
		i++;
	}

	current_node->ring = popRing(current_node->ring);							// удаление эл-та кольца
	return head;
}

void FindAndPrintRingCurrentList(struct LIST* head, int position)				// функция нахождения текущего эл-та списка и вывод его кольца
{
	struct LIST* prev_node = NULL;
	struct LIST* current_node = head;
	int i = 1;

	if (position > NumberOfLists(head))
	{
		printf("There is no that list's element");
		return;
	}

	while (i != position)
	{
		prev_node = current_node;
		current_node = current_node->next;
		i++;
	}

	PrintRing1(current_node->ring);												// вывод кольца текущего эл-та списка
}

int NumberOfLists(struct LIST* head)											// функция нахождения кол-ва эл-ов списка
{
	struct LIST* n = head;
	int i = 0;
	while (n != NULL)															// пока не дойдём до конца списка
	{
		i++;
		n = n->next;															// становимся на следующий эл-т списка
	}
	free(n);
	return i;
}

int NumberOfElementsInRing(struct Ring* ring)									// функция нахождения кол-ва эл-ов в кольце
{
	struct Ring* temp = ring;
	int i = 0;
	if (ring == NULL)															// если кольцо пустое
	{
		printf("Empty!\n");
		return 0;
	}
	else																		// иначе
	{
		do
		{
			i++;
			temp = temp->next;
		} while (temp != ring);
	}
	return i;
}

int returnFunc()																// функция для возвращения пользовательского меню
{
	int choice;
	printf("\nEnter the any button to return the menu: ");
	scanf_s("%d", &choice);
	rewind(stdin);
	return 1;
}

void InitialMenu(struct LIST** head, struct LIST** tail)						// пользовательское меню
{
	system("cls");
	printf("1.Create LIST.\n");
	printf("2.Add element in RING.\n");
	printf("3.Delete element in RING.\n");
	printf("4.Print elements of RING.\n");
	printf("5.Delete LIST element.\n");
	printf("6.RASPRED.\n");
	printf("7.Exit.\n");
	int a;
	int n;
	int position;
	struct LIST* temp = (struct LIST*)calloc(1, sizeof(struct LIST));
	int choice = getchar();														// выбор опции
	rewind(stdin);
	switch (choice)
	{
	case '1':																	// создание списка
		system("cls");
		n = Number();
		for (int i = 1; i <= n; i++)											// цикл для создания n эл-ов
		{
			a = EnterNumber(i);
			PushHead(head, tail, a);
		}
		returnFunc();
		InitialMenu(head, tail);
		break;
	case '2':																	// добавить элемент в кольцо
		system("cls");
		position = NumberOfCurrentList();
		*head = FindAndPushCurrentList(*head, position);
		returnFunc();
		InitialMenu(head, tail);
		break;
	case '3':																	// удаление элемента кольца							
		system("cls");															// очитска консоли
		position = NumberOfCurrentList();
		*head = FindAndPopCurrentList(*head, position);
		returnFunc();															
		InitialMenu(head, tail);												
		break;
	case '4':																	// вывод элементов кольца												
		system("cls");
		position = NumberOfCurrentList();
		FindAndPrintRingCurrentList(*head, position);
		returnFunc();
		InitialMenu(head, tail);
		break;
	case '5':																	// удалить элемент списка с хвоста													
		system("cls");
		PopTail(head, tail);
		returnFunc();
		InitialMenu(head, tail);
		break;
	case '6':																	// распредление элементов кольца по остальным кольцам														
		system("cls");
		removeElement(head, tail);
		printf("The elements are successfully removed.\n");
		returnFunc();
		InitialMenu(head, tail);
		break;
	case '7':																	// закончить выполнение программы
		system("cls");
		printf("Thank you for using our service. Goodbye!");
		break;
	default:																	// при вводе другого варианта, выводится сообщение
		printf("There is no this option. Try again please!");
	}
}

int TakeData(struct Ring* p)													// функция взятия информацию с инф. поля кольца
{
	struct Ring* temp = (struct Ring*)calloc(1, sizeof(struct Ring));
	temp = p;
	if (p == NULL)																// если кольцо пустое
	{
		printf("This ring is empty\n");
		return;
	}
	else																		// иначе
		return temp->data;
}

void removeElement(struct LIST** head, struct LIST** tail)						// функция распределения элементов кольца по остальным
{   
	int num = NumberOfCurrentList();											// индекс текущего элемента списка
	int number = NumberOfLists(*head);											// кол-во элементов списка

	struct LIST* tmp = FindCurrentList(*head, num);								// получение указателя на текущий элемент списка
	struct LIST* temp = (*head);											
	int Numb = NumberOfElementsInRing(tmp->ring);								// кол-во элементов кольца текущего элемента списка
	int a;
	for(int i = 0; i < Numb; i++)												// цикл для распределения всех элементов
	{
		if (temp == tmp)														// если указатель стал на текущий элемент списка, то становимся на следующий и пропускаем иттерацию цикла
		{
			temp = temp->next;
			i--;
			continue;
		}

		if (temp == NULL)														// если указатель равен NULL, то становимся на голову списка
			temp = (*head);

		a = TakeData(tmp->ring);												// получаем значение инф поля кольца текущего эл-та
		tmp->ring = tmp->ring->next;											// становимся на следующий элемент кольца

		temp->ring = pushRing(temp->ring, a);									// добавляем полученное значение в элемент списка

		temp = temp->next;														// станвоимся на следующий элемент списка
	}
}