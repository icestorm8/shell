#include "myFunction.h"
#include <dirent.h>

char *getInputFromUser()
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char)); // get more space dynamically
    while ((ch = getchar()) != '\n')                 // until enter - scan another char
    {
        *(str + index) = ch; // save in address (start+char number/count)
        size++;
        index++;
        str = (char *)realloc(str, size * sizeof(char)); // ask for more space for existing allocated space - increase by 1;
    }
    *(str + index) = '\0'; // if enter was pressed - end of string - add '\0' to symbolize end of string

    return str; // return user's input
}

char **splitArguments(char *str)
{
    if (strlen(str) == 0 || str == NULL)
    {
        return NULL;
    }
    // str is at first the pointer to the beggining of the string (first letter)
    // as long as we didn't get to the end of the string
    int size = 1;
    char **substrings = (char **)malloc(size * sizeof(char *));
    if (substrings == NULL)
    {
        puts("something went wrong");
        return NULL;
    }
    // char* startP = str; // SAVE POINTER
    // substrings[0] = str; // SAVE START ADDRESS OF FIRST WORD(STRING)
    // size++;
    char **temp;
    while (*str)
    {
        if (*str == ' ')
        {                // IF SPACE WAS FOUND
            *str = '\0'; // REPLACE CURRENT CHAR WITH NULL POINTER
            str++;       // MOVE TO NEXT CHAR

            while (*str == ' ')
            {
                str++;
            }
            // if (*str != ' ')
            if (*str != '\0')
            {

                temp = (char **)realloc(substrings, (size) * sizeof(char *));
                if (temp == NULL)
                {
                    puts("something went wrong");
                    free(substrings);
                    return NULL;
                }
                else
                {
                    substrings = temp;
                }
                substrings[size - 1] = str;
                size++;
            }
        }
        else
        {
            if (size == 1)
            {
                substrings[0] = str; // SAVE START ADDRESS OF FIRST WORD(STRING)
                size++;
            }
            str++;
        }
    }

    temp = (char **)realloc(substrings, size * sizeof(char *));
    if (temp == NULL)
    {
        puts("something went wrong");
        free(substrings);
        return NULL;
    }
    else
    {
        substrings = temp;
    }
    // IF STRING WAS ENDED (/0) - ADD NULL TO THE END OF THE SUBSTRING ARRAY (INCREASE THAN ADD)
    substrings[size - 1] = NULL;

    // for (int i = 0; i < size; i++)
    // {
    //     printf("\n%d: '%s'\n", i, substrings[i]);
    // }

    return substrings;
}

void getLocation()
{
    // add user too before @
    char location[BUFF_SIZE];
    char cpName[BUFF_SIZE];

    gethostname(cpName, BUFF_SIZE);

    if (getcwd(location, BUFF_SIZE) == NULL)
    {
        puts("Error");
    }
    else
    {
        bold();
        green();
        printf("%s@%s", getenv("USER"), cpName); // read that i shouldn't use environment variables here, but for now
        reset();
        printf(":");
        blue();
        printf("%s", location);
        reset();
        printf("$ ");
        boldOff();
    }
}

void logout(char *input, char **arg)
{
    free(input); // free cells in which input was saved - do i need to free the arg array too if it contains pointers to input?
    free(arg);
    puts("logged out"); // print log out message
    exit(EXIT_SUCCESS); // breaking will exit the while which the return follows it EXIT_SUCCESS = 0
}

void echo(char **arg)
{
    // gets the arguments entered in the terminal and prints them

    while (*(++arg) != NULL)
    {
        // as long as next arg (starting with next cause first is echo(?) is not null - print it)
        printf("%s ", *arg);
    }
    puts(""); // new line at the end of print
}

