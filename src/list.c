#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "tree.h"

void init_freq_array(unsigned *freq){
	for(unsigned i = 0; i < MAX_ASCII; i++)
		freq[i] = 0;
}

void calc_chars_frequency_in_the_buffer(unsigned *freq, char *buffer){
	while(*buffer != '\0')
		freq[*(buffer++)]++;
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

void transfer_chars_to_list(unsigned *freq, list_node **list){
	for(unsigned i = 0; i < MAX_ASCII; i++){
		if(freq[i] > 0){
			tree_node *leaf = create_leaf(i, freq[i]);
			add_new_node_to_list(list, leaf);
		}
	}
}

list_node *create_char_list(char *buffer){
	unsigned freq[MAX_ASCII];
	list_node *list = NULL;

	init_freq_array(freq);

	calc_chars_frequency_in_the_buffer(freq, buffer);

	transfer_chars_to_list(freq, &list);

	return list;
}
