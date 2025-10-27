/**
* @file fileio.h
* @brief 
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 7
* Name: Megan Cranston
*
*/

#include "vectors.h"

#ifndef FILEIO_H
#define FILEIO_H

void load(char filename[50], vect **vector, int *count, int *CAP);
void save(char filename[50], vect *vector, int *count);
int count_lines(FILE *infile);

#endif // FILEIO_H