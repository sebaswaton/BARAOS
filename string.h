#ifndef STRING_H
#define STRING_H

int strlen(const char* str);
int strcmp(const char* str1, const char* str2);
char* strcpy(char* dest, const char* src);
char* strcat(char* dest, const char* src);
char* strrchr(const char* str, int c);
int split_string(char* str, char delimiter, char** parts, int max_parts);

#endif