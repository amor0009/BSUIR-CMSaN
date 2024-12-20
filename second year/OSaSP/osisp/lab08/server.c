#define _DEFAULT_SOURCE
#include <arpa/inet.h>
#include <dirent.h>
#include <libgen.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_CONNECTIONS 5

#define QUIT "QUIT\n"
#define BYE "BYE"
#define ECHO "ECHO \""
#define INFO "INFO\n"
#define LIST "LIST\n"
#define CD "CD "

typedef struct client_s {
    int socket;
    char dir[PATH_MAX];
    struct sockaddr_in address;
} client_t;

char root_dir[PATH_MAX];  // Полный путь к коренному каталогу

int create_socket(int port) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Failed to create server socket");
        return -1;
    }

    const int yes = 1;
    // Ошибка "Address already in use"
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))) {
        perror("setsockopt");
        return -1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY; //люой доступный сетевой интерфейс
    server_address.sin_port = htons(port);
    // привязка сокета сервера
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Failed to bind server socket");
        return -1;
    }
    // режим прослушивания входящих соединений
    if (listen(server_socket, MAX_CONNECTIONS) == -1) {
        perror("Failed to listen on server socket");
        return -1;
    }

    return server_socket;
}

void *handle_connection(void *arg) {
    client_t *client = (client_t *)arg;
    DIR *dir;
    struct dirent **namelist;
    int list_count;

    int valread;
    char *answer;
    char path[PATH_MAX], path_buf[PATH_MAX];
    char buffer[1024] = {'\0'},
         lnk[1024] = {'\0'};

    int end = 1;
    struct stat meta; // хранение информации о файле

    do {
        memset(buffer, 0, sizeof(buffer));
        valread = read(client->socket, buffer, 1024);
        printf("%s", buffer);

        if (strncasecmp(buffer, ECHO, strlen(ECHO)) == 0) {
            // Получить первое вхождение кавычки
            answer = strchr(buffer, '\"');

            // Если кавычка была найдена, использовать strtok для извлечения сообщения между кавычками
            if (answer != NULL) {
                answer = strtok(answer + 1, "\"");
                if (answer != NULL) {
                    printf("Message: %s\n", answer);
                }
            }

            send(client->socket, answer, strlen(answer), 0);
        } else if (strcasecmp(buffer, INFO) == 0) {
            FILE *fd;
            size_t size = 256;
            char buffer[256];
            fd = fopen("info", "r");
            if (fd == NULL) {
                perror("File");
                continue;
            }
            memset(buffer, 0, sizeof(buffer));
            fread(buffer, 255, 1, fd);
            printf("%s", buffer);
            send(client->socket, buffer, sizeof(buffer), 0);
            fclose(fd);
        } else if (strncasecmp(buffer, CD, strlen(CD)) == 0) {
            // Работает не прерывая друг друга , без синхронизации , разные текущие каталоги.
            answer = strtok(buffer, " ");
            answer = strtok(NULL, " ");
            strtok(answer, "\n");

            memset(path_buf, 0, sizeof(path_buf));

            strcat(path_buf, client->dir);
            strcat(path_buf, "/");
            strcat(path_buf, answer);
            realpath(path_buf, path_buf);

            if (strncmp(root_dir, path_buf, strlen(root_dir)) == 0) {
                if ((dir = opendir(path_buf)) == NULL) {
                    perror("Dir");
                    strcpy(answer, "/");
                } else {
                    closedir(dir);
                    memset(answer, 0, sizeof(answer));
                    answer = client->dir + strlen(root_dir) + 1;

                    memset(client->dir, 0, sizeof(client->dir));
                    strcpy(client->dir, path_buf);
                }
            } else {
                strcpy(answer, "//");
            }
            if (strcmp(answer, "") == 0)
                strcpy(answer, ".");

            send(client->socket, answer, strlen(answer), 0);
        } else if (strcasecmp(buffer, LIST) == 0) {  // Вывод содержащегося в каталоге
            int a = list_count;
            list_count = scandir(client->dir, &namelist, NULL, alphasort);
            if (list_count < 0) {
                perror("Scandir");
                list_count = a;
                continue;
            }

            send(client->socket, &list_count, sizeof(int), 0);

            for (int i = 0; i < list_count; i++) {
                send(client->socket, namelist[i], sizeof(struct dirent), 0);

                if (namelist[i]->d_type == DT_LNK) {  // Если симлинк

                    memset(lnk, 0, strlen(lnk));
                    readlink(namelist[i]->d_name, lnk, 1024);

                    memset(&meta, 0, sizeof(meta));
                    if (lstat(lnk, &meta) != 0) {
                        perror("LSTAT");
                    }

                    send(client->socket, &meta.st_mode, sizeof(mode_t), 0);
                    send(client->socket, lnk, sizeof(lnk), 0);
                }

                free(namelist[i]);
            }
            free(namelist);
        } else if (strcasecmp(buffer, QUIT) == 0) {
            send(client->socket, BYE, strlen(BYE), 0);
            end = 0;
        } else {
            send(client->socket, "UNKNOWN", strlen("UNKNOWN"), 0);
        }
    } while (end);

    printf("Connection with %d ended\n", client->socket);

    close(client->socket);
    free(client);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        printf("Usage: ./server <port> <root_dir>\n");
        return -1;
    }

    int port = atoi(argv[1]);
    if (port == 0) {
        printf("Invalid port: %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (!opendir(argv[2])) {
        perror("Dir");
        exit(EXIT_FAILURE);
    };
    // получение абсолютного пути
    realpath(argv[2], root_dir);

    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);
    pthread_t connections[MAX_CONNECTIONS];
    int i = 0;

    server_socket = create_socket(port);
    if (server_socket == -1) {
        printf("Create socket");
        return -1;
    }

    printf("Server started on port %d\n", port);

    // Ожидание входящих соединений и создание новых потоков
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len))) {
        if (client_socket == -1) {
            perror("Accept");
            continue;
        }
        printf("New client connected: %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
        client_t *client = (client_t *)malloc(sizeof(client_t));
        strcpy(client->dir, root_dir);
        client->socket = client_socket;
        client->address = client_address;
        pthread_create(&connections[i++], NULL, handle_connection, (void *)client);
        if (i == MAX_CONNECTIONS) {
            break;
        }
    }

    // Ожидание завершения всех потоков
    for (int x = 0; x < i; x++) {
        pthread_join(connections[x], NULL);
    }

    // Закрытие сокета сервера
    close(server_socket);

    return 0;
}
