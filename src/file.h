#ifndef FILE_H
#define FILE_H

FILE *init_file(char *filename);
long get_file_length(FILE *file);
char *read_whole_file(char *filename);

#endif
