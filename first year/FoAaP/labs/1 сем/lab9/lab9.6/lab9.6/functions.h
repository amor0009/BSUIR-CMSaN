#pragma once

int number_of_rows();                                                        // ���� ���-�� ����� 

int number_of_symbols();                                                     // ������� ��� ����� ���-�� �������� � i-�� ������

char** memory(int n, int m);                                                 // �������� ������������ ������

void row_input(char* mas, int m);                                            // ���� ������ 

void row_fgets_input(char* mas, int m);                                      // ���� ������ � ������ fgets

char** text_input(char** mas, int n, int m);                                 // ���� ������ (����s �����)

char** text_fgets_input(char** mas, int n, int m);                           // ���� ������( ���� �����) � ������� fgets

int str_len(char* mas);                                                      // ����� i-� ������

void row_output(char* mas, int n);                                           // ����� ������

void row_fgets_output(char* mas, int n);                                     // ����� ������ � ������� puts

void text_output(char** mas, int n, int m);                                  // ������ ���� �����

void text_puts_output(char** mas, int n, int m);                             // ������ ���� ����� � ������� puts

char* changed_text(char* mas, int n);										 // ��������� ������

char** changed_text1(char** mas, int m, int n);                              // ��������� ������

int sum_salary(char* mas);													 // ������� ��� �������� �������� � ����� � �� �����

char** changed_text2(char** mas, int n, int m);                              // ���������� ����� ������ �� ��������

char** changed_text3(char** mas, int n, int m);								 // ���������� ����� ������ �� ����� ���� �������

char** choice_option1_and_changing(char** mas, int n, int m);				 // ����� ������� ���������� � � ����������

int choice_option2();                                                        // ������� ��� ������ �������� ��� ����������

int sum(int k, ...);                                                         // ����� � ������� ������� � ���������� ���-��� ����������

int fib(int n);                                                              // ���������� ����� �������� (��������)