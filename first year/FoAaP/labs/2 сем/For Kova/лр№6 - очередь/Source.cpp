#include "Header.h"

void PushHead(struct LIST** head, struct LIST** tail, int x)					// ������� ���������� � ������ ������
{
	struct LIST* temp;
	temp = (struct LIST*)calloc(1, sizeof(struct LIST));
	temp->ring = NULL;
	temp->next = NULL;
	temp->data = x;
	if (*head == NULL)															// ���� ������ ������
	{
		*head = temp;
		*tail = temp;
	}
	else																		// ���� ������ �� ������
	{
		temp->next = *head;
		*head = temp;
	}
}

void PopHead(struct LIST** head, struct LIST** tail)							// ������� �������� � ������ ������
{
	if (*head != NULL)															// ���� ������ �� ������
	{
		struct LIST* temp;
		temp = (struct LIST*)calloc(1, sizeof(struct LIST));
		*head = (*head)->next;
	}
	else																		// ���� ������ ������
		tail = NULL;
}

void PushTail(struct LIST** head, struct LIST** tail, int x)					// ������� ���������� �������� � ����� ������
{
	struct LIST* temp;
	temp = (struct LIST*)calloc(1, sizeof(struct LIST));
	temp->next = NULL;
	temp->data = x;
	if (*head == NULL)															// ���� ������ ������
	{
		*head = temp;
		*tail = temp;
	}
	else																		// �����
	{
		(*tail)->next = temp;
		(*tail) = temp;
	}
}

void PopTail(struct LIST** head, struct LIST** tail)							// ������� �������� �������� � ������ ������
{
	struct LIST* temp;
	temp = (*head);
	if ((*tail) != (*head))														// ���� ����� �� ��������� ������
	{
		while (temp->next != (*tail))											// ���� �� ����� �� ������
			temp = temp->next;
		*tail = temp;
		(*tail)->next = NULL;
	}
	else																		// �����
	{
		*tail = NULL;
		*head = NULL;
	}
}

struct Ring* pushRing(struct Ring* p, int x)									// ������� ���������� �������� � ������
{
	struct Ring* temp = (struct Ring*)calloc(1, sizeof(struct Ring));
	temp->next = NULL;
	temp->prev = NULL;
	temp->data = x;
	if (p == NULL)																// ���� ������ ������
	{
		temp->next = temp;
		temp->prev = temp;
		p = temp;
	}
	else																		// �����
	{
		temp->next = p->next;
		p->next->prev = temp;
		p->next = temp;
		temp->prev = p;
		p = temp;
	}
	return p;
}

struct Ring* popRing(struct Ring* p)											// ������� �������� �������� ������
{
	if (p == NULL)																// ���� ������ ������
	{
		printf("Empty\n");
		return NULL;
	}
	if (p == p->next)															// ���� ������ ������� �� ������ ��������
	{
		free(p);
		return NULL;
	}
	else																		// �����
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

void PrintRing1(struct Ring* p)													// ������� ������ ������ 1
{
	struct Ring* temp = (struct Ring*)calloc(1, sizeof(struct Ring));
	temp = p;
	if (p == NULL)																// ���� ������ ������
		printf("Empty\n");
	else																		// �����
	{
		printf("Ring's elements: ");
		do
		{
			printf("%d ", temp->data);
			temp = temp->next;
		} while (temp != p);													// ���� ��������� ��������� �� ������ �� ������ ������
	}
}

void PrintRing2(struct Ring* p)													// ������� ������ ������ 2
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

int Number()																	// ������� ����� ���-�� �����
{
	int num;
	printf("Enter the number of elements you would like to enter: ");
	scanf("%d", &num);
	while (num <= 0)															// ��������
	{
		rewind(stdin);
		printf("\nYou have entered the wrong data.\nTry again please.\n");
		scanf("%d", &num);
	}
	return num;
}

int EnterNumber(int i)															// ������� ����� �����
{
	int num;
	printf("Enter the %d number: ", i);
	scanf("%d", &num);
	printf("\n");
	return num;
}

int NumberOfCurrentList()														// ������� ����� ������ �������� �������� ������
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

struct LIST* FindAndPushCurrentList(struct LIST* head, int position)			// ������� ���������� �������� ������ � ���������� �������� � ��� ������
{
	struct LIST* prev_node = NULL;
	struct LIST* current_node = head;
	int i = 1;

	if (position > NumberOfLists(head))											// ���� ������ �������� �������� ������ ������ ���-�� ��������� ������
	{
		printf("There is no that list's element\n");
		return;
	}

	while (i != position)														// ��������� �������� �������� ������
	{
		prev_node = current_node;
		current_node = current_node->next;
		i++;
	}
	
	int a = EnterNumber(1);
	current_node->ring = pushRing(current_node->ring, a);						// ���������� �������� � ������ �������� ������
	return head;
}

struct LIST* FindCurrentList(struct LIST* head, int position)					// ������� ���������� �������� �������� ������
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

struct LIST* FindAndPopCurrentList(struct LIST* head, int position)				// ������� ���������� �������� �������� ������ � �������� �������� ��� ������
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

