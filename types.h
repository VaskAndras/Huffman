#ifndef TYPES_H
#define TYPES_H

typedef struct CharStat { 
    // structure for character statistics (this is recursively used for tree nodes)
    char character; // the character
    int count;      // its frequency
    struct CharStat *Left;  // left child in the Huffman tree
    struct CharStat *Right; // right child in the Huffman tree
} CharStat;

typedef struct { 
    // structure for storing Huffman codes
    char ch;    // a character
    char code[32];  // its Huffman code as a string
} huffman_codes;    

typedef struct {
    // structure for binary representation of Huffman codes
    char ch;          // a character
    unsigned char* bits; // a pointer to the bits representing the code, this is an array of bytes 
    int bit_len;      // length of the code in bits
} binary_huffman_code;

#endif