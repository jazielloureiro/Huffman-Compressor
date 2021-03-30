#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "table.h"

void init_freq_array(unsigned *freq){
	for(unsigned i = 0; i < MAX_ASCII; i++)
		freq[i] = 0;
}

void calc_chars_frequency_in_the_buffer(unsigned *freq, char *buffer){
	while(*buffer != '\0')
		freq[*(buffer++)]++;
}

void transfer_chars_to_table(unsigned *freq, char_table *table){
	table->list = NULL;

	for(unsigned i = 0; i < MAX_ASCII; i++){
		if(freq[i] > 0){
			tree_node *leaf = create_leaf(i, freq[i]);
			add_new_node_to_list(table, leaf);
		}
	}
}

char_table create_table(char *buffer){
	unsigned freq[MAX_ASCII];
	char_table table;

	init_freq_array(freq);

	calc_chars_frequency_in_the_buffer(freq, buffer);

	transfer_chars_to_table(freq, &table);

	return table;
}
