/* pswUtil.c - custom functions for password generator and manager */

#include <string.h>

// Checks if a string contains only a pure number. 1 - true, 0 - false.
unsigned int u_CheckIfPureUInt(const char *s) {
   
    unsigned int len = strlen(s);
    
    if(len == 0 || len > 10) {
        return 0;
    }
    
    for(int i = 0; i < len; i++) {
        if(s[i] < 48 || s[i] > 57) {
            return 0;
        }
    }
    
    return 1;
}

// Gets a string containing a number and returns it as an unsigned int.
// It doesn't care if it's correct, anticipating it has been checked.
unsigned int u_ParseUInt(const char *s) {
    
    unsigned int ui = 0;
    unsigned int len = strlen(s);
    
    for(int i = 0; i < len; i++) {
        unsigned int pos = len - 1 - i;
        unsigned int ten_multiplier = 1;
        for(int j = 0; j < pos; j++) {
            ten_multiplier *= 10;
        }
        ui += (s[i] - 48) * ten_multiplier;
    }
    
    return ui;
}

// indices start from 0
unsigned int u_GetBit(int number, unsigned int index) {
    return (number >> index) % 2;
}

// checks if a string is present in an array of strings
unsigned int u_StringInArray(const char **sArr, size_t sArr_size, const char *s) {

    for(size_t i = 0; i < sArr_size; i++) {
        if (sArr[i] == NULL) break;
        if(!strcmp(sArr[i], s)) {
            return 1;
        }
    }
    
    return 0;
}
