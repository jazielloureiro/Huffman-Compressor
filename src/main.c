#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "list.h"
#include "tree.h"

void help(){
	puts("Syntax:\n\t./hc [OPTION] [INPUT FILE] [DESTINY FILE]"
	     "\n\nOptions:\n\t"
	     "-c, --compress:\n\t\tcompress the input file.\n\t"
	     "-d, --decompress:\n\t\tdecompress the input file.\n\t"
	     "-h, --help:\n\t\tshow this help and exit.");
}

int main(int argc, char **argv){
	if(argc > 4)
		puts("You've entered too many arguments.");
	else if(argc == 1 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
		help();
	else if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compress") == 0){
		FILE *input = init_file(argv[2], "r+"),
		     *output = init_file(argv[3], "w+");
		list_node *list = create_char_list(input);
		uint16_t list_length = get_list_length(list);
		tree_node *root;

		fwrite(&list_length, sizeof(uint16_t), 1, output);
		write_list_to_header(list, output);

		root = create_huffman_tree(list);

		compress_file(root, input, output);

		fclose(input);
		fclose(output);
		free_tree(root);
	}else if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decompress") == 0){
		FILE *input = init_file(argv[2], "r+"),
		     *output = init_file(argv[3], "w+");
		list_node *list = read_list_from_header(input);
		tree_node *root = create_huffman_tree(list);

		decompress_file(root, input, output);

		fclose(input);
		fclose(output);
		free_tree(root);
	}else
		puts("You've entered an invalid option.");

	return 0;
}
