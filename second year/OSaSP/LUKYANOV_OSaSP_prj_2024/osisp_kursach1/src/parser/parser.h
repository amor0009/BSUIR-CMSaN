#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>

char current_field[128];
char token[PATH_MAX];
char output[PATH_MAX];
char braces_flag = 0;
char size_flag = 0;
char first_flag = 0;
char current_operation[20];
char buffer[128];
int j = 0;

//Парсер
void process_input(const char input[256]);