#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdint.h>

struct index_string {
	double time_mark; 
	uint64_t recno;
};

int main(int argc, char** argv)
{
	srand(time(NULL));
	if (!argv[1] || !argv[2]) {
		fputs("Error in processing command line arguments\nUsing of program: ./generator [filename] [indexes-count]\n\0", stderr);
		return -1;
	}
	uint64_t indexses_count = atoi(argv[2]);
	if (indexses_count == 0) {
		fputs("Error input of indexes-count\n", stderr);
		return -1;
	}
	FILE *file;
	char filename[50];
	strcpy(filename, argv[1]);
	strcat(filename, ".info");
	file = fopen(filename, "wb");

	if (!file) {
		perror("Cant create file");
		return -1;
	}

	indexses_count = ((indexses_count + 255)/256)*256;

	printf("Index count rounded to %ld\n", indexses_count);

	for (uint64_t i = 0; i < indexses_count; i++) {
		struct index_string str;
		str.recno = i;
		double time_mark = rand() % (2399999 - 15020) + 15020;
		time_mark += (double)rand() / RAND_MAX;
		str.time_mark = time_mark;

		fwrite(&str, sizeof(struct index_string), 1, file);
	}
	fclose(file);	
	return 0;
}
