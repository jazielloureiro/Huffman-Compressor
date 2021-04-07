#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void help(){
	puts("Syntax:\n\t./hc [OPTION] [SOURCE FILE] [DESTINY FILE]"
	     "\n\nOptions:\n\t"
	     "-c, --compress:\n\t\tcompress the source file.\n\t"
	     "-d, --decompress:\n\t\tdecompress the source file.\n\t"
	     "-h, --help:\n\t\tdisplay this help and exit.");
}

int main(int argc, char **argv){
	if(argc == 1)
		help();
	else if(argc > 4)
		puts("You've entered too many arguments.");
	else if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compress") == 0){
		FILE *outfile = init_file(argv[3], "w+");
		char *buffer = read_whole_file(argv[2], "r");
		list_node *list = create_char_list(buffer);
		tree_node *root;

		write_list_in_header(list, outfile);
		fputc('\0', outfile);

		root = create_huffman_tree(list);

		encoding_file(buffer, root, outfile);

		free(buffer);
		free(list);
		fclose(outfile);
	}else if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decompress") == 0){
		FILE *infile = init_file(argv[2], "r+");
		list_node *list = read(infile);
		tree_node *root = create_huffman_tree(list);

		decoding_file(infile, root);

		free(list);
		fclose(infile);
	}else
		puts("You've entered an invalid option.");

	return 0;
}
