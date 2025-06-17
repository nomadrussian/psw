#include "directory.h"

#include "config.h"
#include "error.h"

#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

typedef struct stat s_stat;

int dir_create(const char *path)
{
    if (path == nullptr)
    {
        return err_RECEIVED_NULLPTR;
    }

    // probably unnecessary check, potentially remove in the future
    if (dir_exists(path))
    {
        return err_DIR_ALREADY_EXISTS;
    }
    else
    {
        /* 0777 - permissions to read, write, and execute */
        if (mkdir(path, 0777) == 0)         {
            return SUCCESS;
        }
        else
        {
            switch (errno)
            {
                case EACCES:
                case EROFS: return err_DIR_NO_ACCESS;
                case EEXIST: return err_DIR_ALREADY_EXISTS;
                case ENAMETOOLONG: return err_NAME_TOO_LONG;
                case ENOSPC: return err_NOT_ENOUGH_SPACE;
                default: return err_UNKNOWN_ERROR;
            }
        }
    }
}

bool dir_exists(const char *path)
{
    if (path == nullptr)
    {
        return false;
    }

    s_stat st;
    stat(path, &st);

    return (errno != ENOENT) && (S_ISDIR(st.st_mode));
}

int dir_is_available(const char *path)
{
    if (path == nullptr)
    {
        return err_RECEIVED_NULLPTR;
    }

    s_stat st;

    if (stat(path, &st) != 0)
    {
        switch (errno)
        {
            case EACCES:
            case EROFS: return err_DIR_NO_ACCESS;
            case ENAMETOOLONG: return err_NAME_TOO_LONG;
            case ENOENT: return err_DIR_DOES_NOT_EXIST;
            case ENOMEM: return err_NOT_ENOUGH_RAM;
            default: return err_UNKNOWN_ERROR;
        }
    }
    else if (!S_ISDIR(st.st_mode))
    {
        return err_DIR_NOT_A_DIRECTORY;
    } else
    {
        return OK;
    }
}

