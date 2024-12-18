#include "parser.h"

void process_input(const char input[256]) {
    char ptr[PATH_MAX];
    strcpy(ptr, input);
    int i = 0;
    while (ptr[i] != '\0') {
        switch (ptr[i]) {
            case '!':
                strcat(current_operation, "-not ");
                break;
            case '&':
                size_flag = 0;
                if (first_flag) {
                    if (braces_flag)
                        strcat(output, "\\) ");
                    strcpy(current_operation, "-and ");
                }
                break;
            case '|':
                size_flag = 0;
                if (first_flag) {
                    if (braces_flag)
                        strcat(output, "\\) ");
                    strcpy(current_operation, "-o ");
                }
                break;
            case '\n':
                return;
            case '{': // Process tags
                {
                    j = 0;
                    while(ptr[i] != '}') {
                        buffer[j] = ptr[i];
                        i++;
                        j++;
                    }

                    if (buffer[0] != '\0') {
                        buffer[0] = '-';
                        strcpy(current_field, buffer);
                        if (strcmp(buffer, "-size")) {
                            size_flag = 1;
                        }
                        braces_flag = 0;
                        token[0] = 0;
                        memset(buffer, '\0', 128);
                    }
                }
                break;
            case '"': // Process name.
                {
                    i++;
                    j = 1;
                    buffer[0] = '"';
                    while(ptr[i] != '"') {
                        buffer[j] = ptr[i];
                        i++;
                        j++;
                    }
                    buffer[j] = ptr[i];
                    if (buffer[0] != '\0') {
                        first_flag = 1;
                        if (!braces_flag) {
                            strcat(output, current_operation);
                            strcpy(current_operation, " ");
                        }
                        if (token[0] != 0 && !size_flag) {
                            strcat(output, "-o ");
                        } else if (token[0] != 0 && size_flag) {
                            strcat(output, "-and ");
                        } else
                            strcat(output, "\\( ");
                        sprintf(token, "%s %s ", current_field, buffer);
                        strcat(output, token);
                        braces_flag = 1;
                        memset(buffer, '\0', 128);
                    }
                }
                break;
            default:
                break;
        }

        i++;
    };
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <input_string>\n", argv[0]);
        return 1;
    }

    process_input(argv[1]);
    if (braces_flag)
        strcat(output, "\\) ");
    printf("%s", output);

    return 0;
}