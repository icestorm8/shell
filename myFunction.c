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

// maybe check for tabs and newlines as well (haven't yet)
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

            if (*str != ' ')
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

// בפונקציה הנ"ל קיבלנו את הנתיב ממנו אנחנו מריצים את התוכנית שלנו
//  עליכם לשדרג את הנראות של הנתיב כך ש-בתחילת הנתיב יופיע שם המחשב (כמו בטרמינל המקורי) בסוף יופיע הסימן דולר
//  ולאחר הדולר ניתן אפשרות למשתמש להזין מחרוזת מבלי שנרד שורה.
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

char **checkPath(char **arg, int expectedPaths, const char *funcName)
{
    char **paths = calloc(expectedPaths + 1, sizeof(char *)); // trying to change so it will fit more methods - one for null
    int currentPath = 0;                                      // start with first path

    // starts with " - look for arg that ends with "
    // input =  cd "OneDrive - Ariel University"\0
    // [cd, "OneDrive, - , Ariel, University", NULL]
    int hasClosingQuotation = 0; // false till true
    int index = 1;
    //
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
    if (arg[1] == NULL)
    {
        puts("-myShell: cd: missing arguments");
        return;
    }
    if (strncmp(arg[1], "\"", 1) != 0 && arg[2] != NULL) // wanted to not use the function if i can
    {
        // first arg doesn't start with " and there is a second arg
        puts("-myShell: cd: too many arguments");
        return;
        //     // return;
    }
    // else if (strncmp(arg[1], "\"", 1) == 0)
    // {
    else
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
        }
    }
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
        puts(src);
        puts(dest);
        puts(newDest);
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