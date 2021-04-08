#ifndef TREE_H
#define TREE_H

tree_node *create_leaf(char character, unsigned frequency);
tree_node *create_internal_tree_node(tree_node *left, tree_node *right);
tree_node *create_huffman_tree(list_node *list);
void free_tree(tree_node *aux);

#endif
