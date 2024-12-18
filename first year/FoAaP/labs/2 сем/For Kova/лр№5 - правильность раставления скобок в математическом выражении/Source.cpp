#include "Header.h"

struct FILO* push(struct FILO* h, char sym)										// ���������� �������� � ������ �����
{
	struct FILO* temp = (struct FILO*)calloc(1, sizeof(struct FILO));
	temp->next = NULL;
	temp->data = sym;

	if (h != NULL)																// ���� ������ �� ������, �� temp->next �� ������ � ������ ��������� temp
		temp->next = h;
	h = temp;
	return h;
}

struct FILO* pop(struct FILO* h)												// �������� �������� ����� �� ������
{
	if (h != NULL)
		h = h->next;
	return h;
}

int IsEmpty(struct FILO* h)														// ������� ��� �������� ������ ����� (������ ��)
{
	if (h == NULL)
		return 0;
	return 1;
}

char peek(struct FILO* h)														// ������� ������ �� ������ �����
{
	if (h == NULL)
	{
		printf("There is a mistake!!!");
		exit(-1);
	}
	char sym = h->data;
	return sym;
}

int IsEquel(char a, char b)														// ������� ��� �������� ����������� ����� ������
{
	if ((a == '(' && b == ')') || (a == '[' && b == ']') || (a == '{' && b == '}') || (a == '<' && b == '>'))
		return 1;
	return 0;

}

char* Input()															// ���� ��������������� ���������
{
	printf("Enter the term, please: ");
	rewind(stdin);
	char* strin = (char*)calloc(30, sizeof(char));
	fgets(strin, 30, stdin);
	return strin;
}

int Check(struct FILO* h, char* string)											// �������� �������� ������������ ������ � ������� �������������� ���������
{
	for (int i = 0; i < strlen(string); i++)									// ���� ��� ����������� �� ���� ��������� ��������������� ���������
	{

		if ((string[0] == ')' || string[0] == ']' || string[0] == '>' || string[0] == '}') && IsEmpty(h) == 0)		// ���� ������ ������ ������������� � ���� ������, �� ��������� �� �����
		{
			printf("There is a mistake!");
			return 0;
		}

		if (string[i] == '(' || string[i] == '[' || string[i] == '<' || string[i] == '{')							// ���� ������� ������ ��� ��������� - ��� ������������� ������, �� �� � ��������� � ����
			h = push(h, string[i]);

		if ((string[i] == ')' || string[i] == ']' || string[i] == '>' || string[i] == '}') && IsEquel(peek(h), string[i]) == 1)				// ���� ������� ������ ��� ��������� - ��� ����������� ������, ��������������� ���� ������ � �����, �� ������� ������������� ������ �� �����
			h = pop(h);
	}

	if (h == NULL)																// ���� � ����� �������� ������ ������, �� ������ ����������� �����
	{
		printf("Everything is good!");
		return 1;
	}
	else																		// ����� ������ ����������� �������
	{
		printf("There is a mistake!");
		return 0;
	}
}

int choice()																	// ������� ��� ������ �������� ��� ����������
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