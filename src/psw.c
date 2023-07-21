/* psw.c - the main module of the personal password manager.
 * ---------------------------------------------------------------------
 * This program is designed for a personal use to make your password
 * management easier and more convenient.
 *
 * PSW v.1.0 Abilities:
 * 1. Generate a new password with optional strength:
 *     1.1 Preferable length is defined by a number, up to 255 symbols;
 *     1.2 -l option activates lower case English letters;
 *     1.3 -L option activates upper case English letters;
 *     1.4 -d or -D activates digits 0..9;
 *     1.5 -s activates special symbols !@#$%^&...etc;
 *     1.6 -S activates additional special symbols;
 *     1.7 In general: $psw genl <label> <length> <options>;
 * 2. Save the new password under a label (e.g. a website name), so
 *    you can recall it if you need. E.g. $psw recall <label>;
 * 3. If a label is not needed (e.g for a test, or just for generation),
 *    then just $gen <length> <options> <number_of_passwords>;
 *    if <num_of_passwords> is not gotten, then it generates just one;
 * 4. Show the list of your labels in alphabetic order: $psw lb;
 *    to list it including your passwords: $psw lb_unsafe;
 * 5. To remove the password from the list, use $psw rm <label>, it asks
 *    confirmation; BE CAREFUL - the action cannot be undone.
 * ---------------------------------------------------------------------
 *                        |||   WARNING   |||
 * The software is completely free, use it as you want and keep it free.
 * ------------------------------------------------------------------ */

#include <stdio.h>
#include <string.h>
#include "generator.h"
#include "info.h"
#include "pswUtil.h"

int main(int argc, char **argv) {
    
    int ERR_ARGID;
    
    // Checking zero arguments case.
    if(argc == 1) {
        printRInfo();
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
    } else if (!strcmp(argv[1], "help")) {
        if(argc > 2) {
            ERR_ARGID = 2;
            goto LERR_REDUNDANT_ARGS;
        }
        printf("No help yet. In development.\n");
        //printHelp();  // implement later
        
    // 'gen' argument processing:
    } else if (!strcmp(argv[1], "gen")) {
        
        // if the only argument is 'gen', just default generation
        if(argc == 2) {
            printf("Default automatic generation: %s\n", generatePassword(0));
            return 0;
        }
        
        unsigned int FLAGS = 0x00000000;
        
        // the second argument has to be a number
        if(!u_CheckIfPureUInt(argv[2])) {
            ERR_ARGID = 2;
            goto LERR_UNEXPECTED_ARGS_NUMBER;
        }
        
        // check the anticipated range 1..255
        if(!(1 < (FLAGS += u_ParseUInt(argv[2])) < 255)) {
            ERR_ARGID = 2;
            goto LERR_UNEXPECTED_ARGS_NUMBER_SIZE;
        }
        printf("%d\n", FLAGS % 0xff);
        // set flags
        
        
        //printf("Your password: %s\n", generatePassword(FLAGS));
        
    // wrong first argument error handling:
    } else {
        ERR_ARGID = 1;
        goto LERR_UNEXPECTED_ARGS;
    }

    return 0;

    // ERROR HANDLING
LERR_UNEXPECTED_ARGS:
    printf("PASSWORD GENERATOR ERROR: UNEXPECTED ARGUMENT \'%s\'\n"
           "USE 'help' TO GET MORE INFORMATION ABOUT AVAILABLE "
           "ARGUMENT OPTIONS.\n", argv[ERR_ARGID]);
    return 1;
LERR_UNEXPECTED_ARGS_NUMBER:
    printf("PASSWORD GENERATOR ERROR: UNEXPECTED ARGUMENT \'%s\'\n"
           "ANTICIPATED <number:1..255>\n"
           "USE 'help' TO GET MORE INFORMATION ABOUT AVAILABLE "
           "ARGUMENT OPTIONS.\n", argv[ERR_ARGID]);
    return 1;
LERR_UNEXPECTED_ARGS_NUMBER_SIZE:
    printf("PASSWORD GENERATOR ERROR: UNEXPECTED LENGTH SIZE \'%s\'\n"
           "ANTICIPATED RANGE: <1..255>\n"
           "USE 'help' TO GET MORE INFORMATION ABOUT AVAILABLE "
           "ARGUMENT OPTIONS.\n", argv[ERR_ARGID]);
    return 1;
LERR_REDUNDANT_ARGS:
    printf("PASSWORD GENERATOR ERROR: REDUNDANT ARGUMENT(S) \'%s...\'\n"
           "USE 'help' TO GET MORE INFORMATION.\n", argv[ERR_ARGID]);
    return 1;
}
