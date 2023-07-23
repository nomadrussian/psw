/* help.c - shows information about commands */

#include <stdio.h>

extern char *VERSION;
extern char *LAST_UPD;

void printMainHelp() {
    printf("PSW %s from %s\n", VERSION, LAST_UPD);
    printf("Usage: $ psw [INSTRUCTION] [ARGS]\n");
    printf("\nInstructions:\n");
    printf("\n  gen [LENGTH] [FLAGS]  -  generates a new random password\n");
    printf("\n  help [INSTRUCTION]  -  provides more information about specific instruction\n");
    printf("\n  info  -  prints information about PSW version and the last update\n");
    
    printf("\n");
}

void printGenHelp() {
    printf("\n  gen [LENGTH] [FLAGS]  -  generates a new random password\n");
    printf("\n  [LENGTH]  -  <number:1..255>, specifies the password\'s length\n");
    printf(  "  [FLAGS]  -  specify characters that are used in generation\n");
    printf("\n  Flags:\n");
    printf(  "    -d or -D  -  includes digits\n");
    printf(  "          -l  -  includes lowercase letters\n");
    printf(  "          -L  -  includes uppercase letters\n");
    printf(  "          -s  -  includes additional charaters !@#$%^&*()\n");
    printf(  "          -S  -  includes additional symbols \"\'+,-./:;<=>?[\\]_`{|}~ and <space>\n");
    printf("\n  gen [LENGTH]  -  specifies the length and sets default -d -l -L -s flags\n");
    printf(  "  gen  -  sets the default length=12 and default -d -l -L -s flags\n");
    
    printf("\n");
}

void printHelpHelp() {
    printf("\n  help [INSTRUCTION]  -  provides more information about specific instruction\n");
    
    printf("\n");
}

void printInfoHelp() {
    printf("\n  info  -  prints information about PSW version and the last update\n");
    
    printf("\n");
}