	current_node->ring = popRing(current_node->ring);							// �������� ��-�� ������
	return head;
}

void FindAndPrintRingCurrentList(struct LIST* head, int position)				// ������� ���������� �������� ��-�� ������ � ����� ��� ������
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

	PrintRing1(current_node->ring);												// ����� ������ �������� ��-�� ������
}

int NumberOfLists(struct LIST* head)											// ������� ���������� ���-�� ��-�� ������
{
	struct LIST* n = head;
	int i = 0;
	while (n != NULL)															// ���� �� ����� �� ����� ������
	{
		i++;
		n = n->next;															// ���������� �� ��������� ��-� ������
	}
	free(n);
	return i;
}

int NumberOfElementsInRing(struct Ring* ring)									// ������� ���������� ���-�� ��-�� � ������
{
	struct Ring* temp = ring;
	int i = 0;
	if (ring == NULL)															// ���� ������ ������
	{
		printf("Empty!\n");
		return 0;
	}
	else																		// �����
	{
		do
		{
			i++;
			temp = temp->next;
		} while (temp != ring);
	}
	return i;
}

int returnFunc()																// ������� ��� ����������� ����������������� ����
{
	int choice;
	printf("\nEnter the any button to return the menu: ");
	scanf_s("%d", &choice);
	rewind(stdin);
	return 1;
}

void InitialMenu(struct LIST** head, struct LIST** tail)						// ���������������� ����
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
	int choice = getchar();														// ����� �����
	rewind(stdin);
	switch (choice)
	{
	case '1':																	// �������� ������
		system("cls");
		n = Number();
		for (int i = 1; i <= n; i++)											// ���� ��� �������� n ��-��
		{
			a = EnterNumber(i);
			PushHead(head, tail, a);
		}
		returnFunc();
		InitialMenu(head, tail);
		break;
	case '2':																	// �������� ������� � ������
		system("cls");
		position = NumberOfCurrentList();
		*head = FindAndPushCurrentList(*head, position);
		returnFunc();
		InitialMenu(head, tail);
		break;
	case '3':																	// �������� �������� ������							
		system("cls");															// ������� �������
		position = NumberOfCurrentList();
		*head = FindAndPopCurrentList(*head, position);
		returnFunc();															
		InitialMenu(head, tail);												
		break;
	case '4':																	// ����� ��������� ������												
		system("cls");
		position = NumberOfCurrentList();
		FindAndPrintRingCurrentList(*head, position);
		returnFunc();
		InitialMenu(head, tail);
		break;
	case '5':																	// ������� ������� ������ � ������													
		system("cls");
		PopTail(head, tail);
		returnFunc();
		InitialMenu(head, tail);
		break;
	case '6':																	// ������������ ��������� ������ �� ��������� �������														
		system("cls");
		removeElement(head, tail);
		printf("The elements are successfully removed.\n");
		returnFunc();
		InitialMenu(head, tail);
		break;
	case '7':																	// ��������� ���������� ���������
		system("cls");
		printf("Thank you for using our service. Goodbye!");
		break;
	default:																	// ��� ����� ������� ��������, ��������� ���������
		printf("There is no this option. Try again please!");
	}
}

int TakeData(struct Ring* p)													// ������� ������ ���������� � ���. ���� ������
{
	struct Ring* temp = (struct Ring*)calloc(1, sizeof(struct Ring));
	temp = p;
	if (p == NULL)																// ���� ������ ������
	{
		printf("This ring is empty\n");
		return;
	}
	else																		// �����
		return temp->data;
}

void removeElement(struct LIST** head, struct LIST** tail)						// ������� ������������� ��������� ������ �� ���������
{   
	int num = NumberOfCurrentList();											// ������ �������� �������� ������
	int number = NumberOfLists(*head);											// ���-�� ��������� ������

	struct LIST* tmp = FindCurrentList(*head, num);								// ��������� ��������� �� ������� ������� ������
	struct LIST* temp = (*head);											
	int Numb = NumberOfElementsInRing(tmp->ring);								// ���-�� ��������� ������ �������� �������� ������
	int a;
	for(int i = 0; i < Numb; i++)												// ���� ��� ������������� ���� ���������
	{
		if (temp == tmp)														// ���� ��������� ���� �� ������� ������� ������, �� ���������� �� ��������� � ���������� ��������� �����
		{
			temp = temp->next;
			i--;
			continue;
		}

		if (temp == NULL)														// ���� ��������� ����� NULL, �� ���������� �� ������ ������
			temp = (*head);

		a = TakeData(tmp->ring);												// �������� �������� ��� ���� ������ �������� ��-��
		tmp->ring = tmp->ring->next;											// ���������� �� ��������� ������� ������

		temp->ring = pushRing(temp->ring, a);									// ��������� ���������� �������� � ������� ������

		temp = temp->next;														// ���������� �� ��������� ������� ������
	}
}