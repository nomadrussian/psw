/* help.c - shows information about commands */

#include <stdio.h>

#include "help.h"

extern char *VERSION;
extern char *LAST_UPD;

void printMainHelp()
{
    printf("PSW %s from %s\n", VERSION, LAST_UPD);
    printf(
        "Usage: $ psw [INSTRUCTION] [ARGS]\n"
        "\nInstructions:\n"
        "\n  info  -  prints information about PSW version and the last "
        "update\n"
        "\n  help [INSTRUCTION]  -  provides more information about "
        "specific instruction\n"
        "\n  gen [LENGTH] [FLAGS]  -  generates a new random password\n"
        "\n  genlist [NUMBER OF PASSWORDS] [\'gen\' ARGS]  -  generates a list "
        "of new\n      random passwords, able to use generation flags like "
        "\'gen\' command\n"
    );

    printf("\n");
}

void printInfoHelp()
{
    printf(
        "\n  info  -  prints information about PSW version and "
        "the last update\n"
    );
    
    printf("\n");
}

void printHelpHelp()
{
    printf(
        "\n  help [INSTRUCTION]  -  provides more information about "
        "specific instruction\n"
    );
    
    printf("\n");
}

void printGenHelp()
{
    printf(
        "\n  gen [LENGTH] [FLAGS]  -  generates a new random password\n"
        "\n  [LENGTH]  -  <number:1..255>, specifies the password\'s "
        "length\n"
        "  [FLAGS]  -  specify characters that are used in generation\n"
        "\n  Flags:\n"
        "    -d or -D  -  includes digits\n"
        "          -l  -  includes lowercase letters\n"
        "          -L  -  includes uppercase letters\n"
        "          -s  -  includes additional charaters !@#$%%^&*()\n"
        "          -S  -  includes additional symbols "
        "\"\'+,-./:;<=>?[\\]_`{|}~ and <space>\n"
        "\n  gen [LENGTH]  -  specifies the length and sets default "
        "-d -l -L -s flags\n"
        "  gen  -  sets the default length=12 and default "
        "-d -l -L -s flags\n"
    );
    
    printf("\n");
}

void printGenlistHelp() 
{
    printf(
        "\n  genlist [NUMBER OF PASSWORDS] [gen ARGS]\n"
        "\n  [NUMBER OF PASSWORDS]  -  <number:1..255>\n"
        "  [\'gen\' ARGS]  -  use the same arguments that you would use with "
        "\'gen\' command\n"
        "\n  To get more information about [\'gen\' ARGS] use "
        "\'$ psw help gen\'\n"
    );

    printf("\n");
}

