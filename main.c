/**
* @file main.c
* @brief 
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 5
* Name: Megan Cranston
*
* compile: gcc main.c operations.c commands.c -o vector_lab
*
* Algorithm:
* - Initialize vector storage
* - Loop until user quits
*   - Prompt user for input
*   - Parse input into components
*   - Determine command type (help, clear, list, quit, create vector, display vector, perform operation)
*   - Execute command
*   - Handle errors (invalid command, vector not found, storage full)
* - End program
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"
#include "commands.h"
#include "vectors.h"

#define SIZE 10

vect perform_operation(vect vectors[], int index_a, char operation[50], int index_b);
int is_float(char str[]);

int main(int argc, char *argv[]) {

    // check for -h argument
    if (argc > 1 && !strcmp(argv[1], "-h")) help();
    
    char input[256];
    vect vectors[SIZE]; 
    int vect_count = 0;

    while (1) {
        // scan input
        printf("minimat> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        // parse input, turn commas into spaces
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == ',') {
                input[i] = ' ';
            }
        } 

        char index0[50] = "", index1[50] = "", index2[50] = "", index3[50] = "", index4[50] = "", index5[50] = "";
        sscanf(input, "%s %s %s %s %s %s", index0, index1, index2, index3, index4, index5);

        if (!strcmp(index0, "quit")) {
            return 0;
        } else if (!strcmp(index0, "help")) {
            help();
            continue;
        } else if (!strcmp(index0, "clear")) {
            clear(vectors, vect_count);
            vect_count = 0;
            continue;
        } else if (!strcmp(index0, "list")) {
            list(vectors, vect_count);
            continue;
        }

        // check for invalid inputs
        if (index5[0] != '\0') {
            // extra input
            printf("Error: Extra input entered.\n");
            continue;
        } else if (index0[0] == '\0') {
            // no input
            printf("Error: No input entered.\n");
            continue;
        } else if (index0[0] != '\0' && !strcmp(index1, "=") && (index2[0] == '\0' || index3[0] == '\0' || index4[0] == '\0')) {
            // invalid: a = 1 2, a = 1, a = b +
            printf("Error: Invalid assignment.\n");
            continue;
        } else if ((is_float(index0) || is_float(index2)) && strcmp(index1, "*") != 0 && strcmp(index1, "=") != 0) {
            // invalid: 1 + a (operation other than scalar)
            printf("Error: Invalid command.\n");
            continue;
        } else if (!strcmp(index1, "=") && ((!is_float(index2) && find_vect(vectors, index2, SIZE) == -1) || (!is_float(index4) && find_vect(vectors, index4, SIZE) == -1))) {
            // invalid: vector not found
            printf("Error: Vector not found.\n");
            continue;
        } 

        // check for existing vector
        int vector_index = find_vect(vectors, index0, vect_count);                
        if (index1[0] == '\0') {
            // print a vector
            if (vector_index != -1) {
                print_vect(vectors[vector_index].name, vectors[vector_index].x, vectors[vector_index].y, vectors[vector_index].z);
             } else {
                printf("Error: Vector not found.\n");
                continue;
            }
        } else if (!strcmp(index1, "=")){
            if (is_float(index2) && is_float(index3) && is_float(index4)) {
                // create new vector
                if (vect_count < SIZE) {
                    if (vector_index != -1) { // vect name already exists, update it
                        vectors[vector_index] = new_vect(index0, atof(index2), atof(index3), atof(index4));
                        continue;
                    }
                    vectors[vect_count++] = new_vect(index0, atof(index2), atof(index3), atof(index4));
                } else {
                    printf("Error: Vector storage full.\n");
                    continue;
                }
            } else if (index3 != '\0') { // format: a = b + c
                int index_a = find_vect(vectors, index2, vect_count);
                int index_b = find_vect(vectors, index4, vect_count);
                vect temp;
                if (index_a != -1 && index_b == -1) {       // a = b * 2
                    temp = scalar_vect(vectors[index_a], atof(index4));
                } else if (index_a == -1 && index_b != -1) { // a = 2 * b
                    temp = scalar_vect(vectors[index_b], atof(index2));
                } else {                                    // not scalar
                    temp = perform_operation(vectors, index_a, index3, index_b);
                }
                if (temp.name == NULL && temp.x == 0 && temp.y == 0 && temp.z == 0) {
                    printf("Error: Invalid operation.\n");
                    continue;
                }
                if (vector_index != -1) { // vect name already exists, update it
                    vectors[vector_index] = new_vect(index0, temp.x, temp.y, temp.z);
                    continue;
                }
                vectors[vect_count++] = new_vect(index0, temp.x, temp.y, temp.z);
            }
        } else if (index1 != '\0') { // format: a + b
            int index_a = find_vect(vectors, index0, vect_count);
            int index_b = find_vect(vectors, index2, vect_count);
            vect temp;
            if (index_a != -1 && index_b == -1) {           // a * 2
                temp = scalar_vect(vectors[index_a], atof(index2));
            } else if (index_a == -1 && index_b != -1) {    // 2 * a
                temp = scalar_vect(vectors[index_b], atof(index0));
            } else {                                        // not scalar    
                temp = perform_operation(vectors, index_a, index1, index_b);
            }
            if (temp.name == NULL && temp.x == 0 && temp.y == 0 && temp.z == 0) {
                printf("Error: Invalid operation.\n");
                continue;
            }
            char name[50] = "ans";
            print_vect(name, temp.x, temp.y, temp.z);
        } else {
            printf("Error: Invalid command.\n");
        }

    }

    return 0;
}

/*
* @brief Perform the specified operation on two vectors
* @param vectors - The array of stored vectors
* @param index_a - The index of the first vector
* @param operation - The operation to perform
* @param index_b - The index of the second vector
* @return vect - The result of the operation
*/
vect perform_operation(vect vectors[], int index_a, char operation[50], int index_b) {
    if (!strcmp(operation, "+")) {
        return add_vect(vectors[index_a], vectors[index_b]);
    } else if (!strcmp(operation, "-")) {
        return sub_vect(vectors[index_a], vectors[index_b]);
    } else if (!strcmp(operation, ".")) {
        return dot_vect(vectors[index_a], vectors[index_b]);
    } else if (!strcmp(operation, "*")) {
        return cross_vect(vectors[index_a], vectors[index_b]);
    } else { // invalid operation
        return new_vect(NULL, 0, 0, 0);
    }
}

/*
* @brief Check if a string is a valid float 
* @param str - The string to check
* @return 1 if the string is a valid float, 0 otherwise
*/
int is_float(char str[]) {
    if (str == NULL || str[0] == '\0') return 0;

    char *endptr;
    strtof(str, &endptr);

    return (*endptr == '\0') ? 1 : 0;
}
