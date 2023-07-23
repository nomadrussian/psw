/* psw.c - the main module of the personal password manager.
 * ----------------------------------------------------------------------
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
 *     1.7 In general: $ psw genl <label> <length> <options>;
 * 2. Save the new password under a label (e.g. a website name), so
 *    you can recall it if you need. E.g. $ psw recall <label>;
 * 3. If a label is not needed (e.g for a test, or just for generation),
 *    then just $ gen <length> <options> <number_of_passwords>;
 *    if <num_of_passwords> is not gotten, then it generates just one;
 * 4. Show the list of your labels in alphabetic order: $psw lb;
 *    to list it including your passwords: $ psw lb_unsafe;
 * 5. To remove the password from the list, use $ psw rm <label>, it asks
 *    confirmation; BE CAREFUL - the action cannot be undone.
 * ----------------------------------------------------------------------
 *                        |||   WARNING   |||
 * The software is completely free, use it as you want and keep it free.
 * ------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generator.h"
#include "help.h"
#include "info.h"
#include "psw.h"
#include "pswUtil.h"

char *AVLBLINSTR[] = { "gen", "info", "help" };
char *AVLBLGENINSTR[] = { "-d", "-D", "-l", "-L", "-s", "-S" };
size_t AVLBLINSTRLEN = sizeof(AVLBLINSTR) / sizeof(AVLBLINSTR[0]);
size_t AVLBLGENINSTRLEN = sizeof(AVLBLGENINSTR) / sizeof(AVLBLGENINSTR[0]);

int main(int argc, char **argv) {
    
    int ERR_ARGID;
    
    // Checking zero arguments case.
    if(argc == 1) {
        printBriefInfo();
        return 0;
    }

    /* Checking the key (first) argument provided by a user
     * and attempting to execute the program. */
    
    // 'info' argument processing:
    if(!strcmp(argv[1], "info")) {
        
        if(argc > 2) {
            ERR_ARGID = 2;
            goto LERR_REDUNDANT_ARGS;
        }
        
        printInfo();
        
    // 'help' argument processing:
    } else if(!strcmp(argv[1], "help")) {
        
        if(argc == 2) {
            printMainHelp();
        } else {
            // handling unexpected or redundant arguments
            if(!u_StringInArray(AVLBLINSTR, AVLBLINSTRLEN, argv[2])) {
                ERR_ARGID = 2;
                goto LERR_UNEXPECTED_ARGS;
            }
            if(argc > 3) {
                ERR_ARGID = 3;
                goto LERR_REDUNDANT_ARGS;
            }
            // printing help information
            if(!strcmp(argv[2], "gen")) {
                printGenHelp();
            } else if(!strcmp(argv[2], "help")) {
                printHelpHelp();
            } else if(!strcmp(argv[2], "info")) {
                printInfoHelp();
            }
        }
        
    // 'gen' argument processing:
    } else if(!strcmp(argv[1], "gen")) {
        
        unsigned int FLAGS = 0x0000;

        // if the only argument is 'gen'
        if(argc == 2) {
            // default generation: all flags except extended symbols, length=12
            FLAGS = 0x0F0C;
            printf("Default automatic generation: %s\n", 
                    generatePassword(FLAGS));
            return 0;
        }
        
        // the second argument has to be a number
        if(!u_CheckIfPureUInt(argv[2])) {
            ERR_ARGID = 2;
            goto LERR_UNEXPECTED_ARGS_NUMBER;
        }
        
        // specifying the length
        FLAGS += u_ParseUInt(argv[2]);
        
        // checking the anticipated range 1..255
        if(FLAGS > 0x00ff || FLAGS < 0x0001) {
            ERR_ARGID = 2;
            goto LERR_UNEXPECTED_ARGS_NUMBER_SIZE;
        }
        
        // if only length is specified
        if(argc == 3) {
            // default generation: all flags except extended symbols
            FLAGS += 0x0F00;
            printf("Your password: %s\n", generatePassword(FLAGS));
            return 0;
        }
        
        // check if gotten flags are correct
        char **duplicate_check = malloc(sizeof(AVLBLGENINSTR) * sizeof(char*));
        
        for(int i = 0; i < AVLBLGENINSTRLEN; i++) {
            duplicate_check[i] = "";
        }
        
        for(int i = 3; i <= argc - 1; i++) {
            // -d and -D collision handling
            if((!strcmp(argv[i], "-d") 
            && u_StringInArray(duplicate_check, AVLBLGENINSTRLEN, "-D"))
            || (!strcmp(argv[i], "-D")
            && u_StringInArray(duplicate_check, AVLBLGENINSTRLEN, "-d"))) {
                ERR_ARGID = i;
                goto LERR_REDUNDANT_ARGS;
            }
            
            // check if invalid argument
            if(!u_StringInArray(AVLBLGENINSTR, AVLBLGENINSTRLEN, argv[i])) {
                ERR_ARGID = i;
                goto LERR_UNEXPECTED_ARGS;
            }
           
            // check for duplicates
            if(u_StringInArray(duplicate_check, AVLBLGENINSTRLEN, argv[i])) {
                ERR_ARGID = i;
                goto LERR_REDUNDANT_FLAGS;
            }
            
            duplicate_check[i - 3] = argv[i];
        }
        
        free(duplicate_check);
        
        // set flags
        if(u_StringInArray(argv, argc, "-d") 
        || u_StringInArray(argv, argc, "-D")) {
            u_SetBit(&FLAGS, 0x8, 1);
        }
        if(u_StringInArray(argv, argc, "-l")) {
            u_SetBit(&FLAGS, 0x9, 1);
        }
        if(u_StringInArray(argv, argc, "-L")) {
            u_SetBit(&FLAGS, 0xA, 1);
        }
        if(u_StringInArray(argv, argc, "-s")) {
            u_SetBit(&FLAGS, 0xB, 1);
        }
        if(u_StringInArray(argv, argc, "-S")) {
            u_SetBit(&FLAGS, 0xC, 1);
        }
        
        // custom generation
        printf("Your password: %s\n", generatePassword(FLAGS));
        
    // wrong first argument error handling:
    } else {
        ERR_ARGID = 1;
        goto LERR_UNEXPECTED_ARGS;
    }

    return 0;

