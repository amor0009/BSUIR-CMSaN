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

struct FILO* push1(struct FILO* h, char sym, int x)								// ���������� �������� � ������ �����
{
	struct FILO* temp = (struct FILO*)calloc(1, sizeof(struct FILO));
	temp->next = NULL;
	temp->x = x;
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

char* Input()																	// ���� ��������������� ���������
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

	if (h == NULL)																// ���� � ����� �������� ������ ������, �� ������ ����������� �����;
		return 1;
	else																		// ����� ������ ����������� �������
		return 0;
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

void del(char* string, int x)													// ������� ��� �������� ������� ������� x �� ������
{   
	int i = x;
	while (*(string + i) != '\0') 
	{
		string[i] = string[i + 1];
		i++;
	}
}

int CheckAndReplace(struct FILO* h, char* string)							// ������� �������� ����������� ������ � ��������� � ������
{																			
	int n = strlen(string);                                                 // ����� ������
	int fl = 0;                                                             // ���� ��� �������� ������������ ����������� ������, 0 - ���������, 1 - ����������� 

	for (int i = 0; i < n; i++)												// ���� �� �������� ������
	{   
		if (string[i] == '(' || string[i] == '[' || string[i] == '<' || string[i] == '{')                // ���� ����������� ����������� ������
			h = push(h, string[i]);											// ���������� ����������� ������ � ����
		else if (string[i] == ')' || string[i] == ']' || string[i] == '>' || string[i] == '}')			// ���� ����������� ����������� ������ 
		{       
			if (h == NULL)													// ���� � ����� ��� ����������� ������
			{                                             
				del(string, i);                                             // �������� ������ ����������� ������
				i--;                                                        // ���������� �������, ����� �� ���������� ��������� ��������
				n--;                                                        // ���������� ����� ������
				fl = 1;                                                     // ��������� �������� ����������
			}
			else if (IsEquel(peek(h), string[i]) == 0)						// ���� ��� ����������� � ����������� ������ �� ���������
			{
				if (h->data == '(')
					string[i] = ')'; 										// ������ ����������� ������ �� ������ ���
				else if (h->data == '[')
					string[i] = ']';
				else if (h->data == '{')
					string[i] = '}';
				else if (h->data == '<')
					string[i] = '>';
				fl = 1;                                                     // ��������� �������� ����������
				h = pop(h);													// �������� ����������� ������ �� �����
			}
			else 
				h = pop(h);													// ������� ����������� ������ �� �����
		}
	}
	while (h != NULL)														// ���� � ����� �������� ������ ����������� ������
	{                                                  
		fl = 1;                                                             // ��������� �������� �����
		del(string, h->x);                                                  // �������� ������ �� �����
		h = pop(h);															// �������� ������ �� �����
	}
	if (fl == 0)															// ���� �����, �������� �� �������������
	{										
		puts("\nBracket placement is correct.");                              // ����� ��������� � ���, ��� ��������� ���������
		return 1;
	}
	else 
	{
		puts("\nBracket placement is incorrect.");							// ������� ��������� � ���, ��� ��������� �����������
		if (string[0] == '\0') { printf("Expression is empty.\n"); }        // ���� ���� ������� ��� �������, ����� ��������� � ���, ��� ������ ������
		else { printf("Corrected expression: %s\n", string); }              // ������� ������������ ���������
		return 0;
	}
}