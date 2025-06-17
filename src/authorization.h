#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "config.h"

extern bool authorized;

int check_authentification_data();
NOOPTIMIZE int attempt_authorize();
int load_authentification_data();
NOOPTIMIZE int force_log_out();
NOOPTIMIZE void clear_master_password_buff();

#endif

