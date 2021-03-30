#include <stdio.h>

#include "file.h"
#include "list.h"
#include "table.h"

void print(tree_node *node){
	if(node != NULL){
		printf("%s : %d;\n", node->chars, node->frequency);
		print(node->left);
		print(node->right);
	}
}

int main(){
	char *buffer = read_whole_file("data/input1.txt");
	char_table table = create_table(buffer);
	tree_node *root = create_huffman_tree(table.list);

	print(root);

	return 0;
}
