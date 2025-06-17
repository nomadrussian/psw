#ifndef DIRECTORY_H
#define DIRECTORY_H

int dir_create(const char *path);
bool dir_exists(const char *path);
int dir_is_available(const char *path);

#endif

