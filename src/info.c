/* info.c - prints general information about the program. */

#include <stdio.h>
#include "psw.h"

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
}

// Prints reduced information.
void printRInfo() {
	printf("Personal Password Generator and Manager.\n"
	       "Version: %s\n"
	       "Last update: %s\n"
	       "Use info/help for more information.\n", VERSION, LAST_UPD);
}
