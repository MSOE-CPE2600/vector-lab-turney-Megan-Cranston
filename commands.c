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
*/
void clear() {

}

/*
* @brief Quit the program
*/
void quit() {

}