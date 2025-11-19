#ifndef MERGE_SORT_H
#define MERGE_SORT_H
#include "types.h"

/*
== Mergesort module ==
This module provides functions for sorting arrays using the merge sort algorithm.
This can be a little bit overkill for small arrays, but it was a great exercise.
Functions:
1. merge: Merges two sorted subarrays into a single sorted array
2. merge_sort: Recursively sorts an array using the merge sort algorithm
3. merge_for_binary: Merges two sorted subarrays for binary_huffman_code structures
4. merge_sort_for_binary: Recursively sorts an array of binary_huffman_code structures using merge sort
*/

void merge(CharStat **array, int left_length, int right_length);
// Merges two sorted subarrays into a single sorted array
// Parameters:
// - array: pointer to the array of CharStat pointers
// - left_length: length of the left subarray
// - right_length: length of the right subarray

void merge_sort(CharStat **array, int length);
// Performs merge sort on an array of CharStat pointers
// Parameters:
// - array: pointer to the array of CharStat pointers
// - length: number of elements in the array
// Sorts the array in place
// works with merge function(recursive)

void merge_for_binary(binary_huffman_code **array, int left_length, int right_length);
// Merges two sorted subarrays for binary_huffman_code
// Parameters:
// - array: pointer to the array of binary_huffman_code pointers
// - left_length: length of the left subarray
// - right_length: length of the right subarray

void merge_sort_for_binary(binary_huffman_code **array, int length);
// Recursive merge sort function for binary_huffman_code
// Parameters:
// - array: pointer to the array of binary_huffman_code pointers
// - length: number of elements in the array
// Sorts the array in place
// works with merge_for_binary function(recursive)

binary_huffman_code find_binary_code(binary_huffman_code* array, int size, char ch);
// Binary search for a character in a sorted array of binary_huffman_code
// Parameters:
// - array: pointer to the sorted array of binary_huffman_code
// - size: number of elements in the array
// - ch: character to search for
// Returns:
// - the found binary_huffman_code structure


#endif
