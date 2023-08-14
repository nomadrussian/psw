/* psw.c - the main module of the personal password manager.
 * --------------------------------------------------------------------------
 * This program is designed for a personal use to make your password
 * management easier and more convenient.
 *
 * PSW Abilities:
 * 1. Generate a new password with optional strength:
 *     1.1 Preferable length is defined by a number, up to 255 symbols;
 *     1.2 -l option activates lower case English letters;
 *     1.3 -L option activates upper case English letters;
 *     1.4 -d or -D activates digits 0..9;
 *     1.5 -s activates special symbols !@#$%^&...etc;
 *     1.6 -S activates additional special symbols;
 *    In general:
 *        $ psw gen <length> <options>
 * 2. You can also generate multiple passwords at once if you want to,
 *    (e.g for a test):
 *        $ genlist <number of passwords> <length> <options>
 * 3. Save the new password under a label (e.g. a website name) using:
 *        $ psw save <label> <password>
 * 4. To recall and see you saved password, use:
 *        $ psw recall <label>
 *    It asks your confirmation to avoid random unwanted password leak.
 * 5. Show the list of your labels (in alphabetic order):
 *        $ psw lb
 *    To show the full label list including all your passwords:
 *        $ psw lb_unsafe
 *    It requires your confirmation so you understand possible consequenses.
 * 6. To rename your label type in:
 *        $ psw rename <label_old_name> <label_new_name>
 * 7. To remove the password from the list, use:
 *        $ psw remove <label>
 *    It asks your confirmation if you are really sure to do it.
 *    BE CAREFUL - the action CANNOT be undone.
 * 8. Regularly use backup system and save your backup files somewhere else
 *    to prevent accident loss of information!
 *        $ psw backup new
 *    To backup use:
 *        $ psw backup <id>
 *    To see the list of all available backups use:
 *        $ psw backup_list
 * 9. Use your own new special password to work with labels and encryption:
 *        $ psw set_password <new_password>
 *    Change the previous password:
 *        $ psw change_password <new_password>
 *    Remove your password:
 *        $ psw remove_password
 *    All commands ask your confirmation so you understand the consequences.
 *    Don't forget to firmly memorize or note down your special password!!!
 * --------------------------------------------------------------------------
 *                        |||   WARNING   |||
 * The software is completely free, use it as you want and keep it free.
 * -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errorHandler.h"
#include "generator.h"
#include "help.h"
#include "info.h"
#include "psw.h"
#include "pswUtil.h"

char *AVLBLINSTR[] = { "info", "help", "gen", "genlist" };
char *AVLBLGENFLAGS[] = { "-d", "-D", "-l", "-L", "-s", "-S" };
size_t AVLBLINSTRLEN = sizeof(AVLBLINSTR) / sizeof(AVLBLINSTR[0]);
size_t AVLBLGENFLAGSLEN = sizeof(AVLBLGENFLAGS) / sizeof(AVLBLGENFLAGS[0]);

int main(int argc, char **argv)
{   
    // Checking zero arguments case.
    if(argc == 1) {
        printBriefInfo();
        return 0;
    }

    /* Checking the key (first) argument provided by a user
     * and attempting to execute the program. */ 
    if(!strcmp(argv[1], "info")) {
        proceedInfo(argc, argv);
    } else if(!strcmp(argv[1], "help")) {
        proceedHelp(argc, argv);               
    } else if(!strcmp(argv[1], "gen")) {
        proceedGen(argc, argv);        
    } else if(!strcmp(argv[1], "genlist")) {
        proceedGenlist(argc, argv);
    } else {
        // if nonsense first argument gotten
        err_UnexpectedArg(argv, 1);
    }

    return 0;
}

// 'info' argument processing:
void proceedInfo(int argc, char **argv)
{
    if(argc > 2) {
        err_RedundantArg(argv, 2);
    }

    printInfo();
}

// 'help' argument processing:
void proceedHelp(int argc, char **argv)
{
    // printing main help information
    if(argc == 2) {
        printMainHelp();
        return;
    }

    // handling unexpected or redundant arguments
    if(!u_StringInArray(AVLBLINSTR, AVLBLINSTRLEN, argv[2])) {
        err_UnexpectedArg(argv, 2);
    }
    if(argc > 3) {
        err_RedundantArg(argv, 3);
    }

    // printing help information about specific command
    if(!strcmp(argv[2], "info")) {
        printInfoHelp();
    } else if(!strcmp(argv[2], "help")) {
        printHelpHelp();
    } else if(!strcmp(argv[2], "gen")) {
        printGenHelp();
    } else if(!strcmp(argv[2], "genlist")) {
        printGenlistHelp();
    }
}

