#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "types.h"
#include "merge_sort.h"
#include "tree_creating.h"
#include "encoding.h"

/*
================================================================
                            ENCODING.C
================================================================
This file contains functions related to encoding using Huffman coding.
Functions:
1. get_a_filename: Gets a filename from the user
2. create_frequency_array: Creates a frequency array from a file
3. fill_codes: Fills the huffman_codes array with codes generated from the Huffman tree
4. fill_the_array: Creates and returns an array of huffman_codes from the Huffman tree
5. convert_to_binary_huffman_codes: Converts an array of huffman_codes to an array of binary_huffman_code
6. from_array_to_character_codes: Converts an input frequency array to Huffman codes using the Huffman tree
7. create_a_file_if_not_exists: Creates a file with the given filename if it does not already exist
8. create_a_header: Creates a header file containing character frequency data
9. write_encoded_data: Writes encoded data to a binary file
*/


char* get_a_filename(){
    // The goal is to get a filename from the user
    char filename[256]; // buffer to hold the filename input
    printf("Enter the filename: ");

    if (fgets(filename, sizeof(filename), stdin) != NULL) {

        // the last character can be a newline character, we need to remove it
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }

        // Allocate memory for the filename to return
        char* result = (char*)malloc((strlen(filename) + 1) * sizeof(char));

        // Error handling for memory allocation
        if (result == NULL) {
            perror("Memory allocation error in get_a_filename");
            exit(EXIT_FAILURE);
        }

        // Copy the filename to the allocated memory
        strcpy(result, filename);

        return result; 
    } else {
        // Error handling for input failure
        perror("Error reading filename");
        exit(EXIT_FAILURE);
    }
}

CharStat* create_frequency_array(char* filename, int* out_count){
    // The goal is to create a frequency array from a file
    FILE* file = fopen(filename, "r"); // open the file in read mode
    
    // Error handling for file opening
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int frequencies[128] = {0}; // number of ASCII characters

    int ch;
    // Read the file character by character and count frequencies
    while ((ch = fgetc(file)) != EOF) {
        if (ch >= 0 && ch < 128) {
            frequencies[ch]++;
        }
    }

    fclose(file);
    int size = 0;

    for (int i = 0; i < 128; i++) {
        if (frequencies[i] > 0) {
            size++;
        }
    }
    // Now create the frequency array
    CharStat* freq_array = (CharStat*)malloc(size * sizeof(CharStat));

    // Error handling for memory allocation
    if (freq_array == NULL) {
        perror("Memory allocation error in create_frequency_array");
        exit(EXIT_FAILURE);
    }

    // Fill the frequency array, j is the index for freq_array, i for the original array
    for (int i = 0, j = 0; i < 128; i++) { 
        if (frequencies[i] > 0) {
            freq_array[j].character = (char)i;
            freq_array[j].count = frequencies[i];
            freq_array[j].Left = NULL;
            freq_array[j].Right = NULL;
            j++;
        }
    }
    *out_count = size; // set the output count
    return freq_array; // return the frequency array
}

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
    binary_huffman_code* binary_codes = (binary_huffman_code*)malloc(size * sizeof(binary_huffman_code));
    
    // Error handling for memory allocation
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
                // the rest of the bits are already 0 because of calloc               
         }   
        }
    }
    return binary_codes;
}
