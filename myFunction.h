#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFF_SIZE 256
#define blue() printf("\033[0;34m")
#define reset() printf("\033[0m")
#define green() printf("\e[0;32m")
#define bold() printf("\e[1m")
#define boldOff() printf("\e[m")



char* getInputFromUser();
// cp file file
// [cp,file,file]
/**
 * Splits a string into individual words based on whitespace.
 * 
 * This function takes a string as input and splits it based on whitespace
 * characters (space). It dynamically allocates memory for an
 * array of strings to store the pointers to the first char in each word. The caller is responsible for freeing
 * the memory allocated for the array and its elements when it's no longer needed.
 * 
 * @param input A pointer to the string to be split.
 * 
 * @return A dynamically allocated array of strings (char**) containing the tokens.
 *         The last element of the array is NULL. Returns NULL if input is NULL
 *         or if memory allocation fails.
 * 
 * @note The input string will be modified (tokenized) by this function.
 *       Make sure to use a copy of the original string if preservation
 *       of the original string is required.
 * 
 * @warning The caller is responsible for freeing the memory allocated for
 *          the returned array and its elements using free().
 */
char** splitArguments(char*);
char *checkPath(char**);

void getLocation();

void logout(char*, char**);
void echo(char**);
void cd(char**);
void cp(char**);


// char** splitString(char*);