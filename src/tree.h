#ifndef TREE_H
#define TREE_H

typedef struct Tree_Node{
	uint8_t *bytes;
	uint16_t diff_bytes_qty;
	uint32_t frequency;
	struct Tree_Node *left, *right;
} tree_node;

tree_node *create_leaf(uint8_t byte, uint32_t frequency);

void merge_bytes_arrays(tree_node *internal);

tree_node *create_internal_tree_node(tree_node *left, tree_node *right);

tree_node *create_huffman_tree(list_node *list);

void free_tree(tree_node *aux);

#endif
