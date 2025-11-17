#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "types.h"

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

#endif
