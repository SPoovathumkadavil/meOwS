
#if !defined(_CONVERSIONS_H_)
#define _CONVERSIONS_H_

#include <stdint.h>

void int_to_ascii(int n, char str[]);
void hex_to_ascii(int n, char str[]);
void reverse(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);
void backspace(char s[]);
int strlen(const char *s);

#endif // _CONVERSIONS_H_