// cheks paths, gets an array of arguments (char**), the amount of paths we expect to find and the function name that called it
char **checkPath(char **arg, int expectedPaths, const char *funcName)
{

    char **paths = calloc(expectedPaths + 1, sizeof(char *)); // trying to change so it will fit more methods - one for null
    if (arg[1] == NULL)
    {
        paths[0] = arg[0];
        return paths; // in case got one word and it's not a command
    }
    int currentPath = 0; // start with first path

    // starts with " - look for arg that ends with "
    // input =  cd "OneDrive - Ariel University"\0
    // [cd, "OneDrive, - , Ariel, University", NULL]
    int hasClosingQuotation = 0; // false till true
    int index = 1;               // this chekes without the first cell - since its a command mostly. so when passing only a path itll fail

    while (currentPath < expectedPaths && arg[index] != NULL)
    {
        hasClosingQuotation = 0;
        if (strncmp(arg[index], "\"", 1) == 0)
        {
            // has starting quote - check for closing quote
            int opener = index;
            int closer = -1;
            // check if three is a closing double quote - start with second arg since first could be only "
            while (arg[index] != NULL)
            {
                // check length of current word
                // check if the end is " (even for the second arg(the first word after command))

                int length = strlen(arg[index]);
                char lastChar = arg[index][length - 1]; // of each word

                if (lastChar == '\"')
                {
                    hasClosingQuotation = 1; // was found
                    closer = index;
                    break; // want to find one - the first closer
                }
                index++;
            }

            if (!hasClosingQuotation)
            {
                printf("-myShell: %s: closing double quote wasn't found, invalid arguments\n", funcName);

                free(paths);
                return NULL;
            }
            else
            {

                int totalLength = 1; // for null terminator at end of string!
                for (int i = opener; i <= closer; i++)
                {
                    totalLength += strlen(arg[i]) + 1; // save space for word and space (Estimated space)
                }

                char *path = (char *)malloc(totalLength * sizeof(char));
                path[0] = '\0'; // init string path
                for (int i = opener; i <= closer; i++)
                {
                    strcat(path, arg[i]);

                    if (i < index)
                    {
                        strcat(path, " ");
                    }
                }
                // "|hi threr my name is|"
                memmove(path, path + 1, strlen(path) - 2); // remove double quotes cause it sees that as part of the path (changing start and end of string)
                path[strlen(path) - 2] = '\0';

                paths[currentPath] = path;
            }

            // return path;
        }
        else
        {

            paths[currentPath] = arg[index];
        }
        currentPath++;
        index++;
    }

    if (arg[index] != NULL)
    {
        printf("-myShell: %s: too many arguments\n", funcName);
    }
    else if (currentPath < expectedPaths)
    {
        printf("-myShell: %s: missing arguments\n", funcName);
    }
    else
    {
        return paths;
    }
    free(paths);
    return NULL;
}

void cd(char **arg)
{
    char **paths = checkPath(arg, 1, "cd");
    if (paths != NULL)
    {

        if (chdir(paths[0]) != 0)
        {
            printf("-myShell: cd: %s: No such file or directory\n", paths[0]);
        }
        // free(paths[0]);
        free(paths);
        return;
    }
    return;
}

void cp(char **arg)
{
    char ch;
    FILE *src, *des;
    char **paths = checkPath(arg, 2, "cp");
    if (paths != NULL)
    { // AKA EXACT AMOUNT OF PATHS/ARGS
        // both has
        // none has - only 2 args, next is null, no " in any (otherwise - too many args)
        // one of them has (legally or not)
        // - first has opening but not closing - return "too many args"
        // - incase first has both, and second doesn't - return "too many args"
        if ((src = fopen(paths[0], "r")) == NULL)
        {
            puts("-myShell: cp: Erorr - can't read src file");
            return;
        }
        if ((des = fopen(paths[1], "w")) == NULL)
        {
            puts("-myShell: cp: Erorr - can't write to dest file ");
            fclose(src);
            return;
        }

        while ((ch = fgetc(src)) != EOF)
        {
            fputc(ch, des);
        }
        puts("-myShell: cp: copied");
        fclose(src);
        fclose(des);
        free(paths);
    }
    else
    {
        return;
    }
}

