/**
* @file operations.c
* @brief Implementation of vector operations
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 5
* Name: Megan Cranston
*/

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
int new_vect(char name[50], char x[50], char y[50], char z[50]) {

}

/*
* @brief Check if a vector with the given name exists
* @param name - The name of the vector to check
* @return 1 if the vector exists, 0 otherwise
*/
int vect_name(char name[50]) {
    // for (int i = 0; i < 10; i++) {
    //     if (!strcmp(name, vectors[i].name)) {
    //         // print vect
    //     }
    // }
}

/*
* @brief Add two vectors
* @param name_a - The name of the first vector
* @param name_b - The name of the second vector
* @return The resulting vector
*/
vect add_vect(vect name_a, vect name_b) {

}

/*
* @brief Subtract two vectors
* @param name_a - The name of the first vector
* @param name_b - The name of the second vector
* @return The resulting vector
*/
vect sub_vect(vect name_a, vect name_b) {

}

/*
* @brief Dot product of two vectors
* @param name_a - The name of the first vector
* @param name_b - The name of the second vector
* @return The dot product of the two vectors
*/
float dot_vect(vect name_a, vect name_b) {

}

/*
* @brief Cross product of two vectors
* @param name_a - The name of the first vector
* @param name_b - The name of the second vector
* @return The cross product of the two vectors
*/
vect cross_vect(vect name_a, vect name_b) {

}

/*
* @brief Scale a vector
* @param name - The name of the vector
* @param scalar - The scalar value
* @return The scaled vector
*/
vect scalar_vect(vect name, float scalar) {

}

/*
* @brief Set the components of an existing vector
* @param name - The name of the existing vector
* @param new_vect - The new vector components
* @return 1 on success, 0 on failure
*/
int set_vect(char name[50], vect new_vect) {

}

/*
* @brief Print the components of a vector
* @param name - The name of the vector to print
* @return 1 on success, 0 on failure
*/
int print_vect(vect name) {

}
