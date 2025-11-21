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

void create_a_file_if_not_exists(char* filename);
// Creates a file with the given filename if it does not already exist
// Parameters:
// - filename: name of the file to create


void create_a_header(char* filename, CharStat* filtered_array, int size);
// Creates a header file containing character frequency data
// Parameters:
// - filename: name of the header file to create
// - filtered_array: array of CharStat containing character frequencies
// - size: number of elements in the filtered_array

void write_encoded_data(char* input_filename,char* output_filename , binary_huffman_code* binary_codes, int size);
// Writes encoded data to a binary file
// Parameters:
// - input_filename: name of the input file to read original data from
// - output_filename: name of the output file to write encoded data to
// - binary_codes: array of binary_huffman_code for encoding
// - size: number of elements in the binary_codes array
void encoding_main(char* input_filename, char* output_filename);
// Main function to handle the encoding process
// Parameters:
// - input_filename: name of the input file to read original data from
// - output_filename: name of the output file to write encoded data to





#endif