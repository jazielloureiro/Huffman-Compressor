#ifndef LIST_H
#define LIST_H

void init_freq_array(uint32_t *freq);
void calc_chars_frequency_in_the_buffer(uint32_t *freq, unsigned char *buffer);
void add_new_node_to_list(list_node **list, tree_node *leaf);
void transfer_chars_to_list(uint32_t *freq, list_node **list);
list_node *create_char_list(unsigned char *buffer);

#endif
