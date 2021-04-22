#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "tree.h"

tree_node *create_leaf(uint8_t byte, uint32_t frequency){
	tree_node *leaf = malloc(sizeof(tree_node));

	leaf->bytes = malloc(sizeof(uint8_t));
	leaf->bytes[0] = byte;
	leaf->diff_bytes_qty = 1;
	leaf->frequency = frequency;
	leaf->left = NULL;
	leaf->right = NULL;

	return leaf;
}

void merge_bytes_arrays(tree_node *internal){
	uint16_t i;

	for(i = 0; i < internal->right->diff_bytes_qty; i++)
		internal->bytes[i] = internal->right->bytes[i];

	for(uint16_t j = 0; j < internal->left->diff_bytes_qty; i++, j++)
		internal->bytes[i] = internal->left->bytes[j];
}

tree_node *create_internal_tree_node(tree_node *left, tree_node *right){
	tree_node *internal = malloc(sizeof(tree_node));

	internal->left = left;
	internal->right = right;

	internal->frequency = left->frequency + right->frequency;

	internal->diff_bytes_qty = left->diff_bytes_qty + right->diff_bytes_qty;
	internal->bytes = malloc(internal->diff_bytes_qty);
	 
	merge_bytes_arrays(internal);

	return internal;
}

tree_node *create_huffman_tree(list_node *list){
	tree_node *huffman;

	while(list->next != NULL){
		tree_node *new = create_internal_tree_node(list->tree, list->next->tree);
		list_node *trash = list;

		list = list->next->next;
		free(trash->next);
		free(trash);
		
		add_new_node_to_list(&list, new);
	}

	huffman = list->tree;
	free(list);

	return huffman;
}

void free_tree(tree_node *aux){
	if(aux != NULL){
		free_tree(aux->left);
		free_tree(aux->right);
		free(aux->bytes);
		free(aux);
	}
}
