#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "list.h"
#include "tree.h"

FILE *init_file(char *filename, char *mode){
	FILE *file = fopen(filename, mode);

	if(file == NULL){
		printf("It wasn't possible to open the file %s\n", filename);
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

unsigned char *read_whole_file(char *filename){
	FILE *file = init_file(filename, "r+");
	long length = get_file_length(file);
	unsigned char *buffer = malloc(length);

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

void write_bits_to_file(Bitfile *bitfile){
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
			write_bits_to_file(bitfile);

		find_char_in_tree(ch, aux->right, bitfile);
	}else{
		if(bitfile->index == 8)
			write_bits_to_file(bitfile);

		find_char_in_tree(ch, aux->left, bitfile);
	}
}

void compress_file(unsigned char *buffer, tree_node *root, FILE *file){
	Bitfile bitfile;

	bitfile.file = file;
	bitfile.buffer = 0;
	bitfile.index = 0;

	while(*buffer != '\0'){
		find_char_in_tree(*buffer, root, &bitfile);

		buffer++;
	}

	if(bitfile.index != 0){
		bitfile.buffer <<= 8 - bitfile.index;
		write_bits_to_file(&bitfile);
	}
}

void find_char_by_bits(FILE **file, tree_node *aux, Bitfile *bitfile){
	if(aux->left == NULL && aux->right == NULL){
		fputc(aux->chars[0], bitfile->file);
		return;
	}

	if(bitfile->index == 8){
		bitfile->index = 0;
		bitfile->buffer = fgetc(*file);
	}

	bitfile->index++;

	if(bitfile->buffer >> 7){
		bitfile->buffer <<= 1;

		find_char_by_bits(file, aux->right, bitfile);
	}else{
		bitfile->buffer <<= 1;

		find_char_by_bits(file, aux->left, bitfile);
	}
}

void decompress_file(FILE *file, tree_node *root, char *filename){
	Bitfile bitfile;
	unsigned i = 0;

	bitfile.file = init_file(filename, "w");
	bitfile.buffer = fgetc(file);
	bitfile.index = 0;

	while(i++ < root->frequency)
		find_char_by_bits(&file, root, &bitfile);
}

void write_list_to_header(list_node *aux, FILE *file){
	if(aux != NULL){
		write_list_to_header(aux->next, file);
		fputc(aux->tree->chars[0], file);
		fwrite(&aux->tree->frequency, sizeof(unsigned), 1, file);
	}
}

list_node *read_list_from_header(FILE *file){
	list_node *list = NULL;
	char ch;

	while((ch = fgetc(file)) != '\0'){
		unsigned freq;

		fread(&freq, sizeof(unsigned), 1, file);
		add_new_node_to_list(&list, create_leaf(ch, freq));
	}

	return list;
}
