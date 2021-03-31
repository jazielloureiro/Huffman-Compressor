#ifndef LIST_H
#define LIST_H

#define MAX_ASCII 128
#define LEAF_CHARS_LENGTH 2

typedef struct Tree_Node{
	char *chars;
	unsigned frequency;
	struct Tree_Node *left, *right;
} tree_node;

typedef struct List_Node{
	tree_node *tree;
	struct List_Node *next;
} list_node;

void init_freq_array(unsigned *freq);
void calc_chars_frequency_in_the_buffer(unsigned *freq, char *buffer);
void add_new_node_to_list(list_node **list, tree_node *leaf);
void transfer_chars_to_list(unsigned *freq, list_node **list);
list_node *create_char_list(char *buffer);

#endif
