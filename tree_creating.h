#ifndef TREE_CREATING_H
#define TREE_CREATING_H
#include "types.h"
/*
== Tree Creating Module ==
This module provides functions for creating and managing a Huffman tree
from character frequency data. It includes functions to create tree nodes,
build the tree, and free the allocated memory.
*/

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

void fill_codes(CharStat* root, huffman_codes* arr, char*newcode,int *index ,int depth);
// Fills the huffman_codes array with codes generated from the Huffman tree
// Parameters:
// - root: pointer to the root of the Huffman tree
// - arr: pointer to the array of huffman_codes to be filled
// - newcode: temporary string to build the current code
// - index: pointer to the current index in the huffman_codes array
// - depth: current depth in the Huffman tree (used for code generation)

huffman_codes *fill_the_array(CharStat* root, int size);
// Creates and returns an array of huffman_codes from the Huffman tree
// Parameters:
// - root: pointer to the root of the Huffman tree
// - size: number of unique characters (size of the huffman_codes array to be created
// Returns:
// - pointer to the newly created array of huffman_codes

binary_huffman_code* convert_to_binary_huffman_codes(huffman_codes* codes, int size);
// Converts an array of huffman_codes to an array of binary_huffman_code
// Parameters:
// - codes: pointer to the array of huffman_codes
// - size: number of elements in the codes array
// Returns:
// - pointer to the newly created array of binary_huffman_code
// this works with the absolute black magic of bitwise operations

int cmp_binary_huffman_code_by_char(const void *pa, const void *pb);
// Comparison function for qsort to sort binary_huffman_code by character
// Parameters:
// - pa: pointer to the first binary_huffman_code
// - pb: pointer to the second binary_huffman_code
// Returns:
// - negative value if first < second
// - positive value if first > second
// - zero if equal
// this is a help for bsearch function to find binary_huffman_code by character
// this is a help for qsort function to sort binary_huffman_code by character

int cmp_charstat_ptr_by_count(const void *pa, const void *pb);
// Comparison function for qsort to sort CharStat pointers by count (and character for tie-breaking
// Parameters:
// - pa: pointer to the first CharStat pointer
// - pb: pointer to the second CharStat pointer
// Returns:
// - negative value if first < second
// - positive value if first > second
// - zero if equal
// this is a help for qsort function to sort CharStat pointers by count (and character for tie-breaking)

#endif