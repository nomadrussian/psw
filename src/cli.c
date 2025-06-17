#include "cli.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "authorization.h"
#include "psw.h"

const char *greeting = "Hello, PSW is active!";

/**
 * All the lists of aliases for each command have to end with nullptr
 * in order to be proceeded correctly.
 */
const char *cmd_aliases_GET_ALL_ENTRIES[] = { "showall", "all", "list", nullptr };
const char *cmd_aliases_AUTHORIZE[] = { "authorize", "login", nullptr };
const char *cmd_aliases_UNAUTHORIZE[] = { "unauthorize", "logout", nullptr };
const char *cmd_aliases_SET_MASTER_PASSWORD[] = { "register", "reg", "set_master_password", "setmpsw", nullptr };
const char *cmd_aliases_HELP[] = { "help", "h", "aid", nullptr };
const char *cmd_aliases_INFO[] = { "info", "i", "what", nullptr };
const char *cmd_aliases_QUIT[] = { "quit", "q", "leave", "stop", "finish", nullptr };

typedef struct {
    const Command command;
    const char **cmd_aliases;
} CommandMatch;

const CommandMatch CommandMap[] = {
    { cmd_GET_ALL_ENTRIES, cmd_aliases_GET_ALL_ENTRIES },
    { cmd_AUTHORIZE, cmd_aliases_AUTHORIZE },
    { cmd_UNAUTHORIZE, cmd_aliases_UNAUTHORIZE },
    { cmd_SET_MASTER_PASSWORD, cmd_aliases_SET_MASTER_PASSWORD },
    { cmd_HELP, cmd_aliases_HELP },
    { cmd_INFO, cmd_aliases_INFO },
    { cmd_QUIT, cmd_aliases_QUIT }
};

void CLI_run(int authentification_data_status)
{
    if (authentification_data_status == err_CORRUPTED_AUTHENTIFICATION_DATA)
    {
        showup_err(authentification_data_status);
    }

    CLI_greet(); 

    Command current_command;
    while (1)
    {
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
            if(authorized && current_command == cmd_SET_MASTER_PASSWORD && err_code == SUCCESS)
            {
                force_log_out();
                CLI_showup_msg(msg_LOGGED_OUT);
            }
        }
    }
}

void CLI_greet()
{
    CLI_showup_msg(greeting);
}

void CLI_showup_msg(const char *msg)
{
    printf("%s\n", msg);
}

Command CLI_get_next_command()
{
    char cmd_buff[CLI_BUFFER_SIZE] = { 0 };
    Command res;

    printf("(psw) ");

    fgets(cmd_buff, CLI_BUFFER_SIZE, stdin);
    res = parse_command(cmd_buff);

    return res;
}

Command parse_command(const char *buff)
{
    if (buff == nullptr)
    {
        return cmd_UNKNOWN_COMMAND;
    }

    char str_cmd[CLI_BUFFER_SIZE] = { 0 };
    const char *c_in = buff;
    char *c_out = str_cmd;
    char ch;

    while (isalpha((unsigned char) (ch = *c_in++)) || isdigit(ch) || ch == '_')
    {
        *c_out++ = ch;
    }

    for (size_t i = 0; i < sizeof(CommandMap) / sizeof(CommandMatch); i++)
    {
        const char *alias;
        for (size_t j = 0; (alias = CommandMap[i].cmd_aliases[j]) != nullptr; j++)
        {
            if (!strcmp(str_cmd, alias))
            {
                return CommandMap[i].command;
            }
        }
    }

    return cmd_UNKNOWN_COMMAND;
}

/**
 * Parameter size is the actual allocation size, not length like in strlen.
 * It's needed for safe memory clearing. 
 */
char *CLI_get_password(size_t *size)
{
    if (size == nullptr)
    {
        return nullptr;
    }

    char *res = calloc(CLI_BUFFER_SIZE, sizeof(char));

    *size = CLI_BUFFER_SIZE;
    printf("password: "); 
    fgets(res, CLI_BUFFER_SIZE, stdin); 
    res[strlen(res) - 1] = '\0';

    return res;
}

