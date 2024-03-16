#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 300

int main(int argc, char *argv[]) {
    FILE *in;
    FILE *out;
    char line[MAX];

    //checks command line for correct number of arguments;
    if (argc != 3) {
        printf("Can only accept 2 arguments, <input file> <output file>\n");
        exit(1);
    }
    //open file for reading
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file for reading\n");
        exit(1);
    }
    //open file for writing
    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file for writing\n");
        exit(1);
    }
    //read and count each line of input file
    int cnt = 0;
    while (fgets(line, MAX, in) != NULL) {
        cnt += 1;

    }

    //allocate memory for new array
    char **newArr = calloc(cnt, sizeof(char*));
    for (int i = 0; i < cnt; i += 1) {
        newArr[i] = calloc(MAX, sizeof(char));
    }

    //create new empty list
    List sorted = newList();

    //set cursor to beginning of file
    fseek(in, 0, SEEK_SET);
    
    //copy old array into new array
    int idx = 0;
    while (fgets(line, MAX, in) != NULL) {
        strncpy(newArr[idx], line, MAX);
        idx += 1;
    }
    
    //loop inserting elements into correct spot in list
    append(sorted, 0); 
    for (int i = 1; i < cnt; i += 1) {
        bool found = false;
        moveFront(sorted);
        while (found == false) {   
            if (index(sorted) < 0) {
                moveFront(sorted);
            }
            if (strcmp(newArr[get(sorted)], newArr[i]) < 0) {
                moveNext(sorted);
                 if (index(sorted) < 0) {
                    append(sorted, i);
                    found = true;
                 }
            } else {
                insertBefore(sorted, i);
                found = true;
            }
        } 
    }

    //print out newArr to outfile
    moveFront(sorted);
    while (index(sorted) != -1) {
        fprintf(out, newArr[get(sorted)]);
        moveNext(sorted);
    }
    
    //free allocated memory and close files
    for (int i = 0; i < cnt; i += 1) {
        free(newArr[i]);
    }
    free(newArr);
    freeList(&sorted);
    fclose(in);
    fclose(out);

}