void delete(char **arg)
{
    char **paths = checkPath(arg, 1, "delete");
    if (paths != NULL)
    {
        if (unlink(paths[0]) != 0)
            printf("-myShell: delete: %s: No such file or directory\n", paths[0]);
        else
        {
            puts("file deleted successfuly");
        }
    }
    else
    {
        return;
    }
}

void move(char **arg)
{
    char **paths = checkPath(arg, 2, "move");
    if (paths != NULL)
    {

        char *src = paths[0];  // name of file (like file.txt)
        char *dest = paths[1]; // path to move file to
        // i need to extract the file name to add to the destenation path

        // check if there isn't already a file name at the end of the dir path (in case of renaming the file)
        int isDir = 1;
        DIR *dir;
        dir = opendir(dest);
        if (dir == NULL)
        {
            isDir = 0;
        }
        else
        {
            closedir(dir); // close dir
        }

        if (!isDir)
        {
            if (rename(src, dest) != 0)
                puts("-myShell: move: No such file or directory");
            else
            {
                printf("file moved from %s to %s successfuly\n", src, dest);
            }
            return;
        }
        char *fileName = strrchr(src, '/'); // find last slash before file name if there is one

        if (fileName == NULL)
        {
            fileName = src;
        }
        else
        {
            fileName++; // POINTER IS OG TO LAST SLASH INDEX AND NOT TO START OF FILENAME
        }

        // find buffer size
        int destLength = strlen(dest);
        int fileNameLength = strlen(fileName);
        int bufferSize = fileNameLength + 1 + destLength + 1; // 2 added for slash between path and file and /0
        char *newDest = (char *)calloc(bufferSize, sizeof(char));
        if (newDest == NULL)
        {
            // CALLOC DIDN'T WORK
            puts("something went wrong");
            return;
        }
        sprintf(newDest, "%s/%s", dest, fileName);
        // add filename to end of dest (so, src and dest with filename at the end)
        // find last "/" in file name (if there is any)
        // add the name of the file to the end of the dest dir
        // puts(src);
        // puts(dest);
        // puts(newDest);
        if (rename(src, newDest) != 0)
            puts("-myShell: move: No such file or directory");
        else
        {
            printf("file moved from %s to %s successfuly\n", src, dest);
        }
        free(newDest);
    }
    else
    {
        return;
    }
}

int getToken(char **arg, const char *token)
{ // token is a string - could be |, >, >>
    int tokenIndex = 0;
    while (arg[tokenIndex] != NULL)
    {
        if (strcmp(arg[tokenIndex], token) == 0)
        {
            return tokenIndex;
        }
        tokenIndex++;
    }
    // for(int i = 0; i< sizeof)
    return -1;
}

// check this one! something get stuch when cd .. | cd shell (should say " cd: shell: No such file or directory" like in bash?)
void mypipe(char **argv1, char **argv2)
{
    int fildes[2];

    if (fork() == 0)
    {
        pipe(fildes);
        if (fork() == 0)
        {
            /* first component of command line */
            close(STDOUT_FILENO);
            dup(fildes[1]);
            close(fildes[1]);
            close(fildes[0]);
            /* stdout now goes to pipe */
            /* child process does command */

            execvp(argv1[0], argv1);
        }
        /* 2nd command component of command line */
        close(STDIN_FILENO);
        dup(fildes[0]);
        close(fildes[0]);
        close(fildes[1]);
        /* standard input now comes from pipe */
        puts(argv2[0]);
        execvp(argv2[0], argv2);
    }
}

