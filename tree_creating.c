#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "types.h"
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
    // Creating a new node from two child nodes
    // allocating memory for the new node
    CharStat* a = malloc(sizeof(CharStat));
    // Allocation error check
    if (a == NULL) { perror("Memory error in create_a_new_node"); exit(EXIT_FAILURE); }

    // filling the new node
    a->Left = left; // left child
    a->Right = right; // right child
    a->character = '\0'; // internal node has no character
    a->count = left->count + right->count; // sum of counts
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

        // Allocation error check
        if (b == NULL) {
            perror("Memory allocation error for CharStat element in create_a_pointer_array");
            exit(EXIT_FAILURE);
        }
        //filling the element 
        b->character = arr[i].character; // copying character
        b->count = arr[i].count; // copying count
        b->Left = NULL; // no left child
        b->Right = NULL; // no right child

        // filling the array 
        ptr_array[i] = b;
    }
    //passing back the pointer of the pointer array
    return ptr_array;
}

CharStat* create_a_tree(CharStat** array, int size) {
    if (size == 0) return NULL; // handle empty array
    if (size == 1) return array[0]; // single element is the tree

    // ensure ascending order: smallest first with qsort 
    qsort(array,size,sizeof(CharStat*), cmp_charstat_ptr_by_count);

    int current_size = size;
    printf("Merging nodes, current size: %d\n", current_size);

    while (current_size > 1) {
        // Debug print
        

        // a két legkisebb: index 0 és 1 (ha merge_sort ascending)
        CharStat* left = array[0];
        CharStat* right = array[1];

        // create new node
        CharStat* new_node = create_a_new_node(left, right);

        // place new_node at index 0
        array[0] = new_node;

        // shift everything left: drop index 1 (right)
        for (int i = 1; i < current_size - 1; ++i) {
            array[i] = array[i + 1];
        }

        // decrease size (we consumed two nodes, produced one)
        current_size--;
        printf("Merging nodes, current size: %d\n", current_size);
        // reorder the array of size current_size
        qsort(array, current_size, sizeof(CharStat*), cmp_charstat_ptr_by_count);
    }

    // root is now at index 0
    return array[0];
}

void free_huffman_tree(CharStat* root) {
// this is a function for free the binary tree
    if (root == NULL) return;       // the end point check
    free_huffman_tree(root->Left);  // free the left side recursively
    free_huffman_tree(root->Right); // free the right side recursively
    free(root);                     // free the root
}

// Comparison function for qsort to sort CharStat pointers by count (and character for tie-breaking)
int cmp_charstat_ptr_by_count(const void *pa, const void *pb) {
    const CharStat * const * a = pa;   // casting to pointer to pointer to CharStat
    const CharStat * const * b = pb;   // casting to pointer to pointer to CharStat

    if ((*a)->count < (*b)->count) return -1;  // smaller frequency first
    if ((*a)->count > (*b)->count) return 1;   // larger frequency last

    // if frequency is equal, sort by ASCII
    if ((*a)->character < (*b)->character) return -1;
    if ((*a)->character > (*b)->character) return 1;

    return 0; // completely equal
}

// Comparison function for qsort to sort binary_huffman_code by character
int cmp_binary_huffman_code_by_char(const void *pa, const void *pb) {
    const binary_huffman_code * a = pa;   // casting to pointer to binary_huffman_code
    const binary_huffman_code * b = pb;   // casting to pointer to binary_huffman_code
    if (a->ch < b->ch) return -1;  // smaller ASCII first
    if (a->ch > b->ch) return 1;   // larger ASCII
    return 0; // equal
}   

