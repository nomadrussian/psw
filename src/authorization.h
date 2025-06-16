#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "config.h"

NOOPTIMIZE int attempt_authorize();
int load_authentification_data();
NOOPTIMIZE void clear_master_password_buff();

#endif

