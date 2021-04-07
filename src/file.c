#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "file.h"

FILE *init_file(char *filename, char *mode){
	FILE *file = fopen(filename, mode);

	if(file == NULL){
		printf("It wasn't possible to open the file %s", filename);
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

char *read_whole_file(char *filename, char *mode){
	FILE *file = init_file(filename, "r+");
	long length = get_file_length(file);
	char *buffer = malloc(length);

	fread(buffer, 1, length, file);
	fclose(file);

	return buffer;
}

int is_char_in_string(char *str, char ch){
	while(*str != '\0'){
		if(*str == ch)
			return 1;

		str++;
	}

	return 0;
}

void writing_in_the_file(Bitfile *bitfile){
	fwrite(&bitfile->buffer, 1, 1, bitfile->file);
	bitfile->index = 0;
}

void find_char_in_tree(char ch, tree_node *aux, Bitfile *bitfile){
	if(aux->chars[0] == ch && aux->chars[1] == '\0')
		return;

	bitfile->buffer <<= 1;
	bitfile->index++;

	if(is_char_in_string(aux->right->chars, ch)){
		bitfile->buffer++;

		if(bitfile->index == 8)
			writing_in_the_file(bitfile);

		find_char_in_tree(ch, aux->right, bitfile);
	}else{
		if(bitfile->index == 8)
			writing_in_the_file(bitfile);

		find_char_in_tree(ch, aux->left, bitfile);
	}
}

void encoding_file(char *buffer, tree_node *root, FILE *out){
	Bitfile bitfile;

	bitfile.file = out;
	bitfile.buffer = 0;
	bitfile.index = 0;

	while(*buffer != '\0'){
		find_char_in_tree(*buffer, root, &bitfile);

		buffer++;
	}

	bitfile.buffer <<= bitfile.index;
	writing_in_the_file(&bitfile);
}

void decoding(FILE **in, tree_node *aux, Bitfile *bitfile){
	if(aux->left == NULL && aux->right == NULL){
		fputc(aux->chars[0], bitfile->file);
		return;
	}

	if(bitfile->index == 8){
		bitfile->index = 0;
		bitfile->buffer = fgetc(*in);
	}

	bitfile->index++;

	if(bitfile->buffer >> 7){
		bitfile->buffer <<= 1;

		decoding(in, aux->right, bitfile);
	}else{
		bitfile->buffer <<= 1;

		decoding(in, aux->left, bitfile);
	}
}

void decoding_file(FILE *in, tree_node *root){
	unsigned i = 0;
	Bitfile bitfile;

	bitfile.file = init_file("data/output1.txt", "w");
	bitfile.buffer = fgetc(in);
	bitfile.index = 0;

	while(i++ < root->frequency)
		decoding(&in, root, &bitfile);
}
