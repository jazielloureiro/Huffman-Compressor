#ifndef TABLE_H
#define TABLE_H

#define MAX_ASCII 128

typedef struct Node{
	char character;
	unsigned frequency;
	struct Node *left, *right;
} node;

typedef struct{
	node *chars;
	unsigned length;
} char_table;

void init_freq_array(unsigned *freq);
void calc_chars_frequency_in_the_buffer(unsigned *freq, char *buffer);
unsigned calc_table_length(unsigned *freq);
void transfer_chars_to_table(unsigned *freq, char_table *table);
void swap_nodes(node *n1, node *n2);
void sort_table(char_table *table);
char_table create_table(char *buffer);

#endif
