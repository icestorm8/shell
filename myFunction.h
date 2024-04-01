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

/**
 * @brief  Reads a line of text from the user until a newline character is encountered.
 *
 * this function reads char by char from the user (terminal) entil user press enter.
 * the string is allocated dinammically as each char is added.
 *
 * @param  None.
 * @note   This function dynamically allocates memory for the input string and it is the caller's responsibility to free this memory.
 * @warning The function may cause memory leaks if the returned string is not freed properly.
 * @return A pointer to the dynamically allocated string containing the user's input, terminated with a null character.
 */
char *getInputFromUser();

/**
 * @brief Splits a string into individual words based on whitespace.
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
char **splitArguments(char *);

/**
 * @brief prints the user's cp name, host name and current path (simialer to bash's).
 *
 * using the getcwd to get the current path, getENV to get user connected and getHostName to get the computer name.
 * using color codes to print a designed string according to the design of the original bash.
 *
 * @param  None.
 * @return This function does not return a value.
 */
void getLocation();

/**
 * @brief  stops the execute of the program and frees the allocated memory the program used.
 * @param input (char*) - allocated by getInputFromUser()
 * @param arg (char**) - allocated by splitArguments(char *)
 * @note   This function must get the variables that were dinamically allocated so it can free those.
 * @warning not returning the right variables may cause memory leaks since they won't be freed properly.
 * @return This function does not return a value.
 */
void logout(char *, char **);

/**
 * @brief  prints the users input in a new line
 *
 * this function gets the argument array we made and prints the arguments string by string with spaces in the middle.
 *
 * @param arg (char**) - allocated by splitArguments(char *)
 * @return This function does not return a value.
 */
void echo(char **);

/**
 * @brief Changes the current working directory of the process to the directory specified in arg.
 * @param arg A pointer to an array of strings where the first string is expected to be the path to change to.
 * @note This function uses the checkPath function to validate the path before attempting to change the directory.
 * @warning If the path is not valid or does not exist, an error message is printed and no change in directory occurs.
 * @return This function does not return a value.
 */
void cd(char **);

/**
 * @brief Copies the contents of one file to another.
 *
 * by opening the src file to reading and the destanation file to writing and copying each char one by one to the file until reaching EOF.
 *
 *  @param arg A pointer to an array of strings where the first two strings are expected to be the source and destination file paths, respectively.
 * @note This function uses the checkPath function to validate the paths before attempting to copy the file.
 * @warning If the source file cannot be read or the destination file cannot be written, an error message is printed and the function exits without copying.
 * @return This function does not return a value.
 */
void cp(char **);

/**
 * @brief Deletes a file specified by the path in arg.
 *
 * using unlink to delete a file from a path
 * @param arg A pointer to an array of strings where the first string is expected to be the path of the file to be deleted.
 * @note This function uses the checkPath function to validate the path before attempting to delete the file.
 * @warning If the file does not exist or cannot be deleted, an error message is printed.
 * @return This function does not return a value.
 */
void delete(char **);

/**
 * @brief Moves a file from one location to another, with the option to rename it.
 *
 * in case a path to a folder was entered - without a file name at the end - the file we want to move
 * will be moved in it's original name. this was achieved by locating the last slash to find the file name incase the file was given as a path.
 * in case the path to a folder was entered with a new file name at the end, the file will be moved under the new name given to it by the user.
 *
 * @param arg A pointer to an array of strings where the first two strings are expected to be the source path and the destination path, respectively.
 * @note This function uses the checkPath function to validate the paths and determine if the destination is a directory or a new file name.
 * @warning If the source file does not exist, or the destination path is invalid, an error message is printed.
 * @return This function does not return a value.
 */
void move(char **);

/**
 * @brief Searches for a specified token within an array of strings and returns its index.
 * @param arg A pointer to an array of strings to be searched.
 * @param token The string token to search for within the array.
 * @note The function iterates through the array until a match is found or the end of the array is reached.
 * @warning If the token is not found, the function returns -1.
 * @return The index of the token within the array if found, otherwise -1.
 */
int getToken(char **, const char *);

// doesn't work currectly?
/**
 * @brief passes a command result to another command by creating a pipe between the 2 proccess.
 * @param argv1 A pointer to an array of strings until the index of the | found.
 *  @param argv2 A pointer to an array of strings one index after the | sign was found
 * @note This function must get 2 arrays that were split in the | sign in order to work. both sould start with a valid command.
 */
void mypipe(char **, char **);

/**
 * @brief Appends the output of an echo command to a file.
 *
 * incase the file doesn't exist it creates it
 * @param argv1 The argument vector containing the strings to be echoed.
 * @param argv2 The argument vector containing the file path to append the echo output.
 * @note This function checks if the file path is provided and then appends the echo output to the file.
 * @warning If no file name is provided or the file cannot be opened, an error message is printed.
 * @return This function does not return a value.
 */
void echoppend(char **, char **);

/**
 * @brief if file exists erases all its contents, else creates it - than writes the output of an echo command to a file.
 *
 * @param argv1 The argument vector containing the strings to be echoed.
 * @param argv2 The argument vector containing the file path to append the echo output.
 * @note This function checks if the file path is provided and then appends the echo output to the file.
 * @warning If no file name is provided or the file cannot be opened, an error message is printed.
 * @return This function does not return a value.
 */
void echorite(char **, char **);

/**
 * @brief Reads the contents of a file and prints it to the terminal.
 * @param arg A pointer to an array of strings where the second string is expected to be the path of the file to be read.
 * @note This function uses the checkPath function to validate the path before attempting to read the file.
 * @warning If the file path is not provided or the file cannot be opened, an error message is printed.
 * @return This function does not return a value.
 */
void myRead(char **); // /usr/include/unistd.h:371:16: note: previous declaration of ‘read’ with type ‘ssize_t(int,  void *, size_t)’ {aka ‘long int(int,  void *, long unsigned int)’}

/**
 * @brief Counts the number of words or lines in a file according to option entered.
 * @param arg A pointer to an array of strings where the second string is the option (-l or -w) and the third string is the path of the file.
 * @note This function uses the checkPath function to validate the path before attempting to count words or lines.
 * @warning If the file path is not provided, the file cannot be opened, or the option is invalid, an error message is printed.
 * @return This function does not return a value.
 */
void wordCount(char **);

// prints the content of a dir, used for check - not my code
void ls(char **);

// prints all available commands
void help();
