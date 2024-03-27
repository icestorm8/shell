#include "myFunction.h"

char *getInputFromUser()
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char)); // get more space dynamically
    while ((ch = getchar()) != '\n') // until enter - scan another char
    {
        *(str + index) = ch; // save in address (start+char number/count)
        size++; 
        index++;
        str = (char *)realloc(str, size * sizeof(char)); // ask for more space for existing allocated space - increase by 1;
    }
    *(str + index) = '\0'; // if enter was pressed - end of string - add '\0' to symbolize end of string

    return str; // return user's input
}

char **splitArguments(char* str){
    // str is at first the pointer to the beggining of the string (first letter)
    // as long as we didn't get to the end of the string
    int size = 1;
    char** substrings = (char**)malloc(size*sizeof(char*));
    // char* startP = str; // SAVE POINTER
    substrings[0] = str; // SAVE START ADDRESS OF FIRST WORD(STRING)
    size++;
    while(*str){
        if(*str == ' '){ // IF SPACE WAS FOUND
        *str = '\0'; // REPLACE CURRENT CHAR WITH NULL POINTER
        str++; // MOVE TO NEXT CHAR
        substrings = (char**) realloc(substrings, (size)*sizeof(char*));
       
        substrings[size-1] = str;
        size++;
        // INCREASE SIZE OF SUBSTRING ARRAY
        // INSERT STARTP ADDRES INTO ARRAY OF SUBSTRINGS
        }
        else{
            str++;
        }
    }
    
    substrings =(char**) realloc(substrings, size*sizeof(char*));
   
    // printf("size: %d", size);
    // IF STRING WAS ENDED (/0) - ADD NULL TO THE END OF THE SUBSTRING ARRAY (INCREASE THAN ADD)
    substrings[size-1] = NULL;

    // check
    // for (int i = 0; i < size; i++)
    // {
    //     printf("\n%d: %s\n", i,substrings[i]);
       
    //     // puts(a);
        
    //     /* code */
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
        printf("%s@%s",getenv("USER"),cpName); // read that i shouldn't use environment variables here, but for now
        reset();
        printf(":");
        blue();
        printf("%s", location);
        reset();
        printf("$ ");
        boldOff();
    }
}

void logout(char *input)
{
    free(input); // free cells in which input was saved - do i need to free the arg array too if it contains pointers to input?
    puts("log out"); // print log out message
    exit(EXIT_SUCCESS); // breaking will exit the while which the return follows it EXIT_SUCCESS = 0
}

void echo(char **arg){
    // gets the arguments entered in the terminal and prints them
    
    while(*(++arg)!= NULL){
        // as long as next arg (starting with next cause first is echo(?) is not null - print it)
        printf("%s ", *arg);
    }
    puts(""); // new line at the end of print
}



// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות