#ifndef FILE_H
#define FILE_H

typedef struct{
	FILE *file;
	unsigned char buffer;
	unsigned index;
} Bitfile;

FILE *init_file(char *filename, char *mode);
long get_file_length(FILE *file);
char *read_whole_file(char *filename, char *mode);
void encoding_file(char *buffer, tree_node *root, FILE *out);
void decoding_file(FILE *in, tree_node *root);

#endif
