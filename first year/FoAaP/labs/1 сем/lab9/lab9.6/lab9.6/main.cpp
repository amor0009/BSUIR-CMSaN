#include "functions.h"
#include <stdlib.h>
#include "functions.h"

int main()
{
	int opt1, opt2 = 2;
	do
	{
		system("cls");																// ������� ���� ������
		int n = number_of_rows();													// ���� ���-�� ����� ������
		int m = number_of_symbols();												// ���� ���-�� �������� ������
		char** text = memory(n, m);                                                 // �������� ������������ ������
		text = text_input(text, n, m);												// ���� ������ (���� �����)		
		text = changed_text1(text, n, m);											// ��������� �������� � ��������� ����
		text = choice_option1_and_changing(text, n, m);								// ����� ���������� � � ����������
		text_output(text, n, m);													// ����� ������
		opt2 = choice_option2();                                                    // ������� ��� ������ �������� ��� ����������
	} while (opt2 == 0);
	return 0;
}