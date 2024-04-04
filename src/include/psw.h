/* psw.h */
#pragma once

const char *VERSION = "v0.4";
const char *LAST_UPD = "August 14th, 2023";

void proceedInfo(int argc, char **argv);
void proceedHelp(int argc, char **argv);
void proceedGen(int argc, char **argv);
void proceedGenlist(int argc, char **argv);
int getGenFlags(int argc, char **argv, int shift);
