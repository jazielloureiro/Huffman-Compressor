#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "list.h"
#include "tree.h"

enum operations{
	COMPRESS,
	DECOMPRESS
};

void coding(char **argv, uint8_t operation){
	FILE *input = init_file(argv[2], "r+"),
	     *output = init_file(argv[3], "w+");
	tree_node *root;

	if(operation == COMPRESS){
		list_node *list = create_char_list(input);
		uint8_t list_length = get_list_length(list);

		fwrite(&list_length, sizeof(uint8_t), 1, output);
		write_list_to_header(list, output);

		root = create_huffman_tree(list);

		compress_file(root, input, output);
	}else{
		list_node *list = read_list_from_header(input);

		root = create_huffman_tree(list);

		decompress_file(root, input, output);
	}

	fclose(input);
	fclose(output);
	free_tree(root);
}

void help(){
	puts("Usage:\n"
	     "  hc <options> <input file> <output file>\n"
	     "  hc [-h | --help]\n\n"
	     "Options:\n"
	     "  -c, --compress    Compress the input file\n"
	     "  -d, --decompress  Decompress the input file\n"
	     "  -h, --help        Print usage message");
}

int main(int argc, char **argv){
	if(argc == 1)
		help();
	else if(argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
		help();
	else if(argc != 4)
		puts("Error: invalid number of arguments.\nTry 'hc --help'");
	else if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compress") == 0)
		coding(argv, COMPRESS);
	else if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decompress") == 0)
		coding(argv, DECOMPRESS);
	else
		puts("Error: unrecognized option.\nTry 'hc --help'");

	return 0;
}
