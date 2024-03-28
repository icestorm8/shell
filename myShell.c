#include "myShell.h"
#include "myFunction.h"

int main()
{
    welcome();

    while (1)
    {
        getLocation();                      // printing path and cp name
        char *input = getInputFromUser();   // getting string from user
        char **arg = splitArguments(input); // spliting the string to arguments
        char *command = arg[0];             // command is the first word allways. it'll always be the first in the array

        // puts("running...");
        // cp\0<file>\0<file>\0
        // cp <file> <file>\0
        // [cp, <file>, <file> ]
        // [input,input+3,input+10]

        if (strcmp(command, "exit") == 0) // if the input entered equals "exit" - close shell
        {
            logout(input, arg); // freeing input and arg at logout (were created using malloc), command wasn't
        }

        if (strcmp(command, "echo") == 0)
        {
            echo(arg);
        }
        else if (strcmp(command, "cd") == 0)
        {
            // create cd command and edit conditions
            cd(arg);
        }
        else if (strcmp(command, "cp") == 0)
        {
            cp(arg);
        }

        else
        {
            printf("-myshell: command '%s' wasn't found\n", command);
        }

        // "restart" - clean the space that input and args took - not relavant anymore
        free(arg);
        free(input);
    }
    return 0;
}
// יש לכתוב את פונקציית הברוכים הבאים כרצונכם אבל קצת יותר ממה שמוצג מטה לדוגמא:
//                     aSPY//YASa
//              apyyyyCY//////////YCa       |
//             sY//////YSpcs  scpCY//Pp     | Welcome to myShell
//  ayp ayyyyyyySCP//Pp           syY//C    | Version 0.0.1
//  AYAsAYYYYYYYY///Ps              cY//S   |
//          pCCCCY//p          cSSps y//Y   | https://github.com/icestorm8
//          SPPPP///a          pP///AC//Y   |
//               A//A            cyP////C   | Have fun!
//               p///Ac            sC///a   |
//               P////YCpc           A//A   | Craft packets like it is your last
//        scccccp///pSP///p          p//Y   | day on earth.
//       sY/////////y  caa           S//P   |                      -- Lao-Tze
//        cayCyayP//Ya              pY/Ya   |
//         sY/PsY////YCc          aC//Yp    |
//          sc  sccaCY//PCypaapyCP//YSs     |
//                   spCPY//////YPSps       |
//                        ccaacs            |
//                                          |                             using c
void welcome()
{
    char *text[] = {
        " ██████  ██░ ██ ▓█████  ██▓     ██▓ ",
        "▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒   ",
        "░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░   ",
        "  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░  ",
        "▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒",
        "▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░",
        "░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░",
        "░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   ",
        "      ░   ░  ░  ░   ░  ░    ░  ░    ░  ░", '\0'}

    ;
    blue();
    puts("====================== welcome to =====================\n");
    reset();
    int i = 0;
    do
    {
        printf("\t%s\n", text[i++]);
    } while ((text[i]));

    blue();
    puts("==================== written in c ======================");
    puts("============ https://github.com/icestorm8 ==============\n");
    reset();
}
