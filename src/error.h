#ifndef ERROR_H
#define ERROR_H

#define msg_LOGGED_OUT "You've been logged out"
#define msg_SUCCESS "SUCCESS"
#define msg_OK ""
#define errmsg_UNKNOWN_COMMAND "Unknown command"
#define errmsg_UNAUTHORIZED "You are unauthorized"
#define errmsg_AUTHORIZED "You are already logged in"
#define errmsg_CORRUPTED_AUTHENTIFICATION_DATA "WARNING: No master password set or the data were corrupted"
#define errmsg_WRONG_MASTER_PASSWORD "Wrong master password, try again"
#define errmsg_FAILED_TO_SET_MASTER_PASSWORD "Error: Unable to set master password"
#define errmsg_PASSWORD_DOES_NOT_MEET_REQUIREMENTS "The password does not meet safety requirements"
#define errmsg_FAILED_SAFE_EXIT "ERROR: Failed to safely stop PSW"
#define errmsg_UNKNOWN_ERROR "Unknown error"
#define errmsg_NOT_ENOUGH_SPACE "ERROR: Not enough hard drive space"
#define errmsg_NOT_ENOUGH_RAM "ERROR: Not enough RAM"
#define errmsg_NAME_TOO_LONG "Name is too long"
#define errmsg_NULLPTR_FREE_ATTEMPT "err_NULLPTR_FREE_ATTEMPT (internal error)"
#define errmsg_NULLPTR_CLEAR_ATTEMPT "err_NULLPTR_CLEAR_ATTEMPT (internal error)"
#define errmsg_RECEIVED_NULLPTR "err_RECEIVED_NULLPTR (internal error)"
#define errmsg_DIR_NO_ACCESS "No access to directory"
#define errmsg_DIR_DOES_NOT_EXIST "Directory does not exist"
#define errmsg_DIR_ALREADY_EXISTS "Directory already exists"
#define errmsg_DIR_NOT_A_DIRECTORY "Not a directory"

typedef enum {
    LOGGED_OUT = 2,
    SUCCESS = 1,
    OK = 0,
    err_UNKNOWN_COMMAND = -1,
    err_UNAUTHORIZED = -2,
    err_AUTHORIZED = -3,
    err_CORRUPTED_AUTHENTIFICATION_DATA = -4,
    err_WRONG_MASTER_PASSWORD = -5,
    err_FAILED_TO_SET_MASTER_PASSWORD = -6,
    err_PASSWORD_DOES_NOT_MEET_REQUIREMENTS = -7,
    err_FAILED_SAFE_EXIT = -1023,
    err_UNKNOWN_ERROR = -1024,
    err_NOT_ENOUGH_SPACE = -1025,
    err_NOT_ENOUGH_RAM = -1026,
    err_NAME_TOO_LONG = -1027,
    err_NULLPTR_FREE_ATTEMPT = -1028,
    err_NULLPTR_CLEAR_ATTEMPT = -1029,
    err_RECEIVED_NULLPTR = -1030,
    err_DIR_NO_ACCESS = -1031,
    err_DIR_DOES_NOT_EXIST = -1032,
    err_DIR_ALREADY_EXISTS = -1033,
    err_DIR_NOT_A_DIRECTORY = -1034
} ErrorCode;

typedef struct {
    ErrorCode err_code;
    const char *errmsg;
} Error;

extern const Error ErrorMap[];

void showup_err(int err_code);

#endif

