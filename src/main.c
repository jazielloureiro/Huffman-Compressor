#include <stdio.h>

#include "file.h"
#include "table.h"

int main(){
	char *buffer = read_whole_file("data/input1.txt");
	char_table table = create_table(buffer);

	for(int i = 0; i < table.length; i++)
		printf("%c : %d\n", table.chars[i].character, table.chars[i].frequency);
	
	return 0;
}
