#include <stdio.h>
#include <stdlib.h>

#include "file.h"

FILE *init_file(char *filename){
	FILE *file = fopen(filename, "r");

	if(file == NULL){
		printf("It wasn't possible to read %s", filename);
		exit(EXIT_FAILURE);
	}

	return file;
}

long get_file_length(FILE *file){
	long length;

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);

	return length;
}

char *read_whole_file(char *filename){
	FILE *file = init_file(filename);
	long length = get_file_length(file);
	char *buffer = malloc(length);

	fread(buffer, 1, length, file);
	fclose(file);

	return buffer;
}
