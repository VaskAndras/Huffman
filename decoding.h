#ifndef DECODING_H
#define DECODING_H
#include "types.h"

CharStat* rebuild_huffman_tree_from_header(FILE *input_file);
// Rebuilds the Huffman tree from the header information in the input file.

void decode_file(char *input_filename, char *output_filename);
// Decodes the encoded file using the reconstructed Huffman tree and writes the original data to the output file.
#endif