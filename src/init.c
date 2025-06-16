#include "cli.h"
#include "psw.h"

/* The entry point */
int main()
{  
    int fine_master_password = check_authentification_data();

    CLI_run(fine_master_password);

    return 0;
}

