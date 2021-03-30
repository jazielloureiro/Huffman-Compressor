#ifndef LIST_H
#define LIST_H

typedef struct Tree_Node{
	char *chars;
	unsigned frequency;
	struct Tree_Node *left, *right;
} tree_node;

typedef struct List_Node{
	tree_node *tree;
	struct List_Node *next;
} list_node;

typedef struct{
	list_node *list;
} char_table;

tree_node *create_leaf(char character, unsigned frequency);
void add_new_node_to_list(list_node **list, tree_node *leaf);
tree_node *create_internal_tree_node(tree_node *left, tree_node *right);
tree_node *create_huffman_tree(list_node *list);

#endif
