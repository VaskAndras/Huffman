#ifndef FROM_ARRAY_TO_BINARY_TREE_H
#define FROM_ARRAY_TO_BINARY_TREE_H
#include "types.h"

CharStat* compress_chars_dynamic(const int *input, int size, int *out_count);
// Compresses the input frequency array into a dynamic array of CharStat structures
// Parameters:
// - input: array of character frequencies
// - size: size of the input array
// - out_count: pointer to store the number of non-zero frequency characters found
// Returns:
// - pointer to the dynamically allocated array of CharStat structures

CharStat* create_a_new_node(CharStat *left, CharStat *right);
// Creates a new internal node for the Huffman tree
// Parameters:
// - left: pointer to the left child node
// - right: pointer to the right child node
// Returns:
// - pointer to the newly created internal node


CharStat* create_a_tree(CharStat **array, int size);
// Creates a Huffman tree from an array of CharStat pointers
// Parameters:
// - array: array of pointers to CharStat structures
// - size: number of elements in the array
// Returns:
// - pointer to the root of the created Huffman tree

void free_huffman_tree(CharStat* root);
// Frees the memory allocated for the Huffman tree
// Parameters:
// - root: pointer to the root of the Huffman tree to be freed
// works recursively

CharStat** create_a_pointer_array(CharStat* arr, int size);
// Creates an array of pointers to CharStat structures from a given array
// Parameters:
// - arr: array of CharStat structures
// - size: number of elements in the array
// Returns:
// - pointer to the newly created array of CharStat pointers

#endif