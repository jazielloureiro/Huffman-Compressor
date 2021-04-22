#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "tree.h"

#define MAX_BYTES 256

void init_freq_array(uint32_t *freq){
	for(uint16_t i = 0; i < MAX_BYTES; i++)
		freq[i] = 0;
}

void calc_bytes_frequency_in_the_file(uint32_t *freq, FILE *file){
	while(1){
		uint8_t buffer;

		fread(&buffer, sizeof(uint8_t), 1, file);

		if(feof(file))
			break;

		freq[buffer]++;
	}
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

void transfer_bytes_to_list(uint32_t *freq, list_node **list){
	for(uint16_t i = 0; i < MAX_BYTES; i++)
		if(freq[i] > 0)
			add_new_node_to_list(list, create_leaf(i, freq[i]));
}

list_node *create_char_list(FILE *file){
	uint32_t freq[MAX_BYTES];
	list_node *list = NULL;

	init_freq_array(freq);

	calc_bytes_frequency_in_the_file(freq, file);

	transfer_bytes_to_list(freq, &list);

	fseek(file, 0, SEEK_SET);

	return list;
}

uint8_t get_list_length(list_node *aux){
	return aux->next == NULL? 0 : 1 + get_list_length(aux->next);
}
