#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "tree.h"

tree_node *create_leaf(char character, unsigned frequency){
	tree_node *leaf = malloc(sizeof(tree_node));

	leaf->chars = malloc(LEAF_CHARS_LENGTH);
	sprintf(leaf->chars, "%c", character);
	leaf->frequency = frequency;
	leaf->left = NULL;
	leaf->right = NULL;

	return leaf;
}

tree_node *create_internal_tree_node(tree_node *left, tree_node *right){
	tree_node *internal = malloc(sizeof(tree_node));

	internal->chars = malloc(strlen(left->chars) + strlen(right->chars) + 1);
	sprintf(internal->chars, "%s%s", right->chars, left->chars);

	internal->frequency = left->frequency + right->frequency;

	internal->left = left;
	internal->right = right;

	return internal;
}

tree_node *create_huffman_tree(list_node *list){
	while(list->next != NULL){
		tree_node *new = create_internal_tree_node(list->tree, list->next->tree);
		list_node *trash = list;

		list = list->next->next;
		free(trash->next);
		free(trash);
		
		add_new_node_to_list(&list, new);
	}

	return list->tree;
}
