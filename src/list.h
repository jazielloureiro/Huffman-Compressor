#ifndef LIST_H
#define LIST_H

typedef struct Tree_Node tree_node;

typedef struct List_Node{
	tree_node *tree;
	struct List_Node *next;
} list_node;

void init_freq_array(uint32_t *freq);

void calc_bytes_frequency_in_the_file(uint32_t *freq, FILE *file);

void add_new_node_to_list(list_node **list, tree_node *leaf);

void transfer_bytes_to_list(uint32_t *freq, list_node **list);

list_node *create_char_list(FILE *file);

uint8_t get_list_length(list_node *aux);

#endif
