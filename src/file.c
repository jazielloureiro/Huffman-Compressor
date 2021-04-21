#include <stdint.h>
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

uint8_t is_byte_in_bytes_array(uint8_t *bytes, uint8_t byte, uint16_t qty){
	for(uint16_t i = 0; i < qty; i++)
		if(bytes[i] == byte)
			return 1;

	return 0;
}

void write_buffer_to_file(Bitfile *bitfile){
	fwrite(&bitfile->buffer, 1, 1, bitfile->file);
	bitfile->index = 0;
}

void find_byte_in_tree(uint8_t byte, tree_node *aux, Bitfile *bitfile){
	if(aux->diff_bytes_qty == 1)
		return;

	bitfile->buffer <<= 1;
	bitfile->index++;

	if(is_byte_in_bytes_array(aux->right->bytes, byte, aux->right->diff_bytes_qty)){
		bitfile->buffer++;

		if(bitfile->index == 8)
			write_buffer_to_file(bitfile);

		find_byte_in_tree(byte, aux->right, bitfile);
	}else{
		if(bitfile->index == 8)
			write_buffer_to_file(bitfile);

		find_byte_in_tree(byte, aux->left, bitfile);
	}
}

void compress_file(tree_node *root, FILE *input, FILE *output){
	Bitfile bitfile;

	bitfile.file = output;
	bitfile.buffer = 0;
	bitfile.index = 0;

	while(1){
		uint8_t byte;

		fread(&byte, sizeof(uint8_t), 1, input);

		if(feof(input))
			break;

		find_byte_in_tree(byte, root, &bitfile);
	}

	if(bitfile.index != 0){
		bitfile.buffer <<= 8 - bitfile.index;
		write_buffer_to_file(&bitfile);
	}
}

void find_byte_by_bits(FILE **file, tree_node *aux, Bitfile *bitfile){
	if(aux->diff_bytes_qty == 1){
		fwrite(&aux->bytes[0], sizeof(uint8_t), 1, bitfile->file);
		return;
	}

	if(bitfile->index == 8){
		bitfile->index = 0;
		fread(&bitfile->buffer, sizeof(uint8_t), 1, *file);
	}

	bitfile->index++;

	if(bitfile->buffer >> 7){
		bitfile->buffer <<= 1;

		find_byte_by_bits(file, aux->right, bitfile);
	}else{
		bitfile->buffer <<= 1;

		find_byte_by_bits(file, aux->left, bitfile);
	}
}

void decompress_file(tree_node *root, FILE *input, FILE *output){
	Bitfile bitfile;

	bitfile.file = output;
	fread(&bitfile.buffer, sizeof(uint8_t), 1, input);
	bitfile.index = 0;

	for(uint64_t i = 0; i < root->frequency; i++)
		find_byte_by_bits(&input, root, &bitfile);
}

void write_list_to_header(list_node *aux, FILE *file){
	if(aux != NULL){
		write_list_to_header(aux->next, file);
		fwrite(&aux->tree->bytes[0], sizeof(uint8_t), 1, file);
		fwrite(&aux->tree->frequency, sizeof(uint32_t), 1, file);
	}
}

list_node *read_list_from_header(FILE *file){
	list_node *list = NULL;
	uint8_t list_length;

	fread(&list_length, sizeof(uint8_t), 1, file);

	for(uint16_t i = 0; i <= list_length; i++){
		uint8_t byte;
		uint32_t freq;

		fread(&byte, sizeof(uint8_t), 1, file);
		fread(&freq, sizeof(uint32_t), 1, file);
		add_new_node_to_list(&list, create_leaf(byte, freq));
	}

	return list;
}
