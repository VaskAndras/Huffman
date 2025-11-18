#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "tree_creating.h"
#include "merge_sort.h"
#include "debugmalloc.h"

int main(){
    int List_of_characters[128];
    
    for (int i = 0; i<128; i++){
        List_of_characters[i] = 0;
    }

    printf("Please write ");

    char scan;
    while (scanf("%c", &scan ) == 1){
        int int_scan = (int)scan;
        List_of_characters[int_scan]++;
    }

    printf("\nFrequency\n");
    for (int i = 0; i < 128; i++){
        char chari = (char)i;
        printf("%c appeard %d times\n", chari, List_of_characters[i]);
    }


    int count = 0;
    CharStat *filtered = compress_chars_dynamic(List_of_characters, 128, &count);

    printf("Nem nullás karakterek (%d):\n", count);
    for (int i = 0; i < count; i++) {
        printf("'%c' → %d\n", filtered[i].character, filtered[i].count);
    }

    printf("ordered solution");
    for (int i = 0; i < count; i++) {
        printf("'%c' → %d\n", filtered[i].character, filtered[i].count);
    }
    

    CharStat** Filtered_extra = create_a_pointer_array(filtered, count);

    CharStat * Tree = create_a_tree(Filtered_extra, count);

    huffman_codes * codes = fill_the_array(Tree, count);
    
    for (int i = 0; i < count; i++) {
        printf("\n'%c'", codes[i].ch);
            for (int j = 0; codes[i].code[j] != '\0'; j++ ){
                printf("%c",codes[i].code[j]);
                
            }
        fflush(stdout); // azonnal kiírja a buffer tartalmát
    }

free_huffman_tree(Tree);   // felszabadítja az összes csomópontot + leaf-eket
free(filtered);            // eredeti tömb
free(Filtered_extra);      // csak a pointertömb maga
free(codes);               // ha malloc-olt

debugmalloc_dump();    



 return 0;
    }