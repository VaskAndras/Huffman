#ifndef DECODING_H
#define DECODING_H
#include "types.h"

void read_header(unsigned char *encoded_file, CharStat **out_array, int *out_size);
// read the header of the encoded file and rebuild the frequency array
// Parameters:
// - encoded_file: name of the encoded file
// - out_array: pointer to store the rebuilt frequency array
// - out_size: pointer to store the size of the rebuilt frequency array

void decode_file(CharStat *root, unsigned char *input_filename, unsigned  char *output_filename);
// Decodes the encoded file using the Huffman tree and writes the output to a file
// Parameters:
// - root: pointer to the root of the Huffman tree
// - input_filename: name of the encoded input file
// - output_filename: name of the output file to write the decoded data

void decoding_main(unsigned char *input_filename, unsigned char *output_filename);
// Main function to handle the decoding process
// Parameters:
// - input_filename: name of the encoded input file
// - output_filename: name of the output file to write the decoded data
#endif