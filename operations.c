/**
* @file operations.c
* @brief Implementation of vector operations
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 5
* Name: Megan Cranston
*/

#include <stdio.h>
#include <string.h>
#include "operations.h"
#include "commands.h"
#include "vectors.h"

/*
* @brief Create a new vector
* @param name - The name of the vector
* @param x - The x component of the vector
* @param y - The y component of the vector
* @param z - The z component of the vector
* @return 1 on success, 0 on failure
*/
vect new_vect(char name[50], float x, float y, float z) {
    vect temp;
    strncpy(temp.name, name, sizeof(temp.name) - 1);
    temp.name[sizeof(temp.name) - 1] = '\0';
    temp.x = x;
    temp.y = y;
    temp.z = z;
    print_vect(name, x, y, z);
    return temp;
}

/*
* @brief Check if a vector with the given name exists
* @param name - The name of the vector to check
* @param vectors - The array of vectors to search
* @return 1 if the vector exists, -1 otherwise
*/
int find_vect(vect vectors[], char name[50], int size) {
    for (int i = 0; i < size; i++) {
        if (!strcmp(name, vectors[i].name)) {
            return i;
        }
    }
    return -1;
}

/*
* @brief Add two vectors
* @param a - The first vector
* @param b - The second vector
* @return The resulting vector
*/
vect add_vect(vect a, vect b) {
    vect temp;
    temp.x = a.x + b.x;
    temp.y = a.y + b.y;
    temp.z = a.z + b.z;
    return temp;
}

/*
* @brief Subtract two vectors
* @param a - The first vector
* @param b - The second vector
* @return The resulting vector
*/
vect sub_vect(vect a, vect b) {
    vect temp;
    temp.x = a.x - b.x;
    temp.y = a.y - b.y;
    temp.z = a.z - b.z;
    return temp;
}

/*
* @brief Dot product of two vectors
* @param a - The first vector
* @param b - The second vector
* @return The dot product of the two vectors
*/
vect dot_vect(vect a, vect b) {
    vect temp;
    temp.x = a.x * b.x + a.y * b.y + a.z * b.z;
    temp.y = 0;
    temp.z = 0;
    return temp;
}

/*
* @brief Cross product of two vectors
* @param a - The first vector
* @param b - The second vector
* @return The cross product of the two vectors
*/
vect cross_vect(vect a, vect b) {
    vect temp;
    temp.x = a.y * b.z - a.z * b.y;
    temp.y = a.z * b.x - a.x * b.z;
    temp.z = a.x * b.y - a.y * b.x;
    return temp;
}

/*
* @brief Scale a vector
* @param a - The vector to scale
* @param s - The scalar value
* @return The scaled vector
*/
vect scalar_vect(vect a, float s) {
    vect temp;
    temp.x = a.x * s;
    temp.y = a.y * s;
    temp.z = a.z * s;
    return temp;
}

/*
* @brief Print the components of a vector
* @param name - The name of the vector
* @param x - The x component of the vector
* @param y - The y component of the vector
* @param z - The z component of the vector
*/
void print_vect(char name[50], float x, float y, float z) {
    printf("%s = %.2f, %.2f, %.2f\n", name, x, y, z);
}