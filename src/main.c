#include <stdio.h>

#include "file.h"
#include "list.h"
#include "table.h"

int main(){
	char *buffer = read_whole_file("data/input1.txt");
	char_table table = create_table(buffer);

	for(list_node *i = table.list; i != NULL; i = i->next)
		printf("%s : %d\n", i->tree->chars, i->tree->frequency);
	
	return 0;
}
