/**
* @file commands.c
* @brief Implementation of vector commands
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 5
* Name: Megan Cranston
*/

#include <stdio.h>
#include "operations.h"
#include "commands.h"
#include "vectors.h"

/*
* @brief Display help information
*/
void help() {
    printf("Vector Command Help Menu:\n");
    printf("Available commands:\n");
    printf("\t<name> = <x> <y> <z>\t\tCreate a new vector with the given name and components.\n");

    printf("\nAssignment operations:\n");
    printf("\t<name> = <name> + <name>\tAdd two vectors\n");
    printf("\t<name> = <name> - <name>\tSubtract two vectors\n");
    printf("\t<name> = <name> . <name>\tDot product of two vectors\n");
    printf("\t<name> = <name> * <name>\tCross product of two vectors\n");
    printf("\t<name> = <name> * <scalar>\tScale a vector\n");

    printf("\nDisplay operations:\n");
    printf("\t<name>\t\t\t\tView an existing vector\n");
    printf("\t<name> + <name>\t\t\tAdd two vectors\n");
    printf("\t<name> - <name>\t\t\tSubtract two vectors\n");
    printf("\t<name> . <name>\t\t\tDot product of two vectors\n");
    printf("\t<name> * <name>\t\t\tCross product of two vectors\n");
    printf("\t<name> * <scalar>\t\tScale a vector\n");

    printf("\nMiscellaneous operations:\n");
    printf("\tlist\t\t\t\tList all stored vectors\n");
    printf("\tclear\t\t\t\tClear all stored vectors\n");
    printf("\tquit\t\t\t\tExit the program\n");

    printf("\nNote: Only spaces and commas are allowed as separators in commands\n\n");
}

/*
* @brief Clear all stored vectors
* @param vectors - The array of stored vectors
* @param vect_count - The number of stored vectors
*/
void clear(vect vectors[], int vect_count) {
    for (int i = 0; i < vect_count; i++) {
        vectors[i].name[0] = '\0';
        vectors[i].x = 0;
        vectors[i].y = 0;
        vectors[i].z = 0;
    }
    printf("All stored vectors cleared.\n");
}

/*
* @brief List all stored vectors
* @param vectors - The array of stored vectors
* @param vect_count - The number of stored vectors
*/
void list(vect vectors[], int vect_count) {
    printf("Stored vectors:\n");
    for (int i = 0; i < vect_count; i++) {
        printf("\t%s: %.2f, %.2f, %.2f\n", vectors[i].name, vectors[i].x, vectors[i].y, vectors[i].z);
    }
}