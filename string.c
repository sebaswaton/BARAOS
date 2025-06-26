#include "string.h"

int strlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int strcmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) return -1;
        if (str1[i] > str2[i]) return 1;
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') return 0;
    if (str1[i] == '\0') return -1;
    return 1;
}

char* strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char* strcat(char* dest, const char* src) {
    int dest_len = strlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

char* strrchr(const char* str, int c) {
    char* last = 0;
    while (*str) {
        if (*str == c) {
            last = (char*)str;
        }
        str++;
    }
    return last;
}

int split_string(char* str, char delimiter, char** parts, int max_parts) {
    int count = 0;
    int start = 0;
    int len = strlen(str);
    
    for (int i = 0; i <= len && count < max_parts; i++) {
        if (str[i] == delimiter || str[i] == '\0') {
            if (i > start) {
                parts[count] = str + start;
                str[i] = '\0';
                count++;
            }
            start = i + 1;
        }
    }
    
    return count;
}