#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "file.h"
#include "tree.h"

void write_list_in_header(list_node *aux, FILE *outfile){
	if(aux != NULL){
		write_list_in_header(aux->next, outfile);
		fputc(aux->tree->chars[0], outfile);
		fwrite(&aux->tree->frequency, sizeof(unsigned), 1, outfile);
	}
}

list_node *read(FILE *file){
	list_node *list = NULL;
	char aux_ch;

	while((aux_ch = fgetc(file)) != '\0'){
		unsigned aux_freq;

		fread(&aux_freq, sizeof(unsigned), 1, file);
		add_new_node_to_list(&list, create_leaf(aux_ch, aux_freq));
	}

	return list;
}

void print(list_node *aux){
	if(aux != NULL){
		printf("%c : %d\n", aux->tree->chars[0], aux->tree->frequency);
		print(aux->next);
	}
}

int main(){
	FILE *outfile = init_file("data/compressed1.hcf", "w+");
	char *buffer = read_whole_file("data/input1.txt", "r");
	list_node *list = create_char_list(buffer);
	tree_node *root;

	write_list_in_header(list, outfile);
	fputc('\0', outfile);

	root = create_huffman_tree(list);

	encoding_file(buffer, root, outfile);

	free(buffer);
	free(list);
	fclose(outfile);

	outfile = init_file("data/compressed1.hcf", "r+");
	list = read(outfile);
	root = create_huffman_tree(list);

	decoding_file(outfile, root);

	free(list);
	fclose(outfile);

	return 0;
}
