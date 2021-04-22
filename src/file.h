#ifndef FILE_H
#define FILE_H

typedef struct List_Node list_node;
typedef struct Tree_Node tree_node;

typedef struct{
	FILE *file;
	uint8_t buffer, index;
} Bitfile;

FILE *init_file(char *filename, char *mode);

uint8_t is_byte_in_bytes_array(uint8_t *bytes, uint8_t byte, uint16_t qty);

void write_buffer_to_file(Bitfile *bitfile);

void find_byte_in_tree(uint8_t byte, tree_node *aux, Bitfile *bitfile);

void compress_file(tree_node *root, FILE *input, FILE *output);

void find_byte_by_bits(FILE **file, tree_node *aux, Bitfile *bitfile);

void decompress_file(tree_node *root, FILE *input, FILE *output);

void write_list_to_header(list_node *aux, FILE *file);

list_node *read_list_from_header(FILE *file);

#endif
