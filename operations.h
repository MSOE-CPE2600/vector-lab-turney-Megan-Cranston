/**
* @file operations.c
* @brief Implementation of vector operations
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 5
* Name: Megan Cranston
*/

#include "vectors.h"

#ifndef OPERATIONS_H
#define OPERATIONS_H

// return 0 if unsuccessful, 1 if successful
int new_vect(char name[50], char x[50], char y[50], char z[50]); // check for valid floats
int vect_name(char name[50]); 
vect add_vect(vect name_a, vect name_b);
vect sub_vect(vect name_a, vect name_b);
float dot_vect(vect name_a, vect name_b); // return x = #, y = 0 and z = 0
vect cross_vect(vect name_a, vect name_b);
vect scalar_vect(vect name, float scalar);

int set_vect(char name[50], vect new_vect);
    // check for vect length room
    // check for existing vect name

#endif // OPERATIONS_H