/* generator.c - this module generates a new password. */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "generator.h"

// Returns a string containing a new-generated password.
const char *generatePassword(int FLAGS) {
    
    char *password = malloc((FLAGS % 0x100) * sizeof(char));
    unsigned long seed = time(NULL);
    unsigned long useless_garbage;
    useless_garbage = (unsigned long) &useless_garbage;
    
    seed ^= (useless_garbage * (seed * 0xCAFE + useless_garbage % 0xBEEF)) >> (seed % 0x4) * seed * 0x50BAD;
    
    for(int i = 0; i < FLAGS % 0x100; i++) {
        password[i] = randomChar(32, 126, seed + i + (useless_garbage * seed + 0xF00D));
    }

    return password;
}

char randomChar(int range_b, int range_t, unsigned long seed) {
    
    srand(seed);
    
    return rand() % (range_t - range_b + 1) + range_b;
}