// 'gen' argument processing:
void proceedGen(int argc, char **argv)
{
    // if the only argument is 'gen'
    if(argc == 2) {
        // default generation: all flags except extended symbols, length=12
        printf("Default automatic generation: %s\n", generatePassword(0x0F0C, 0));
        return;
    }

    // custom generation
    int FLAGS = getGenFlags(argc, argv, 0);
    printf("Your password: %s\n", generatePassword(FLAGS, 0));
}

// 'genlist' argument processing:
void proceedGenlist(int argc, char **argv)
{
    // if the only argument is 'genlist'
    if(argc == 2) {
        for(int i = 0; i < 12; i++) {
            printf("#%d:\t %s\n", i, generatePassword(0x0F0C, i));
        }

        return;
    }

    // the second argument [NUMBER OF PASSWORDS] has to be a number
    if(!u_CheckIfPureUInt(argv[2])) {
        err_UnexpectedArgSpecified(
            argv, 2, "NUMBER OF PASSWORDS", "number:1..1024"
        );
    }
    
    unsigned int number_of_passwords = u_ParseUInt(argv[2]);
    
    // checking the anticipated range 1..1024
    if(number_of_passwords > 1024 || number_of_passwords < 1) {
        err_UnexpectedArgRange(argv, 2, "NUMBER OF PASSWORDS", "1..1024");
    }
    
    // default generation of password list with specified number of passwords
    if(argc == 3) {
        for(int i = 0; i < number_of_passwords; i++) {
            printf("#%d:\t %s\n", i, generatePassword(0x0F0C, i));
        }

        return;
    }

    int FLAGS = getGenFlags(argc, argv, 1);
   
    // specified generation
    for(int i = 0; i < number_of_passwords; i++) {
        printf("%d:\t %s\n", i, generatePassword(FLAGS, i));
    }
}

int getGenFlags(int argc, char **argv, int shift)
{
    int FLAGS = 0x0000;

    // the second argument has to be a number
    if(!u_CheckIfPureUInt(argv[2 + shift])) {
        err_UnexpectedArgSpecified(argv, 2 + shift, "LENGTH", "length:1..255");
    }
        
    // specifying the length
    FLAGS += u_ParseUInt(argv[2 + shift]);
        
    // checking the anticipated range 1..255
    if(FLAGS > 0x00ff || FLAGS < 0x0001) {
        err_UnexpectedArgRange(argv, 2 + shift, "LENGTH", "1..255");
    }
        
    // if only length is specified
    if(argc == 3 + shift) {
        // default generation: all flags except extended symbols
        return FLAGS + 0x0F00;
    }
     
    // check if gotten flags are correct
    char **duplicate_check = malloc(sizeof(AVLBLGENFLAGS) * sizeof(char*));
  
    for(int i = 0; i < AVLBLGENFLAGSLEN; i++) {
        duplicate_check[i] = "";
    }
       
    for(int i = 3 + shift; i <= argc - 1; i++) {
        // -d and -D collision handling 
        if(
            (!strcmp(argv[i], "-d")
            && u_StringInArray(duplicate_check, AVLBLGENFLAGSLEN, "-D"))
            ||
            (!strcmp(argv[i], "-D")
            && u_StringInArray(duplicate_check, AVLBLGENFLAGSLEN, "-d"))
        ) {
            free(duplicate_check);
            err_RedundantArg(argv, i);
        } 
        
        // check if invalid argument
        if(!u_StringInArray(AVLBLGENFLAGS, AVLBLGENFLAGSLEN, argv[i])) { 
            free(duplicate_check);
            err_UnexpectedArg(argv, i);
        }

        // check for duplicates
        if(u_StringInArray(duplicate_check, AVLBLGENFLAGSLEN, argv[i])) {
            free(duplicate_check);
            err_RedundantFlag(argv, i);
        }
        
        duplicate_check[i - 3] = argv[i];
    }
        
    free(duplicate_check);
        
    // seting flags
    u_SetBit(&FLAGS, 0xC, u_StringInArray(argv, argc, "-S"));
    u_SetBit(&FLAGS, 0xB, u_StringInArray(argv, argc, "-s"));
    u_SetBit(&FLAGS, 0xA, u_StringInArray(argv, argc, "-L"));
    u_SetBit(&FLAGS, 0x9, u_StringInArray(argv, argc, "-l"));
    u_SetBit(&FLAGS, 0x8, u_StringInArray(argv, argc, "-d")
                       || u_StringInArray(argv, argc, "-D")); 
    
    return FLAGS;
}

