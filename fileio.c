/**
* @file fileio.c
* @brief Read file, count entries, dynamically allocate memory for arrays
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 7
* Name: Megan Cranston
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"
#include "logic.h"
#include "operations.h"

/*
* @brief Enter an index file and read its contents into dynamic vector storage
* @param filename - Name of input file
* @param vector - Dynamically allocated vect array
* @param count - Number of vectors stored
* @param CAP - Max capacity of vector storage before reallocation
*/
void load(char filename[50], vect **vector, int *count, int *CAP) {
    // Open file
    FILE *infile = fopen(filename, "r");
    if (!infile) {
        printf("Error opening file\n");
        return;
    }

    // Count lines
    int num_lines = count_lines(infile);
    if (num_lines <= 0) {
        printf("No data found in file.\n");
        fclose(infile);
        return;
    }

    rewind(infile);

    char str[200];
    // Read data from the file into the arrays
    for (int i = 0; i < num_lines; i++) {
        fgets(str, sizeof(str), infile);
        for (char *p = str; *p; p++) {
            if (*p == ',') *p = ' ';
        }

        char name[50], x[50], y[50], z[50];
        sscanf(str, "%s %s %s %s", name, x, y, z);

        // check valid index
        if (!is_float(x) && !is_float(y) && !is_float(z)) {
            printf("Error: Invalid Input on line %d\n", i+1);
            continue;
        }

        // verify vect name doesn't exist
        if (find_vect(*vector, name, *count) == -1) {

            // check if vect array has space
            int error = 0;
            if (*count == *CAP) {
                error = create_space(vector, count, CAP);
            }
            if (!error) {
                (*vector)[(*count)++] = new_vect(name, atof(x), atof(y), atof(z));
            } else {
                printf("Error: Memory Allocation Failed\n");
                return;
            }
        } else {
            printf("Warning: Line %d vector name already exists, skipped\n", i+1);
        }
    }
    fclose(infile);
}

/*
* @brief Enter an output file and save the contents of vector
* @param filename - Name of output file
* @param vector - Storage of all vector components
* @param count - Number of vectors to output
*/
void save(char filename[50], vect *vector, int *count) {
    FILE *outfile = fopen(filename, "w");
    if (outfile == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < *count; i++) {
        fprintf(outfile, "%s,%.2f,%.2f,%.2f\n", vector[i].name, vector[i].x, vector[i].y, vector[i].z);
    }

    fclose(outfile);
}

/*
* @brief Count the number of lines in a file
* @param infile Pointer to the index file
* @return Number of lines in the file
*/
int count_lines(FILE *infile) {
    int count = 0;
    char buffer[100];

    // Read each line from the file until end of file
    while (fgets(buffer, sizeof(buffer), infile) != NULL) {
        count++;
    }

    return count;
}


