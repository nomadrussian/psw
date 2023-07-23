/* pswUtil.h */

unsigned int u_CheckIfPureUInt(const char *s);
unsigned int u_ParseUInt(const char *s);

unsigned int u_GetBit(int number, unsigned int index);
void u_SetBit(int *number, unsigned int index, unsigned int value);

unsigned int u_StringInArray(char **sArr, size_t sArr_size, char *s);

