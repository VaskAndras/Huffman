#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "types.h"
#include "tree_creating.h"
#include "decoding.h"
#include "encoding.h"

void read_header(char *encoded_file, CharStat **out_array, int *out_size) {
    // Rebuilds the Huffman tree from the header of the encoded file
    FILE *file = fopen(encoded_file, "rb");
    // Error handling for file opening
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    // Read the size of the array
    int size;
    if (fread(&size, sizeof(int), 1, file) != 1) {
        // Error handling for reading size
        fprintf(stderr, "Error reading size from header\n");
        exit(EXIT_FAILURE);
    }
    printf("DEBUG: Header size read as %d\n", size); // DEBUG

    // Allocate memory for the output array
    *out_array = (CharStat *)malloc(size * sizeof(CharStat));

    // Error handling for memory allocation
    if (*out_array == NULL) {
        perror("Memory allocation error in rebuild_huffman_tree_from_header");
        exit(EXIT_FAILURE);
    }

    // Read each character and its frequency
    /*
    for (int i = 0; i < size; i++) {
        char ch;
        int count;
        // Read character
        if (fread(&ch, sizeof(char), 1, file) != 1) {
            fprintf(stderr, "Error reading character from header\n");
            exit(EXIT_FAILURE);
        }
        // Read frequency count
        if (fread(&count, sizeof(int), 1, file) != 1) {
            fprintf(stderr, "Error reading frequency count from header\n");
            exit(EXIT_FAILURE);
        }
        printf("DEBUG: Read char='%c' (0x%02X), count=%d\n", ch, (unsigned char)ch, count); // DEBUG
        fflush(stdout);  // <-- ADD EZT HOZZÁ MINDEN printf UTÁN!

        out_array[i]->character = ch; // filling the character
        out_array[i]->count = count;  // filling the count
        out_array[i]->Left = NULL;    // no left child
        out_array[i]->Right = NULL;   // no right child
    }
    */
   for (int i = 0; i < size; i++) {
        size_t items_read = fread(&((*out_array)[i].character), sizeof(char), 1, file);
        if (items_read != 1) {
            fprintf(stderr, "ERROR at index %d: Could not read character\n", i);
            fprintf(stderr, "File position: %ld\n", ftell(file));
            free(*out_array);
            fclose(file);
            exit(EXIT_FAILURE);
        }
        
        items_read = fread(&((*out_array)[i].count), sizeof(int), 1, file);
        if (items_read != 1) {
            fprintf(stderr, "ERROR at index %d: Could not read count\n", i);
            fprintf(stderr, "Character was: 0x%02X\n", (char)(*out_array)[i].character);
            fprintf(stderr, "File position: %ld\n", ftell(file));
            free(*out_array);
            fclose(file);
            exit(EXIT_FAILURE);
        }
        
        (*out_array)[i].Left = NULL;
        (*out_array)[i].Right = NULL;
    }
    
    *out_size = size;    
    fclose(file);
    return;
}
   


void decode_file(CharStat *root, char *input_filename, char *output_filename) {

    // Decodes the encoded file using the Huffman tree and writes the output to a file
    FILE *input_file = fopen(input_filename, "rb");
    FILE *output_file = fopen(output_filename, "wb");

    // Error handling for file opening
    if (input_file == NULL || output_file == NULL) {
        perror("Error opening input or output file");
        exit(EXIT_FAILURE);
    }
    // Start decoding
    CharStat *current = root;
    char byte;
    size_t bytes_read;

    int size_of_header;
    fread(&size_of_header, sizeof(int), 1, input_file);

    printf("DEBUG: Header size = %d\n", size_of_header); // DEBUG
    // move file pointer to the end of the header
    // the reason of this is that we have already read the size of the header
    // sizeof(int) is for the size_of_header itself
    // sizeof(char) + sizeof(int) is for each character and its frequency count
    fseek(input_file, sizeof(int) + size_of_header * (sizeof(char) + sizeof(int)), SEEK_SET); 


    while ((bytes_read = fread(&byte, sizeof(char), 1, input_file)) == 1) {
        for (int i = 0; i < 8; i++) {
            // Traverse the Huffman tree
            char mask= 0b10000000 >> i;
            if (byte & mask) {
                // Bit is 1, go right
                current = current->Right;
            } else {
                // Bit is 0, go left
                current = current->Left;
            }

            // If we reach a leaf node, write the character to the output file
            if (current->Left == NULL && current->Right == NULL) {
                fwrite(&current->character, sizeof(char), 1, output_file);
                current = root; // Go back to the root for the next character
            }
        }
    }
    // Close the files
    fclose(input_file);
    fclose(output_file);
}
void decoding_main(unsigned char *input_filename, unsigned char *output_filename) {
    // Main function to handle the decoding process
    CharStat *frequency_array = NULL;
    int size = 0;

    // Read the header and rebuild the frequency array
    read_header(input_filename, &frequency_array, &size);

    printf("DEBUG: header read\n"); // DEBUG
    // creating a pointer array for the huffman tree creation
    CharStat **pointer_array = create_a_pointer_array(frequency_array, size);
    printf("DEBUG: pointer array created\n"); // DEBUG
    // Build the Huffman tree
    CharStat *huffman_tree_root = create_a_tree(pointer_array, size);
    printf("DEBUG: Huffman tree created\n"); // DEBUG
    //create a file if not exists
    create_a_file_if_not_exists(output_filename);
    printf("DEBUG: output file ensured\n"); // DEBUG

    // Decode the file using the Huffman tree
    decode_file(huffman_tree_root, input_filename, output_filename);
    printf("DEBUG: file decoded\n"); // DEBUG

    // Free allocated memory
   free(pointer_array);  // just the pointer array
   free(frequency_array); // the CharStat array
   free_huffman_tree(huffman_tree_root); // the internal nodes of the tree
}