#include <stdio.h>
#include <stdlib.h>

#define MAX_ASCII 128

typedef struct Node{
	char character;
	unsigned frequency;
	struct Node *left, *right;
} node;

typedef struct{
	node *chars;
	unsigned length;
} char_table;

FILE *init_file(char *filename){
	FILE *file = fopen(filename, "r");

	if(file == NULL){
		printf("It wasn't possible to read %s", filename);
		exit(EXIT_FAILURE);
	}

	return file;
}

long get_file_length(FILE *file){
	long length;

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);

	return length;
}

char *read_whole_file(char *filename){
	FILE *file = init_file(filename);
	long length = get_file_length(file);
	char *buffer = malloc(length);

	fread(buffer, 1, length, file);

	return buffer;
}

unsigned calc_table_length(unsigned *freq){
	unsigned length = 0, i;

	for(i = 0; i < MAX_ASCII; i++)
		if(freq[i] > 0)
			length++;

	return length;
}

void init_freq_array(unsigned *freq){
	for(unsigned i = 0; i < MAX_ASCII; i++)
		freq[i] = 0;
}

void calc_chars_frequency_in_the_buffer(unsigned *freq, char *buffer){
	while(*buffer != '\0')
		freq[*(buffer++)]++;
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

int main(){
	char *buffer = read_whole_file("data/input1.txt");
	char_table table = create_table(buffer);

	for(int i = 0; i < table.length; i++)
		printf("%c : %d\n", table.chars[i].character, table.chars[i].frequency);
	
	return 0;
}
