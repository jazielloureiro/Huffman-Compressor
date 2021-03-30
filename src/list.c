#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "table.h"

tree_node *create_leaf(char character, unsigned frequency){
	tree_node *leaf = malloc(sizeof(tree_node));

	leaf->chars = malloc(2);
	sprintf(leaf->chars, "%c", character);
	leaf->frequency = frequency;
	leaf->left = NULL;
	leaf->right = NULL;

	return leaf;
}

void add_new_node_to_list(list_node **list, tree_node *tree){
	list_node *new = malloc(sizeof(list_node));

	new->tree = tree;

	if(*list == NULL){
		new->next = NULL;
		*list = new;
	}else if(tree->frequency <= (*list)->tree->frequency){
		new->next = *list;
		*list = new;
	}else{
		list_node *aux;

		for(aux = *list; aux->next != NULL; aux = aux->next)
			if(tree->frequency <= aux->next->tree->frequency)
				break;

		new->next = aux->next;
		aux->next = new;
	}
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
