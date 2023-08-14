/* errorHandler.h */

void err_RedundantArg(char **argv, int argID);
void err_RedundantFlag(char **argv, int argID);
void err_UnexpectedArg(char **argv, int argID);
void err_UnexpectedArgSpecified(char **argv, int argID, char *unexp, char *exp);
void err_UnexpectedArgRange(char **argv, int argID, char *unexp, char *exp);

