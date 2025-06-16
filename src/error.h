#ifndef ERROR_H
#define ERROR_H

#define SUCCESS_MSG "SUCCESS"
#define OK_MSG ""
#define err_UNKNOWN_COMMAND_MSG "Unknown command."
#define err_UNAUTHORIZED_MSG "You're unauthorized."
#define err_NO_MASTER_PASSWORD_FOUND_MSG "WARNING: No master password set or the data were corrupted."
#define err_WRONG_MASTER_PASSWORD_MSG "Wrong master password, try again."
#define err_FAILED_SAFE_EXIT_MSG "Failed to safely stop PSW."
#define err_UNKNOWN_ERROR_MSG "Unknown error."

typedef enum {
    SUCCESS = 1,
    OK = 0,
    err_UNKNOWN_COMMAND = -1,
    err_UNAUTHORIZED = -2,
    err_NO_MASTER_PASSWORD_FOUND = -3,
    err_WRONG_MASTER_PASSWORD = -4,
    err_FAILED_SAFE_EXIT = -1023,
    err_UNKNOWN_ERROR = -1024
} ErrorCode;

typedef struct {
    ErrorCode err_code;
    const char *err_msg;
} Error;

extern const Error ErrorMap[];

void showup_err(int err_code);

#endif

