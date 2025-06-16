#include "cli.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "psw.h"

#define CLI_CMD_BUFF_SIZE 64

const char *greeting = "Hello, psw is active!\n";

/* A list of aliases for each command has to end with NULL
   in order to be checked correctly. */
const char *cmd_aliases_GET_ALL_ENTRIES[] = { "showall", "all", "list", NULL };
const char *cmd_aliases_AUTHORIZE[] = { "authorize", "login", NULL };
const char *cmd_aliases_HELP[] = { "help", "h", "aid", NULL };
const char *cmd_aliases_INFO[] = { "info", "i", NULL };
const char *cmd_aliases_QUIT[] = { "quit", "q", "leave", "stop", "finish", NULL };

typedef struct {
    const Command command;
    const char **cmd_aliases;
} CommandMatch;

const CommandMatch CommandMap[] = {
    { cmd_GET_ALL_ENTRIES, cmd_aliases_GET_ALL_ENTRIES },
    { cmd_AUTHORIZE, cmd_aliases_AUTHORIZE },
    { cmd_HELP, cmd_aliases_HELP },
    { cmd_INFO, cmd_aliases_INFO },
    { cmd_QUIT, cmd_aliases_QUIT }
};

void CLI_run()
{
    CLI_greet();

    Command current_command;
    while (1) {
        current_command = CLI_get_next_command();
        if (current_command == cmd_UNKNOWN_COMMAND)
        {
            printf("Unknown command.\n");
            continue;
        }

        int err_code;
        if ((err_code = do_command(current_command)) != OK)
        {
            showup_err(err_code);
        }
    }
}

void CLI_greet()
{
    printf("%s", greeting);
}

Command CLI_get_next_command()
{
    char cmd_buff[CLI_CMD_BUFF_SIZE] = { 0 };
    Command res;

    fgets(cmd_buff, CLI_CMD_BUFF_SIZE, stdin);
    res = parse_command(cmd_buff);

    return res;
}

Command parse_command(const char *buff)
{
    char str_cmd[CLI_CMD_BUFF_SIZE] = { 0 };
    const char *c_in = buff;
    char *c_out = str_cmd;
    char ch;

    while (isalpha((unsigned char) (ch = *c_in++)))
    {
        *c_out++ = ch;
    }

    for (size_t i = 0; i < sizeof(CommandMap) / sizeof(CommandMatch); i++)
    {
        const char *alias;
        for (size_t j = 0; (alias = CommandMap[i].cmd_aliases[j]); j++)
        {
            if (!strcmp(str_cmd, alias))
            {
                return CommandMap[i].command;
            }
        }
    }

    return cmd_UNKNOWN_COMMAND;
}

char *CLI_get_password()
{
    char *res = calloc(CLI_CMD_BUFF_SIZE, sizeof(char));
    
    printf("password: ");
    fgets(res, CLI_CMD_BUFF_SIZE, stdin);

    res[strlen(res) - 1] = '\0';

    return res;
}

