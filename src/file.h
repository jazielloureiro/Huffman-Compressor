#ifndef FILE_H
#define FILE_H

#define MAX_ASCII 128
#define LEAF_CHARS_LENGTH 2

typedef struct Tree_Node{
	char *chars;
	uint32_t frequency;
	struct Tree_Node *left, *right;
} tree_node;

typedef struct List_Node{
	tree_node *tree;
	struct List_Node *next;
} list_node;

typedef struct{
	FILE *file;
	unsigned char buffer;
	unsigned index;
} Bitfile;

FILE *init_file(char *filename, char *mode);
long get_file_length(FILE *file);
unsigned char *read_whole_file(char *filename);
int is_char_in_string(char *str, char ch);
void write_bits_to_file(Bitfile *bitfile);
void find_char_in_tree(char ch, tree_node *aux, Bitfile *bitfile);
void compress_file(unsigned char *buffer, tree_node *root, FILE *file);
void find_char_by_bits(FILE **file, tree_node *aux, Bitfile *bitfile);
void decompress_file(FILE *file, tree_node *root, char *filename);
void write_list_to_header(list_node *aux, FILE *file);
list_node *read_list_from_header(FILE *file);

#endif
