#ifndef TABLE_H
#define TABLE_H

#define MAX_ASCII 128

void init_freq_array(unsigned *freq);
void calc_chars_frequency_in_the_buffer(unsigned *freq, char *buffer);
void transfer_chars_to_table(unsigned *freq, char_table *table);
char_table create_table(char *buffer);

#endif
