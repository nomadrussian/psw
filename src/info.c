/* info.c - prints general information about the program. */

#include <stdio.h>

extern char *VERSION;
extern char *LAST_UPD;



const char *LAST_UPD_INFO = "1) Imlemented 'help' command: $ psw help [INSTRUCTION]\n"
                            "2) Fixed too low -d and -s characters frequency with -l and/or -L.\n"
                            "3) Fixed -d/-D options possible collision in input.\n";

// Prints general information about the program.
void printInfo() {
	printf("Personal Password Generator and Manager.\n"
	       "Version: %s\n"
	       "Last update: %s\n"
	       "This program is designed for a "
	       "personal use to make your\npassword "
	       "management easier and more convenient.\n"
	       "\t1. Generate a new password with"
	       "\tchosen strength.\n"
	       "\t2. You can save the new password under a label!\n"
	       "\t3. Or use it just for password generation without saving.\n"
	       "\t4. Manage your list!\n"
	       "\t5. It's completely FREE and open-source!\n"
	       "Use 'help' for more information.\n", VERSION, LAST_UPD);
    printf("Last update details:\n%s", LAST_UPD_INFO);
}

// Prints reduced information.
void printBriefInfo() {
	printf("Personal Password Generator and Manager.\n"
	       "Version: %s\n"
	       "Last update: %s\n"
	       "Use info/help for more information.\n", VERSION, LAST_UPD);
}
