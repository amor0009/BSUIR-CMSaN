#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h> 
#include <sys/types.h>
#include <stdint.h>

struct index_string {
	double time_mark; 
	uint64_t recno;
};

struct thread_data
{
	int thread_id;
	int* block_size;
	struct index_string** buf_string;
};

struct sort_map
{
	char *flags;
	pthread_mutex_t mutex;
	int block_count;
	int threads_count;

};

static pthread_barrier_t sort_barrier;
static pthread_barrier_t next_cycle_barrier; 

static int sorting_blocks = 1;

static char continue_work = 1;

static struct sort_map map;

void merge_blocks(struct index_string *first_string, struct index_string *second_string, int block_size)
{
	struct index_string *buf_string = (struct index_string *)malloc(block_size * 2  *sizeof(struct index_string));
	int j = 0;

	int first_index = 0;
	int second_index = 0;

	for (; first_index < block_size && second_index < block_size; ) {
		if (first_string[first_index].time_mark < second_string[second_index].time_mark) {
			buf_string[j] = first_string[first_index];
			first_index++;
		}
		else {
			buf_string[j] = second_string[second_index];
			second_index++;
		}
		j++;
	}

	for ( ; first_index < block_size; first_index++) {
		buf_string[j] = first_string[first_index];
		j++;
	}

	for ( ; second_index < block_size; second_index++) {
		buf_string[j] = second_string[second_index];
		j++;
	}

	for (int i = 0; i < block_size * 2; i++) {
		first_string[i] = buf_string[i];
	}

	free(buf_string);
}

int get_records_count_in_block(int block_size)
{
	return block_size / sizeof(struct index_string);
}

int compare_time_marks (const struct index_string *first_string, const struct index_string *second_string)
{
    if (first_string->time_mark < second_string->time_mark)   return -1;
    else if (first_string->time_mark > second_string->time_mark)  return 1;
    else  return 0;
}

void* sorter_thread(void *data)
{
		struct thread_data local_data = *((struct thread_data*)data);
		free(data);
		while (continue_work) {
			int start_position = 0;
			int block_number = local_data.thread_id;
			map.flags[block_number] = 1;
			pthread_barrier_wait(&sort_barrier);
			char find_work = 1;
			while (find_work) {
				start_position = (block_number* (*(local_data.block_size) / sizeof(struct index_string)));
				qsort(*(local_data.buf_string) + start_position, *(local_data.block_size) / sizeof(struct index_string), sizeof(struct index_string), (int (*)(const void *, const void *))compare_time_marks);
				pthread_mutex_lock(&map.mutex);

				find_work = 0;
				for (int i =0; i < map.block_count; i++) {
					if (map.flags[i] == 0) {
						block_number = i;
						find_work = 1;
						map.flags[block_number] = 1;
						break;
					}
				}
				pthread_mutex_unlock(&map.mutex);
			}
			pthread_barrier_wait(&sort_barrier);
			pthread_barrier_wait(&sort_barrier);

			while (sorting_blocks != map.block_count) {
				block_number = local_data.thread_id;

				map.flags[block_number] = 1;

				char find_work = 1;

				while (find_work) {
					start_position = (sorting_blocks * block_number * get_records_count_in_block(*(local_data.block_size)));
					int second_string_start_position = start_position + (get_records_count_in_block(*(local_data.block_size)) *(sorting_blocks/2));
					int buf_length_in_records = map.block_count * get_records_count_in_block(*(local_data.block_size));

					if (start_position < buf_length_in_records && second_string_start_position < buf_length_in_records) {
						merge_blocks(*(local_data.buf_string)  + start_position, *(local_data.buf_string) +second_string_start_position, get_records_count_in_block(*(local_data.block_size)) *(sorting_blocks/2));
					}
					pthread_mutex_lock(&map.mutex);
					find_work = 0;
			
					for (int i = map.threads_count; i < map.block_count/sorting_blocks; i++) {
						if (map.flags[i] == 0) {
							block_number = i;
							map.flags[i] = 1;
							find_work = 1;
							break;
						}
					}
					pthread_mutex_unlock(&map.mutex);
				}
				pthread_barrier_wait(&next_cycle_barrier);
				pthread_barrier_wait(&next_cycle_barrier);
			}
			pthread_barrier_wait(&next_cycle_barrier);
		}
	pthread_exit(0);
}

void copy_file(char* destination_name, char* source_name, long unsigned int filesize )
{
	struct index_string *destination;
	struct index_string *source;

	FILE* new_file = fopen(destination_name, "wb");

	int destination_descriptor = open(destination_name,  O_RDWR);
	int source_descriptor = open(source_name, O_RDWR);
	ftruncate(destination_descriptor, filesize);

	destination = (struct index_string *)mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, destination_descriptor, 0);
	source = (struct index_string *)mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, source_descriptor, 0);


	for (long unsigned int i = 0; i < filesize/sizeof(struct index_string); i++ ) {
		destination[i] = source[i];
	}
	fclose(new_file);

	munmap(destination, filesize);
	munmap(source, filesize);

	close(destination_descriptor);
	close(source_descriptor);
}

