/* info.c - prints general information about the program. */

#include <stdio.h>

#include "info.h"

extern char *VERSION;
extern char *LAST_UPD;

const char *LAST_UPD_INFO =
    "1) Implemented 'genlist' command:\n"
    "       $ psw genlist [NUMBER OF PASSWORDS] ['gen' ARGS].\n"
    "2) Big refactoring.\n"
    "3) Improved coding style to make it much more clear.\n";

// Prints general information about the program.
void printInfo()
{
	printf(
        "Personal Password Generator and Manager.\n"
	    "Version: %s\n"
	    "Last update: %s\n"
	    "\nThis program is designed for a "
	    "personal use to make your\npassword "
	    "management easier and more convenient.\n"
	    "\t1. Generate a new password with"
	    "\tchosen strength.\n"
	    "\t2. You can save your new password under a label!\n"
        "\t3. STRONG and SAFE encryption!\n"
	    "\t4. Or use it just for password generation without saving.\n"
	    "\t5. Manage your list!\n"
	    "\t6. It's completely FREE and open-source!\n"
	    "Use 'help' for more information.\n",
        VERSION, LAST_UPD
    );

    printf("\nLast update details:\n%s", LAST_UPD_INFO);
    printf("\nSource: https://github.com/nomadrussian/PSW/\n");
}

// Prints brief information.
void printBriefInfo()
{
	printf(
        "Personal Password Generator and Manager.\n"
	    "Version: %s\n"
	    "Last update: %s\n"
	    "Use info/help for more information.\n", VERSION, LAST_UPD
    );
}

