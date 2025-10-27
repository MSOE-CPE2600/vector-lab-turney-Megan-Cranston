/**
* @file main.c
* @brief Interactive vector calculator (mini-Matlab program)
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 5
* Name: Megan Cranston
*
* compile: gcc main.c logic.c fileio.c operations.c commands.c -o vector_lab
*
* Algorithm:
* - Initialize vector storage
* - Loop until user quits
*   - Prompt user for str
*   - Parse str into components
*   - Determine command type (quit, help, clear, list, load, save)
*   - If not command, validate vector input (skip handling)
*   - Determine operation (new vect, math/assign vect, math/print vect)
* - End program
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vectors.h"
#include "logic.h"
#include "commands.h"

int main(int argc, char *argv[]) {

    // check for -h argument
    if (argc > 1 && !strcmp(argv[1], "-h")) help();
   
    char str[256];
    char index[6][50] = {0};

    
    int CAPACITY = 10;
    int count = 0;
    vect *vector = (vect *)malloc(CAPACITY * sizeof(vect));

    // 1 = skip loop
    // 0 = don't skip loop
    int skip = 0;

    while (skip != 2) {
        // scan str
        printf("minimat> ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = 0;

        parse_input(str, index);

    // determine quit, help, clear, list, load, save
    skip = determine_command(index[0], index[1], &vector, &count, &CAPACITY);
        if (skip) {
            continue;
        }

        // validate vector input
        skip = validate_input(index, vector, count);
        if (skip) {
            continue;
        }

        // determine new vect, math/assign vect, math/print vect
        skip = determine_operation(index, vector, &count, &CAPACITY);
    }

    free(vector);

    return 0;
}