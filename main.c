#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "tree_creating.h"
#include "merge_sort.h"
#include "debugmalloc.h"
#include "encoding.h"
#include "decoding.h"

// TESTING MAIN FUNCTION

int main() {
    char input_filename[256];
    char encoded_filename[256];
    char output_filename[256];

    printf("Enter input filename: ");
    scanf("%255s", input_filename);

    printf("Enter encoded filename: ");
    scanf("%255s", encoded_filename);

    printf("Enter decoded output filename: ");
    scanf("%255s", output_filename);

    printf("\n=== Encoding Phase ===\n");
    encoding_main(input_filename, encoded_filename);
    printf("Encoding completed successfully!\n");

    printf("\n=== Decoding Phase ===\n");
    decoding_main(encoded_filename, output_filename);
    printf("Decoding completed successfully!\n");

    printf("\nAll tasks completed.\n");

    return 0;
}

    