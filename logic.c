/**
* @file logic.c
* @brief logic handling for main program
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 7
* Name: Megan Cranston
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"
#include "vectors.h"
#include "fileio.h"
#include "operations.h"
#include "commands.h"

/*
* @brief replace commas with spaces, parse input into array
* @param str - Input string to parse
* @param index - Output array of parsed input
*/
void parse_input(char *str, char index[6][50]) {
    // turn commas into spaces
    for (char *p = str; *p; p++) {
        if (*p == ',') *p = ' ';
    }
    // clear array and scan in new info
    memset(index, '\0', 6*50);
    sscanf(str, "%s %s %s %s %s %s", index[0], index[1], index[2], index[3], index[4], index[5]);
}

/*
* @brief determine if a command was entered, and execute
* @param index0 - First input index, possibly containing command
* @param index1 - Second input index, possibly containing filename
* @param vector - Dynamically allocated vect array
* @param count - Number of vectors stored
* @param CAP - Max capacity of vector storage before reallocation
* @return 0 no command, 1 successful command, 2 quit command
*/
int determine_command(char index0[50], char index1[50], vect **vector, int *count, int *CAP) {
    if (!strcmp(index0, "quit")) {
        return 2;
    } else if (!strcmp(index0, "help")) {
        help();
    } else if (!strcmp(index0, "clear")) {
        clear(*vector, count, CAP);
    } else if (!strcmp(index0, "list")) {
        list(*vector, *count);
    } else if (!strcmp(index0, "load")) {
        load(index1, vector, count, CAP);
    } else if (!strcmp(index0, "save")) {
        save(index1, *vector, count);
    } else {
        return 0; // no command, continue to rest of loop
    }
    return 1;
}

/*
* @brief validate the input was entered correctly
* @param index - Input from user
* @param vector - Dynamically allocated vect array
* @param count - Number of vectors stored
* @return 0 no error, 1 error
*/
int validate_input(char index[6][50], vect *vector, int count) {
    if (index[5][0] != '\0') {
        printf("Error: Extra input entered.\n");

    } else if (index[0][0] == '\0') {
        printf("Error: No input entered.\n");

    } else if (index[0][0] != '\0' && !strcmp(index[1], "=") && (index[2][0] == '\0' || index[3][0] == '\0' || index[4][0] == '\0')) {
        // Input: <vector> = (not enough nums)
        printf("Error: Invalid assignment.\n");
    
    } else if ((is_float(index[0]) || is_float(index[2])) && strcmp(index[1], "*") != 0 && strcmp(index[1], "=") != 0) {
        printf("Error: Invalid command.\n");
    
    } else if (!strcmp(index[1], "=") && ((!is_float(index[2]) && find_vect(vector, index[2], count) == -1) || (!is_float(index[4]) && find_vect(vector, index[4], count) == -1))) {
        printf("Error: Vector not found.\n");
    
    } else {
        return 0; // no errors
    }
    return 1; // error found
}

/*
* @brief Determine the mathmatical operation 
* @param index - Input from user
* @param vector - Dynamically allocated vect array
* @param count - Number of vectors stored
* @param CAP - Max capacity of vector storage before reallocation
* @return 0 no error, 1 error
*/
int determine_operation(char index[6][50], vect *vector, int *count, int *CAP) {
    int error = 0;
    int found_vect = find_vect(vector, index[0], *count);    

    if (index[1][0] == '\0') {
        // format: <vector>
        if (found_vect != -1) {
            print_vect(vector[found_vect].name, vector[found_vect].x, vector[found_vect].y, vector[found_vect].z);
        } else {
            printf("Error: Vector not found.\n");
            return 1;
        }
    } else if (!strcmp(index[1], "=")){
        if (is_float(index[2]) && is_float(index[3]) && is_float(index[4])) {
            // format: <vector> = num, num, num
            if (found_vect != -1) { 
                vector[found_vect] = new_vect(index[0], atof(index[2]), atof(index[3]), atof(index[4]));
            } else { 
                error = create_space(&vector, count, CAP); 
                vector[(*count)++] = new_vect(index[0], atof(index[2]), atof(index[3]), atof(index[4]));
            }
        } else if (index[3][0] != '\0') { 
            // format: <vector> = <vector> op <vector>
            vect temp = perform_operation(index[2], index[3], index[4], vector, *count);
            
            // operation failed
            if (temp.name == NULL && temp.x == 0 && temp.y == 0 && temp.z == 0) {
                printf("Error: Invalid operation.\n");
                return 1;
            }
            // operation succeded, assign new values
            if (found_vect != -1) {
                vector[found_vect] = new_vect(index[0], temp.x, temp.y, temp.z);
            } else {
                error = create_space(&vector, count, CAP); 
                vector[(*count)++] = new_vect(index[0], temp.x, temp.y, temp.z);
            }
        }
           
    } else if (index[1][0] != '\0') {
        // format: <vector> opp <vector>
        vect temp = perform_operation(index[0], index[1], index[2], vector, *count);

        // operation failed
        if (temp.name == NULL && temp.x == 0 && temp.y == 0 && temp.z == 0) {
            printf("Error: Invalid operation.\n");
            return 1;
        }
        // operation succeded, print new values
        char name[50] = "ans";
        print_vect(name, temp.x, temp.y, temp.z);

    } else {
        printf("Error: Invalid command.\n");
        return 1;
    }        
    return error;
}

/*
* @brief Reallocate the vector array, add 5 indexes 
* @param vector - Dynamically allocated vect array
* @param count - Number of vectors stored
* @param CAP - Max capacity of vector storage before reallocation
* @return 0 no error, 1 error
*/
int create_space(vect **vector, int *count, int *CAP) {
    // if vector array is full, add 5 slots
    if (*count == *CAP) {
        *CAP += 5;
        vect *temp = realloc(*vector, (*CAP)*sizeof(vect));
        if (!temp) {
            printf("Error: Reallocation failed\n");
            free(*vector);
            return 1;
        }
        *vector = temp;
    }
    
    return 0;
}


/*
* @brief Perform the specified operation
* @param A - The index of the first operand
* @param op - The operation to perform
* @param B - The index of the second operand
* @oaram vector - The vector array
* @param count - The number of vector stored
* @return vect - The result of the operation
*/
vect perform_operation(char A[50], char op[50], char B[50], vect *vector, int count) {
    // search for operand vector
    int index_a = find_vect(vector, A, count);
    int index_b = find_vect(vector, B, count);
    if (index_a != -1 && index_b == -1) {       
        // <vector> = <vector> * <scalar>
        return scalar_vect(vector[index_a], atof(B));
    } else if (index_a == -1 && index_b != -1) { 
        // <vector> = <scalar> * <vector>
        return scalar_vect(vector[index_b], atof(A));
    } else {               
        // <vector> = <vector> op <vector>
        if (!strcmp(op, "+")) {
            return add_vect(vector[index_a], vector[index_b]);
        } else if (!strcmp(op, "-")) {
            return sub_vect(vector[index_a], vector[index_b]);
        } else if (!strcmp(op, ".")) {
            return dot_vect(vector[index_a], vector[index_b]);
        } else if (!strcmp(op, "*")) {
            return cross_vect(vector[index_a], vector[index_b]);
        }
    }
    // invalid operation
    return new_vect(NULL, 0, 0, 0);
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