#ifndef OPERARARING_WITH_CHARACTER_CODES_H
#define OPERARARING_WITH_CHARACTER_CODES_H
#include "types.h"


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

#endif