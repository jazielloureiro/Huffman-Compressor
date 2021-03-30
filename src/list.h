#ifndef LIST_H
#define LIST_H

typedef struct Tree_Node{
	char *chars;
	unsigned frequency;
	struct Node *left, *right;
} tree_node;

typedef struct List_Node{
	tree_node *tree;
	struct List_Node *next;
} list_node;

typedef struct{
	list_node *list;
} char_table;

tree_node *create_leaf(char character, unsigned frequency);
void add_new_node_to_list(char_table *table, tree_node *leaf);

#endif
