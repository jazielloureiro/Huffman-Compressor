#include <stdio.h>
#include <stdlib.h>

#include "table.h"

void init_freq_array(unsigned *freq){
	for(unsigned i = 0; i < MAX_ASCII; i++)
		freq[i] = 0;
}

void calc_chars_frequency_in_the_buffer(unsigned *freq, char *buffer){
	while(*buffer != '\0')
		freq[*(buffer++)]++;
}

unsigned calc_table_length(unsigned *freq){
	unsigned length = 0, i;

	for(i = 0; i < MAX_ASCII; i++)
		if(freq[i] > 0)
			length++;

	return length;
}

void transfer_chars_to_table(unsigned *freq, char_table *table){
	unsigned i, j;

	for(i = 0, j = 0; i < MAX_ASCII; i++){
		if(freq[i] > 0){
			table->chars[j].character = i;
			table->chars[j].frequency = freq[i];
			table->chars[j].left = NULL;
			table->chars[j].right = NULL;
			j++;
		}
	}
}

void swap_nodes(node *n1, node *n2){
	node aux = *n1;
	*n1 = *n2;
	*n2 = aux;
}

void sort_table(char_table *table){
	for(unsigned i = 0; i < table->length; i++){
		node *min = &table->chars[i];

		for(unsigned j = i + 1; j < table->length; j++)
			if(table->chars[j].frequency < min->frequency)
				min = &table->chars[j];

		swap_nodes(&table->chars[i], min);
	}
}

char_table create_table(char *buffer){
	unsigned freq[MAX_ASCII], length;
	char_table table;

	init_freq_array(freq);

	calc_chars_frequency_in_the_buffer(freq, buffer);

	table.length = calc_table_length(freq);
	table.chars = malloc(sizeof(node) * table.length);

	transfer_chars_to_table(freq, &table);

	sort_table(&table);

	return table;
}
