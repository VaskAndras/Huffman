#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "types.h"
#include "merge_sort.h"
#include "from_array_to_binary_tree.h"
#include "opeararing_with_character_codes.h"

void fill_codes(CharStat* root, huffman_codes* arr, char*newcode,int *index ,int depth){
    //the gole of the function is to fill the array with recursion but an another function will be needed
    if (root == NULL) return;

    // If I found a leaf
    if (root->Left == NULL && root->Right == NULL) {
    newcode[depth] = '\0'; // the last character of the code will be the end of string
    arr[*index].ch = root->character; //the character of the next element of the result array will be the character of the leef
    strcpy(arr[*index].code, newcode); // the code part of the new element will be the newcode
    (*index)++; //increase bc it's needed for the next element and it's a pointer bc it's value goes thruough the recursion
    return; // end of this part of the recursion
    }
    
    // Left side  part the code will be 0
    newcode[depth] = '0'; // the 
    fill_codes(root->Left, arr, newcode, index,depth + 1);

    // right side part the code will be 1
    newcode[depth] = '1';
    fill_codes(root->Right, arr, newcode, index, depth + 1);
}

huffman_codes *fill_the_array(CharStat* root, int size){
    // the goal is to give back a perfectly sized array with the codes
    huffman_codes* a = (huffman_codes*)malloc(size*sizeof(huffman_codes));
    char newcode[128]={0}; //should be enought
    int index = 0;
    int depth = 0;
    fill_codes(root, a, newcode, &index, depth); 
    return a;
}

binary_huffman_code* convert_to_binary_huffman_codes(huffman_codes* codes, int size) {
    // The goal is to convert the huffman_codes array to binary_huffman_code array
    binary_huffman_code* binary_codes = (binary_huffman_code*)malloc(size * sizeof
    (binary_huffman_code));
    if (binary_codes == NULL) {
        perror("Memory allocation error in convert_to_binary_huffman_codes");
        exit(EXIT_FAILURE);
    }
    // Filling the binary_huffman_code array
    for (int i = 0; i < size; i++) {
        binary_codes[i].ch = codes[i].ch; // Copy the character
        int bit_len = strlen(codes[i].code); // Length of the code in bits
        binary_codes[i].bit_len = bit_len; // Set the bit length(in the new struct)

        // Calculate number of bytes needed (the +7 is for rounding up, for example 9 bits need 2 bytes)
        int byte_len = (bit_len + 7) / 8; 

        // Allocate memory for the bits array
        binary_codes[i].bits = (unsigned char*)calloc(byte_len, sizeof(unsigned char));

        // Error handling for memory allocation
        if (binary_codes[i].bits == NULL) { 
            perror("Memory allocation error for bits in convert_to_binary_huffman_codes");
            exit(EXIT_FAILURE);
        }

        // Fill the bits array
        for (int j = 0; j < bit_len; j++) {
            // Set the appropriate bit in the bits array
            if (codes[i].code[j] == '1') { 
                // set the proper bit to 1 by using bitwise OR and shift
                binary_codes[i].bits[j / 8] |= (1 << (7 - (j % 8))); 
                // j%8 gives the position within the byte 0-7
                // 7-(j%8) because we want to fill from the left side 
                // << is the left shift operator with the value of the position
                // |= is the bitwise OR assignment operator
                // we add 1 to the proper position
                // Example: if j=0, we set the highest bit of the first byte
                // if j=9, we set the second highest bit of the second byte
                // this way we build the binary representation bit by bit
                // the rest of the bits remain 0 due to calloc                
         }   
        }
    }
    return binary_codes;
}