// ERROR HANDLING
LERR_UNEXPECTED_ARGS:
    printf("PASSWORD GENERATOR ERROR: UNEXPECTED ARGUMENT \'%s\' [id:%d]\n"
           "USE 'help' TO GET MORE INFORMATION ABOUT AVAILABLE "
           "ARGUMENT OPTIONS.\n", argv[ERR_ARGID], ERR_ARGID);
    return 1;
LERR_UNEXPECTED_ARGS_NUMBER:
    printf("PASSWORD GENERATOR ERROR: UNEXPECTED ARGUMENT \'%s\' [id:%d]\n"
           "ANTICIPATED <length:1..255>\n"
           "USE 'help' TO GET MORE INFORMATION ABOUT AVAILABLE "
           "ARGUMENT OPTIONS.\n", argv[ERR_ARGID], ERR_ARGID);
    return 1;
LERR_UNEXPECTED_ARGS_NUMBER_SIZE:
    printf("PASSWORD GENERATOR ERROR: UNEXPECTED LENGTH SIZE \'%s\' [id:%d]\n"
           "ANTICIPATED RANGE: <1..255>\n"
           "USE 'help' TO GET MORE INFORMATION ABOUT AVAILABLE "
           "ARGUMENT OPTIONS.\n", argv[ERR_ARGID], ERR_ARGID);
    return 1;
LERR_REDUNDANT_ARGS:
    printf("PASSWORD GENERATOR ERROR: REDUNDANT ARGUMENT(S) \'%s...\' [id:%d]\n"
           "USE 'help' TO GET MORE INFORMATION.\n", argv[ERR_ARGID], ERR_ARGID);
    return 1;
LERR_REDUNDANT_FLAGS:
    printf("PASSWORD GENERATOR ERROR: REDUNDANT FLAG(S) \'%s...\' [id:%d]\n"
           "USE 'help' TO GET MORE INFORMATION.\n", argv[ERR_ARGID], ERR_ARGID);
    return 1;
}
