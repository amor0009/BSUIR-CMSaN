#pragma once

int number_of_symbols();							// ������� ��� ����� ���-�� �������� ������

char* memory(int n);								// ������� ��� ��������� ������������ ������

char* text_input_fgets(char* mas, int n);			// ������� ��� ����� ������ � ������� gets

char* text_input(char* mas, int n);					// ������� ��� ����� ������

int str_len(char* mas);								// ������� ��� ���������� ����� ������

void text_output(char* mas, int n);					// ������� ��� ������ ������

char* changed_text(char* mas, int n);				// ������� ��� ��������� ������

int choice_option();								// ������� ��� ������ �������� ��� ����������
