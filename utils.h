#ifndef _H_UTILS_
#define _H_UTILS_
#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t n);

int strcmp(const char *a, const char *b);
size_t strlen(const char *s);
void puts(char *s);
void int2str(int input, char *output);
void printf(char *output);
int strncmp(char *val1, char *val2, int length);

#endif
