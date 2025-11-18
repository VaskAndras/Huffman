#ifndef ENCODING_H
#define ENCODING_H
#include "types.h"

/* 
== Encoding Module ==
This module provides functions for generating Huffman codes from a Huffman tree, 
converting these codes to a binary format, and obtaining filenames from user input.
*/

char* get_a_filename();
// Gets a filename from the user
// Returns:
// - the filename as a string

CharStat* create_frequency_array(char* filename, int *out_count);
// Creates a frequency array from the contents of a file
// Parameters:
// - filename: name of the file to read
// - out_count: pointer to store the number of unique characters found
// Returns:
// - pointer to the dynamically allocated frequency array

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

void from_array_to_character_codes(int *input, int size, int *out_count, huffman_codes **out_codes);
// Main function to convert an array of character frequencies to Huffman codes
// Parameters:
// - input: array of character frequencies
// - size: size of the input array
// - out_count: pointer to store the number of unique characters (size of the output codes array)
// - out_codes: pointer to store the pointer to the newly created array of huffman_codes

void create_a_file_if_not_exists(char* filename);
// Creates a file with the given filename if it does not already exist
// Parameters:
// - filename: name of the file to create

void create_a_header(char* filename, CharStat* filtered_array, int size);
// Creates a header in the specified file containing character statistics
// Parameters:
// - filename: name of the file to write the header to
// - filtered_array: array of CharStat structures containing character statistics
// - size: number of elements in the filtered_array

void write_encoded_data(char* filename, binary_huffman_code* binary_codes, int size);
// Writes the encoded data to the specified file
// Parameters:
// - filename: name of the file to write the encoded data to
// - binary_codes: array of binary_huffman_code structures containing the encoded data
// - size: number of elements in the binary_codes array


#endif