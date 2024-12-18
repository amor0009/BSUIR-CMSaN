#pragma once

int n_rows(void);															// ������� ��� ����� ��-�� ����� �������

int m_columns(void);														// ������� ��� ����� ���-�� �������� �������

int** memory(int n, int m);													// ������� ��� ��������� ������������ ������

void input_row_random(int* mas, int n);										// ������� ��� ����� ������ ��������� �����

void input_row(int* mas, int n);											// ������� ��� ����� ������ � ����������

void input_matr_random(int** matr, int n, int m);							// ������� ��� ����� ������� ��������� �����

void input_matr(int** matr, int n, int m);									// ������� ��� ����� ������� � ����������

void print_row(int* mas, int n);											// ������� ��� ������ ������ �������

void print_matr(int** matr, int n, int m);									// ������� ��� ������ �������

int modul(int a);															// ������� ��� ��������� ������ ��������

int** changed_matr(int** mas, int* row, int* column);						// ������� ��� ��������� �������

int del_i_max_row(int** mas, int* row, int column, int i_max);				// ������� ��� ��������(����� ����� �������) ������ �������, �� ������� ��������� ������������ �� ������ �������

int del_j_max_column(int** mas, int row, int* column, int j_max);			// ������� ��� ��������(����� �������� �������) ������� �������, �� ������� ��������� ������������ �� ������ �������

void choice_option1(int** mas, int n, int m);								// ������� ��� ������ �������� ����� �������

int choice_option2(void);													// ������� ��� ������ �������� ��� ����������

void free_mas(int** mas);													// ������� ��� ������� ������