int main(int argc, char** argv)
{
	char* lasts_after_strtol =  NULL;
	if (argc < 5) {
		fputs("Not enough command line arguments\nUsing of program: ./sorter [memsize] [granul] [threads] [filename]\n", stderr);
		return -1;
	}

	int file_descriptor = open(argv[4], O_RDWR);
	if (file_descriptor == -1) {
		perror("Error opening file ");
		return -1;
	}

	int old_buffer_size;
	int buffer_size = strtol(argv[1], &lasts_after_strtol, 10);

	if ( strlen(lasts_after_strtol) > 0 || buffer_size == 0) {
		fputs("Give correct memsize\n ", stderr);
		return -1;
	}
	buffer_size = ((buffer_size + getpagesize()-1)/getpagesize())*getpagesize();
	printf("Buffer size set to %d \n", buffer_size);

	map.block_count = strtol(argv[2], &lasts_after_strtol, 10);
	if ( strlen(lasts_after_strtol) || map.block_count == 0) {
		fputs("Give correct granul count\n", stderr);
		return -1;
	}
	map.block_count = ((map.block_count + 1)/2)*2;
	printf("Granul count set to %d \n", map.block_count);

	map.threads_count = strtol(argv[3], &lasts_after_strtol, 10);
	if ( strlen(lasts_after_strtol) || map.block_count == 0) {
		fputs("Give correct granul count\n ", stderr);
		return -1;
	}

	if (map.threads_count > map.block_count) {
		fputs("Error. Granul count must be greater than threads count\n", stderr);
		return -1;
	}

	struct stat file_status;
	fstat(file_descriptor, &file_status);
	struct index_string *buf_string;

	copy_file("source\0", argv[4], file_status.st_size);

	pthread_mutex_init(&map.mutex, NULL);
	pthread_barrier_init(&sort_barrier, NULL, map.threads_count + 1);
	pthread_barrier_init(&next_cycle_barrier, NULL, map.threads_count + 1);

	pthread_t *threads = (pthread_t*)malloc(map.threads_count * sizeof(pthread_t)); 
	map.flags = (char*)malloc(map.block_count * sizeof(char));

	int offset = 0;
	int block_size = buffer_size/map.block_count;

	for (int i = 0; i < map.threads_count; i++) {
		struct thread_data* data = (struct thread_data*)malloc(1 * sizeof(struct thread_data));
		data->block_size = &block_size;
		data->thread_id = i;
		data->buf_string = &buf_string;
		pthread_create(&threads[i], NULL, sorter_thread, (void*)data);
	}

	int buf_count = 0;

	while (continue_work) {
		if (offset + buffer_size > file_status.st_size) {
			old_buffer_size = buffer_size;
			buffer_size = file_status.st_size - offset;
			block_size = buffer_size / map.block_count;
			continue_work = 0;
		}
		buf_string = (struct index_string *)mmap(NULL, buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, offset);
		buf_count++;

		pthread_barrier_wait(&sort_barrier);
		pthread_barrier_wait(&sort_barrier); 

		for (int i =0; i < map.block_count; i++) {
				map.flags[i] = 0;
		}

		sorting_blocks = 2;
		pthread_barrier_wait(&sort_barrier); 

		while (sorting_blocks != map.block_count) {
			pthread_barrier_wait(&next_cycle_barrier); 
			for (int i =0; i < map.block_count; i++) {
				map.flags[i] = 0;
			}
			sorting_blocks *=2;
			pthread_barrier_wait(&next_cycle_barrier);	    
		}

		pthread_barrier_wait(&next_cycle_barrier);
		merge_blocks(buf_string, buf_string + (get_records_count_in_block(buffer_size/map.block_count) *(map.block_count/2) ), get_records_count_in_block(buffer_size/map.block_count) *(map.block_count/2));
		offset += buffer_size;
		munmap(buf_string, buffer_size);
	}

	for (int i = 0; i < map.threads_count; i++) {
		pthread_cancel(threads[i]);
	}

	buffer_size = old_buffer_size;

	unsigned int *buffer_indexes = (unsigned int*)calloc(buf_count, sizeof(unsigned int));
	buf_string = (struct index_string *)mmap(NULL, file_status.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);
	FILE* result_file = fopen("result.info", "wb");

	unsigned int rec_in_buf = buffer_size/sizeof(struct index_string);
	unsigned int rec_in_last_buf = (file_status.st_size -  buffer_size*(buf_count-1)) / sizeof(struct index_string);

	unsigned int ind = 0;
	while (ind < (unsigned int)(rec_in_buf*(buf_count-1) + rec_in_last_buf) )
	{
		int min_buf_ind = 0; 
		for (int i = 0; i < buf_count; i++) {
			if (buffer_indexes[i] < rec_in_buf) { 
				min_buf_ind = i;
				break;
			}
		}
		for (int i = 0; i < buf_count; i++) {
			if (i == buf_count-1) {
				if(buffer_indexes[i] >= rec_in_last_buf) break; 
			}
			if (buffer_indexes[i] < rec_in_buf && buf_string[(rec_in_buf * i) + buffer_indexes[i]].time_mark < buf_string[rec_in_buf * min_buf_ind + buffer_indexes[min_buf_ind]].time_mark) {
				min_buf_ind = i;
			}
		}
		fwrite(&buf_string[rec_in_buf * min_buf_ind + buffer_indexes[min_buf_ind]], sizeof(struct index_string), 1, result_file);
		buffer_indexes[min_buf_ind]++;
		ind++;
	}
	fclose(result_file);
	munmap(buf_string, file_status.st_size);

	remove(argv[4]);
	rename("source", argv[4]);

	pthread_mutex_destroy(&map.mutex);
	pthread_barrier_destroy(&sort_barrier);
	pthread_barrier_destroy(&next_cycle_barrier);

	close(file_descriptor);
	free(threads);
	free(map.flags);

	return 0;
}
