#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "types.h"
#include "merge_sort.h"
#include "tree_creating.h"
/*
================================================================
                        TREE_CREATING.C
================================================================
This file contains functions related to creating and managing the Huffman tree.
Functions:
1. create_a_new_node: Creates a new tree node from two child nodes
2. create_a_pointer_array: Creates an array of pointers to CharStat structures
3. create_a_tree: Builds the Huffman tree from an array of CharStat pointers
4. free_huffman_tree: Frees the memory allocated for the Huffman tree
5. from_array_to_character_codes: Converts an input frequency array to Huffman codes using the Huffman tree
*/

CharStat* create_a_new_node(CharStat *left, CharStat *right) {
// This is a function for creating a new node of the tree
    //lets allocate memory for this task
    CharStat* a = malloc(sizeof(CharStat));
    if ( a == NULL ) { // allocation check
        perror("Memory error in create_a_new_node");
        exit(EXIT_FAILURE);
    }
    // filling with properties
    a->Left = left;   
    a->Right = right; 
    a->character = '\0'; // bc it's inside 
    a->count = left->count + right->count; // the sum of the counts of the leafs is the value of this point 
    return a;
}
CharStat** create_a_pointer_array(CharStat* arr, int size) {
    // Creating an array 
    CharStat** ptr_array = (CharStat**)malloc(size * sizeof(CharStat*));
    // Allocation error
    if (ptr_array == NULL) {
        perror("Memory allocation error for pointer array in create_a_pointer_array");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        //allocating a new charstat element 
        CharStat* b = (CharStat*)malloc(sizeof(CharStat));
        if (b == NULL) {
            perror("Memory allocation error for CharStat element in create_a_pointer_array");
            exit(EXIT_FAILURE);
        }
        //filling the element 
        b->character = arr[i].character;
        b->count = arr[i].count;
        b->Left = NULL;
        b->Right = NULL;

        // filling the array 
        ptr_array[i] = b;
    }
    //passing back the pointer of the pointer array
    return ptr_array;
}

CharStat* create_a_tree(CharStat** array, int size) {
    // the goal is to create a pointer to the first element of the binary tree

    //if the array is too small
    if (size == 0) return NULL;
    if (size == 1) return array[0];

    //ordering the elements by frequency and then by ASCII
    merge_sort(array, size);

    int current_size = size;

    while (current_size > 1) {
        // finding the smallest two elements 
        CharStat* left = array[current_size - 2];
        CharStat* right = array[current_size - 1];

        // create a new node from the smallest 2 elements 
        CharStat* new_node = create_a_new_node(left, right);

        // modify the pointer of the 2. smallest element
        array[current_size - 2] = new_node;

        // the size is decreasing 
        current_size--;

        // reordering 
        merge_sort(array, current_size);
    }

    // return the root 
    return array[0];


}

void free_huffman_tree(CharStat* root) {
// this is a function for free the binary tree
    if (root == NULL) return;       // the end point check
    free_huffman_tree(root->Left);  // free the left side recursively
    free_huffman_tree(root->Right); // free the right side recursively
    free(root);                     // free the root
}





