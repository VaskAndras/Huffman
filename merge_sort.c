#include <stdlib.h>
#include <stdio.h>
#include "debugmalloc.h"
#include "merge_sort.h"
#include "types.h"
/*
================================================================
                            MERGE_SORT.C
================================================================
This file contains functions related to merge sort algorithm.
Functions:
1. merge: Merges two sorted subarrays into a single sorted array
2. merge_sort: Recursively sorts an array using the merge sort algorithm
3. merge_for_binary: Merges two sorted subarrays for binary_huffman_code structures
4. merge_sort_for_binary: Recursively sorts an array of binary_huffman_code structures using merge sort
*/

// Merge two sorted subarrays: left part of length left_length, right part of length right_length
void merge(CharStat **array, int left_length, int right_length){
    CharStat **Left = (CharStat**)malloc(left_length * sizeof(CharStat*));
    CharStat **Right = (CharStat**)malloc(right_length * sizeof(CharStat*));
    // Error handling 
    if (Left == NULL || Right == NULL) {
        perror("Memory allocation error in merge");
        exit(EXIT_FAILURE);
    }

    // Copy data to temporary arrays
    //simple copy, elemently
    for (int i = 0; i < left_length; i++) {
        Left[i] = array[i];
    }
    for (int i = 0; i < right_length; i++) {
        Right[i] = array[left_length + i];
    }
    
    // initializeing
    int leftcount = 0, rightcount = 0, overwrite = 0;

    // Merge elements back into original array
    // check if they are in the range
    while (leftcount < left_length && rightcount < right_length) {
        // Smaller goes first and if equal the abc order matter
        if (Left[leftcount]->count > Right[rightcount]->count || (Left[leftcount]->count == Right[rightcount]->count && Left[leftcount]->character >= Right[rightcount]->character)) {
        
            // operate than add one
            array[overwrite++] = Left[leftcount++];
        
        // other case
    } else {
            // same as above
            array[overwrite++] = Right[rightcount++];
        }
    }

    // Copy any remaining elements from Left
    while (leftcount < left_length) {
        array[overwrite++] = Left[leftcount++];
    }

    // Copy any remaining elements from Right
    while (rightcount < right_length) {
        array[overwrite++] = Right[rightcount++];
    }

    // Free up the memory
    free(Left);
    free(Right);
}

// Recursive merge sort function
void merge_sort(CharStat **array, int length){
    // check if it's too short, if is, we dont have to change anyting.
    if (length <= 1) return;
    // calculates the left and right half of the array
    int left_length = length / 2;
    int right_length = length - left_length;

    // recursive part
    // we will be in the array all the time but now we have to take parts of that 
    //the left side is basically just the first some elemets till left  
    merge_sort(array, left_length);
    // right part's pointer is just shifted with the length of the left part ( Black magic :) ) 
    merge_sort(array + left_length, right_length);
    // this will do the hard work.
    merge(array, left_length, right_length);
}

void merge_for_binary(binary_huffman_code **array, int left_length, int right_length){
    // Merge two sorted subarrays for binary_huffman_code
    // same as above, but for binary_huffman_code struct

    // Allocate temporary arrays for left and right subarrays
    binary_huffman_code **Left = (binary_huffman_code**)malloc(left_length * sizeof(binary_huffman_code*));
    binary_huffman_code **Right = (binary_huffman_code**)malloc(right_length * sizeof(binary_huffman_code*));

    // Error handling 
    if (Left == NULL || Right == NULL) {
        perror("Memory allocation error in merge_for_binary");
        exit(EXIT_FAILURE);
    }
    // Copy data to temporary arrays
    for (int i = 0; i < left_length; i++) {
        Left[i] = array[i];
    }
    for (int i = 0; i < right_length; i++) {
        Right[i] = array[left_length + i];
    }
    // initializeing
    int leftcount = 0, rightcount = 0, overwrite = 0;
    // Merge elements back into original array
    while (leftcount < left_length && rightcount < right_length) {
        // Smaller goes first and if equal the abc order matter
        if (Left[leftcount]->ch > Right[rightcount]->ch) {
            // operate than add one
            array[overwrite++] = Left[leftcount++];
        } else {
            // same as above
            array[overwrite++] = Right[rightcount++];
        }
    }

    // Copy any remaining elements from Left
    while (leftcount < left_length) {
        array[overwrite++] = Left[leftcount++];
    }
    
    // Copy any remaining elements from Right
    while (rightcount < right_length) {
        array[overwrite++] = Right[rightcount++];
    }

    // Free up the memory
    free(Left);
    free(Right);
}


void merge_sort_for_binary(binary_huffman_code **array, int length){
    // Recursive merge sort function for binary_huffman_code
    if (length <= 1) return;

    // calculates the left and right half of the array
    int left_length = length / 2;
    int right_length = length - left_length;

    // recursive part
    // we will be in the array all the time but now we have to take parts of
    //the left side is basically just the first some elemets till left
    merge_sort_for_binary(array, left_length);
    merge_sort_for_binary(array + left_length, right_length);

    // this will do the hard work.
    merge_for_binary(array, left_length, right_length);
}