void echoppend(char **argv1, char **argv2)
{
    // [echo, hi , there, >> , path] // check that path is one arg, if not existing (file doesn't open - create new file)
    // echo up to the >> and save to file

    // this should get a path to file  (as filename)
    // should also get the result of an echo command
    if (argv2[0] == NULL) // checking if there is a file name after the pending >>
    {
        puts("-myShell: echorite: missing arguments (no file name)");
        return;
    }
    char **filename = checkPath(argv2, 1, "echoppend"); // when passing this - it has no command so the function had to be changed to return a word if the arg array contain only one

    if (filename == NULL)
    {
        return;
    }

    FILE *file = freopen(filename[0], "a+", stdout); // append - exists - addes to it, doesn't - creates new file
    if (file == NULL)
    {
        puts("Error opening file");
        free(filename);
        return;
    }

    // Call the echo function with the provided arguments
    echo(argv1);

    // Close the redirected output
    fclose(stdout);
    fclose(file);
    // stdout = fdopen(1, "w");
    freopen("/dev/tty", "w", stdout); // back to default (/*for gcc, ubuntu*/ )
    printf("Output written to file.txt\n");
    free(filename);
}

void echorite(char **argv1, char **argv2)
{

    if (argv2[0] == NULL)
    {
        puts("-myShell: echorite: missing arguments (no file name)");
        return;
    }
    char **filename = checkPath(argv2, 1, "echowrite");
    if (filename == NULL)
    {
        return;
    }

    FILE *file = freopen(filename[0], "w", stdout); // write - exists - addes to it, doesn't - creates new file
    if (file == NULL)
    {
        puts("Error opening file");
        free(filename);
        return;
    }
    // fflush(stdout);
    // Call the echo function with the provided arguments
    echo(argv1);

    // Close the redirected output
    fclose(stdout);
    fclose(file);
    // stdout = fdopen(1, "w");
    freopen("/dev/tty", "w", stdout); // back to default (/*for gcc, ubuntu*/ )
    printf("Output written to file.txt\n");
    free(filename);
}

void myRead(char **arg)
{
    if (arg[1] == NULL)
    {
        puts("-myShell: read: missing arguments");
        return;
    }
    char **filename = checkPath(arg, 1, "read"); // arg[0] - command, arg[1] - filename
    FILE *file = fopen(filename[0], "r");

    if (file == NULL)
    {
        printf("-myShell: read: could not open file '%s', file may not exist\n", filename[0]);
        free(filename);
        return;
    }

    // read one character at a time (like echo)
    // and print it to terminal
    // until getting to EOF - end of file mark
    char ch;
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);

    // close the file
    fclose(file);
    free(filename);
    return;
}

void wordCount(char **arg)
{
    if (arg[1] == NULL)
    {
        // arg[1] should be -l / -w
        puts("-myShell: wordCount: missing arguments");
        return;
    }
    char *option = arg[1];
    if (strcmp(option, "-l") != 0 && strcmp(option, "-w") != 0)
    {
        printf("-myShell: wordCount: invalid option %s\n", option);
        return;
    }
    // try to open file from path/filename
    char **filename = checkPath(arg, 2, "wordCount"); // arg[0] - command, arg[1] - filename

    if (filename[1] == NULL)
    {
        puts("-myShell: wordCount: missing arguments");
        return;
    }
    FILE *file = fopen(filename[1], "r");

    if (file == NULL)
    {
        printf("-myShell: read: could not open file '%s', file may not exist\n", filename[1]);
        free(filename);
        return;
    }
    // if it exists and there was a success opening it - count spaces and new lines
    char ch;

    // not sure how to count since its right some of the times but in other not so much
    int words = 0;
    int lines = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == ' ')
        {
            words++;
        }
        if (ch == '\n')
        {
            lines++;
            words++;
        }
    }

    if (strcmp(option, "-l") == 0)
    {
        // return count of new line
        printf("%d\n", lines);
    }
    else
    {
        // return count of new line + count of spaces
        printf("%d\n", words);
    }

    // read one character at a time (like echo)
    // and print it to terminal
    // until getting to EOF - end of file mark

    // close the file
    fclose(file);
    free(filename);
    return;
}

// for checking move
void ls(char **arg)
{
    char **paths = checkPath(arg, 1, "ls");
    if (paths == NULL)
    {
        return;
    }
    DIR *dir;
    struct dirent *entry;
    dir = opendir(paths[0]);
    if (dir == NULL)
    {
        perror("Error opening directory");
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}