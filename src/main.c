#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "list.h"
#include "tree.h"

void help(){
	puts("Syntax:\n\t./hc [OPTION] [SOURCE FILE] [DESTINY FILE]"
	     "\n\nOptions:\n\t"
	     "-c, --compress:\n\t\tcompress the source file.\n\t"
	     "-d, --decompress:\n\t\tdecompress the source file.\n\t"
	     "-h, --help:\n\t\tdisplay this help and exit.");
}

int main(int argc, char **argv){
	if(argc > 4)
		puts("You've entered too many arguments.");
	else if(argc == 1 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
		help();
	else if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compress") == 0){
		char *buffer = read_whole_file(argv[2]);
		FILE *file = init_file(argv[3], "w+");
		list_node *list = create_char_list(buffer);
		tree_node *root;

		write_list_to_header(list, file);
		fputc('\0', file);

		root = create_huffman_tree(list);

		compress_file(buffer, root, file);

		free(buffer);
		free(list);
		free_tree(root);
		fclose(file);
	}else if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decompress") == 0){
		FILE *compressed = init_file(argv[2], "r+"),
		     *decompressed = init_file(argv[3], "w");
		list_node *list = read_list_from_header(compressed);
		tree_node *root = create_huffman_tree(list);

		decompress_file(compressed, root, argv[3]);

		free(list);
		free_tree(root);
		fclose(compressed);
		fclose(decompressed);
	}else
		puts("You've entered an invalid option.");

	return 0;
}
