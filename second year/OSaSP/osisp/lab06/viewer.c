#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdint.h>

#define WIDTH 12
#define HEIGHT 50

struct index_string {
	double time_mark; 
	uint64_t recno;
};

int kbhit() {
	  struct termios oldt, newt;
	  int ch, oldf;
	  tcgetattr(STDIN_FILENO, &oldt);
	  newt = oldt;
	  newt.c_lflag &= ~(ICANON | ECHO);
	  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	  ch = getchar();
	  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	  fcntl(STDIN_FILENO, F_SETFL, oldf);
	  if (ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	  }
	  return 0;
}

int main(int argc, char** argv)
{
	if (!argv[1]) {
		fputs("No filename\n\0", stderr);
		return -1;
	}
	FILE *file = fopen(argv[1], "rb");

	if (!file) {
		perror("Filename is incorrect\n");
		return -1;
	}
	system("clear");
	int fd = open("/dev/tty", O_RDWR);

	struct index_string to_print;
	int width_index = 1;
	int height_index = 0;
	char need_print = 1;
	unsigned int offset = 0;
	while (1) {
		if (kbhit() && !need_print) {
			char ch = getchar();
			if (ch == 's') {
				system("clear");
				need_print = 1;
				height_index = 0;
				width_index = 1;
			}
			if (ch == 'w') {
				int new_offset = ((offset-(WIDTH*HEIGHT*2)));
				if (new_offset < 0) { new_offset = 0;}
				fseek(file, new_offset * sizeof(struct index_string), SEEK_SET);
				offset = new_offset;
				system("clear");
				need_print = 1;
				height_index = 0;

			}
			if (ch == 'q') {
				break;
			}
		}
		if (need_print) {
			if(!fread(&to_print, sizeof(struct index_string), 1, file))
			{
				printf("\nEnd of file\n");
				need_print = 0;
				continue;
			}
			printf(" %-10lf ", to_print.time_mark);
			offset++;

			if (width_index >= WIDTH) {
					width_index = 0;
					height_index++;
					printf("\n");
			}
			width_index++;
			if (height_index >=  HEIGHT) 
			{
				need_print = 0;
				printf("Press 'q' to quit. 's' - to scroll down. 'w' - to scroll up\n");
			}
		}
	}
	printf("\n");
	close(fd);
	fclose(file);
	return 0;
}
