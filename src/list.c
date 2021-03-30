#include <stdio.h>
#include <stdlib.h>

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

void add_new_node_to_list(char_table *table, tree_node *tree){
	list_node *new = malloc(sizeof(list_node));

	new->tree = tree;

	if(table->list == NULL){
		new->next = NULL;
		table->list = new;
	}else if(tree->frequency <= table->list->tree->frequency){
		new->next = table->list;
		table->list = new;
	}else{
		list_node *aux;

		for(aux = table->list; aux->next != NULL; aux = aux->next)
			if(tree->frequency <= aux->next->tree->frequency)
				break;

		new->next = aux->next;
		aux->next = new;
	}
}
