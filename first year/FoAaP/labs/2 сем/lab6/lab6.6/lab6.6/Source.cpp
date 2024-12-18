#include "Header.h"

void CreationOfTheList(struct LIST** ptr, int x)									// добавление элемента в конец однонаправленной очереди
{
	struct LIST* temp;
	printf("Creation of the list.\n");
	do
	{
		struct LIST* temp;
		temp = (struct LIST*)malloc(sizeof(struct LIST));
		temp->data = x;
		temp->next = (*ptr)->next;
		temp->prev = (*ptr);
		struct LIST* next_ptr = (*ptr)->next;
		(*ptr)->next = temp;
		if (next_ptr)
			next_ptr->prev = temp;
	} while (getchar() == 'y');
}

void push_after(struct LIST** ptr, int x)									// добавление элемента в конец однонаправленной очереди
{
	struct LIST* temp;
	temp = (struct LIST*)malloc(sizeof(struct LIST));
	temp->data = x;
	temp->next = (*ptr)->next;
	temp->prev = (*ptr);
	struct LIST* next_ptr = (*ptr)->next;
	(*ptr)->next = temp;
	if (next_ptr)
		next_ptr->prev = temp;
}

void pop_after(struct LIST** ptr)												// удаление элемента однонапрваленной очереди
{
	struct LIST* temp = (*ptr)->next;
	if (temp != NULL)
	{
		struct LIST* next_ptr = temp->next;
		(*ptr)->next = next_ptr;
		if (next_ptr)
			next_ptr->prev = *ptr;
	}
	else
		(*ptr)->next = NULL;
}

void push(struct Ring** p)										// добавить элемент в однонапрваленное кольцо
{
	struct Ring* temp;
	printf("Creation of the ring.\n");
	do 
	{
		temp = (struct Ring*)calloc(1, sizeof(struct Ring));
		temp->next = NULL;
		printf("Enter the information in element of ring.\n");
		scanf("%d", &(temp->data));

		if (*p == NULL)
		{
			temp->next = temp;
			*p = temp;
		}
		else
		{
			temp->next = (*p)->next;
			(*p)->next = temp;
		}
		printf("Continue (y/n): ");
		rewind(stdin);
		free(temp);
	} while (getchar() == 'y');
}

struct Ring* pop(struct Ring* p)												// удалить элемент однонапрваленного кольца
{
	if (p == NULL)
	{
		printf("This ring is empty!!!\n");
		return p;
	}

	if (p == p->next)
	{
		free(p);
		return NULL;
	}
	else
	{
		struct Ring* temp;
		temp = p->next;
		p->next = p->next->next;
		free(temp);
		return p;
	}
}

void PrintRing(struct Ring* p)													// просмотр элементов кольца
{
	struct Ring* temp = p;
	if (p == NULL)
	{
		printf("This ring is empty!!!\n");
		exit(1);
	}
	else
	{
		do
		{
			printf("%3d", temp->data);
			temp = temp->next;
		} while (temp != p);
	}
	printf("\n");
}

void Menu(struct Ring** p, struct LIST** ptr, int x)
{
	while (1)
	{
		printf("1. Add Ring.\n");
		printf("2. Delete Ring.\n");
		printf("3. Print elements of ring.\n");
		printf("4. Delete element of ochered.\n");
		printf("5. Raspred.");
		printf("6. Finish the program.\n");
		rewind(stdin);
		switch (getchar())
		{
			case '1': push(*p, x);
			case '2': *p = pop(*p);
			case '3': PrintRing(*p);
			case '4': pop_after(*ptr);
			case '5': 
			case '6': exit(1);
			default: printf("Mistake. Try again please!\n");
		}
	}
}