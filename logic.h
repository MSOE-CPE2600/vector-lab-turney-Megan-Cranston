/**
* @file logic.h
* @brief header file for the logic handling methods
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 7
* Name: Megan Cranston
*
*/

#include "vectors.h"

#ifndef LOGIC_H
#define LOGIC_H

void parse_input(char *str, char index[6][50]);
int determine_command(char index0[50], char index1[50], vect **vector, int *count, int *CAP);
int validate_input(char index[6][50], vect *vector, int count);
int determine_operation(char index[6][50], vect *vector, int *count, int *CAP);

int create_space(vect **vector, int *count, int *CAP);
vect perform_operation(char A[50], char op[50], char B[50], vect *vector, int count);
int is_float(char str[]);

#endif // LOGIC_H