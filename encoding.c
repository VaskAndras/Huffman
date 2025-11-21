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
    merge_sort_for_binary(&binary_codes, size); // sorting the array for faster searching later

    return binary_codes;
}
void create_a_file_if_not_exists(char* filename) {
    // The goal is to create a file if it does not exist
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // File does not exist, create it
        file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error creating file");
            exit(EXIT_FAILURE);
        }
    } else {
        // File exists, just close it
        fclose(file);
    }
}

void create_a_header(char* filename, CharStat* filtered_array, int size) {
    // The goal is to create a header in the specified file
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for header creation");
        exit(EXIT_FAILURE);
    }
    // Write the number of unique characters
    fwrite(&size, sizeof(int), 1, file);
    // Write each character and its frequency
    for (int i = 0; i < size; i++) {
        fwrite(&filtered_array[i].character, sizeof(char), 1, file);
        fwrite(&filtered_array[i].count, sizeof(int), 1, file);
    }
    fclose(file);
}


void write_encoded_data(char* input_filename,char* output_filename , binary_huffman_code* binary_codes, int size) {
    // The goal is to write the encoded data to a file
    FILE* output_file = fopen(output_filename, "ab"); // open in append binary mode

    // Error handling for file opening
    if (output_file == NULL) {
        perror("Error opening file for writing encoded data");
        exit(EXIT_FAILURE);
    }
    // open the original file to read and encode its content
    FILE* input_file = fopen(input_filename, "r"); // open in read mode

    // Error handling for file opening
    if (input_file == NULL) {
        perror("Error opening input file for encoding");
        exit(EXIT_FAILURE);
    }
    int ch;
    uint64_t buffer = 0; // buffer to hold bits before writing to file
    int bit_count = 0; // number of bits currently in the buffer
    while ((ch = fgetc(input_file)) != EOF) {
        // Find the corresponding binary_huffman_code for the character
        binary_huffman_code code = find_binary_code(binary_codes, size, (char)ch);
        
        if (code.bit_len == 0) {
            fprintf(stderr, "Error: Character '%c' not found in binary_huffman_code array\n", ch);
            exit(EXIT_FAILURE);
        }
        // Write the bits of the code to the buffer

    // worst case scenario the code is longer than 64 bits
       if (code.bit_len > 64) {
            
            int remaining_bits = code.bit_len; // bits left to write
            int bit_index = 0; // current bit index in the code
            
            // Write in chunks of 63 bits
            while (remaining_bits > 0) {
                // Determine how many bits to write in this chunk (max 63)
                int bits_to_write = remaining_bits > 63 ? 63 : remaining_bits; // max 63 bits at a time
                // Extract the chunk from the code
                uint64_t chunk = 0; 

                // Build the chunk bit by bit
                for (int i = 0; i < bits_to_write; i++) {
                    int byte_index = (bit_index + i) / 8; // which byte
                    int bit_index_in_byte = 7 - ((bit_index + i) % 8); // which bit in the byte
                    int bit = (code.bits[byte_index] >> bit_index_in_byte) & 1; // extract the bit
                    chunk = (chunk << 1) | bit; // append the bit to the chunk 
                }
                // Append chunk to buffer
                for (int i = 0; i < bits_to_write; i++) {
                    int bit = (chunk >> (bits_to_write - 1 - i)) & 1;
                    buffer = (buffer << 1) | bit;
                    bit_count++;
                    if (bit_count == 8) {
                        unsigned char byte_to_write = (unsigned char)(buffer & 0xFF);
                        fwrite(&byte_to_write, sizeof(unsigned char), 1, output_file);
                        buffer = 0; // reset buffer
                        bit_count = 0; // reset bit count
                    }
                }
                remaining_bits -= bits_to_write; // decrease remaining bits by the number written
                bit_index += bits_to_write; // move the bit index forward
            }
        }
        else {
            // Normal case: code length <= 64 bits
            for (int i = 0; i < code.bit_len; i++) {
                int byte_index = i / 8; // which byte
                int bit_index_in_byte = 7 - (i % 8); // which bit
                int bit = (code.bits[byte_index] >> bit_index_in_byte) & 1; // extract the bit
                buffer = (buffer << 1) | bit; // append the bit to the buffer
                bit_count++;
                // If we have 8 bits in the buffer, write it to the file
                if (bit_count == 8) {
                    unsigned char byte_to_write = (unsigned char)(buffer & 0xFF);
                    fwrite(&byte_to_write, sizeof(unsigned char), 1, output_file);
                    buffer = 0; // reset buffer
                    bit_count = 0; // reset bit count
                }
            }
        }
    }
    // Write any remaining bits in the buffer to the file
    if (bit_count > 0) {
        buffer <<= (8 - bit_count); // shift to fill the last byte 
        unsigned char byte_to_write = (unsigned char)(buffer & 0xFF); // get the last byte
        fwrite(&byte_to_write, sizeof(unsigned char), 1, output_file); // write it to the file
    } 
    fclose(input_file);
    fclose(output_file);
}

void encoding_main(char* input_filename, char* output_filename){
    // Main function to handle the encoding process
    int frequency_array_size = 0;
    CharStat* frequency_array = create_frequency_array(input_filename, &frequency_array_size);
    // creating a pointer array for the huffman tree creation
    CharStat **pointer_array = create_a_pointer_array(frequency_array, frequency_array_size);
    // Build the Huffman tree
    CharStat *huffman_tree_root = create_a_tree(pointer_array, frequency_array_size);
    // Create the huffman_codes array
    huffman_codes* codes = fill_the_array(huffman_tree_root, frequency_array_size);
    // Convert to binary_huffman_code array
    binary_huffman_code* binary_codes = convert_to_binary_huffman_codes(codes, frequency_array_size);
    // Create a file if not exists
    create_a_file_if_not_exists(output_filename);
    // Create a header in the output file
    create_a_header(output_filename, frequency_array, frequency_array_size);
    // Write the encoded data to the output file
    write_encoded_data(input_filename, output_filename, binary_codes, frequency_array_size);
}