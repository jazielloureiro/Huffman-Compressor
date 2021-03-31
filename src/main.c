#include <stdio.h>

#include "file.h"
#include "list.h"
#include "tree.h"

int main(){
	char *buffer = read_whole_file("data/input1.txt");
	list_node *list = create_char_list(buffer);
	tree_node *root = create_huffman_tree(list);

	return 0;
}
