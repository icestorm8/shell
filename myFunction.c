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
// עליכם לממש את הפונקציה strtok כלומר שהפונקציה הנ"ל תבצע בדיוק אותו הדבר רק בלי השימוש בפונקציה strtok
char **splitArgument(char *str)
{
    // str = cp file file file
    //[cp,file,file,file,NULL]
    char *subStr;
    int size = 2;
    int index = 0;
    subStr = strtok(str, " ");
    char **argumnts = (char **)malloc(size * sizeof(char *));
    *(argumnts + index) = subStr;
    while ((subStr = strtok(NULL, " ")) != NULL)
    {
        size++;
        index++;
        *(argumnts + index) = subStr;
        argumnts = (char **)realloc(argumnts,size * sizeof(char *));
    }
    *(argumnts + (index+1)) = NULL;

    return argumnts;
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
    free(input); // free cells in which input was saved
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


char **splitString(char* str){
    // str is at first the pointer to the beggining of the string (first letter)
    // int size = 1;
    // char **splited = (char **)malloc(size * sizeof(char *));
    // int count = 0;
    // as long as we didn't get to the end of the string
    char *startP = str;
    int size = 1;
    int index = 0;
    int subCount = 1;
    char **subStrings = (char**)malloc(subCount*sizeof(char)); // if space wasn't found ill still have an array of 1 string
    char *current =(char*)malloc(size*sizeof(char));
    while(*(startP+index) != '\0'){
        // if its a space = split
        
        if(*startP == ' '){
            *startP = '\0' ;
            size++;
            *current = (char*)realloc(current, size*sizeof(char)); // increase by one
            current = startP;
            // the substring ended
            // add to char[][]
            subCount++;
            if(subCount == 1){
                // pass the something to the something
            }
            else{
                
                **subStrings = (char**)realloc(subStrings, subCount*sizeof(char));
            }
            
           

            printf("%s\n", startP + 1); // Print the substrin
        }
        else{
            if(index != 0){
                current = startP; // the idea is to pass the first char of the string to the current substring i save
            }
            else{
                // allocate space for another char in the current substring, increase size of current substring array
                size++;
               *current = (char*)realloc(current, size*sizeof(char)); // increase by one
                current = startP;
            }

        }
        startP++; // next char in string
    }
    return NULL;
}

// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות