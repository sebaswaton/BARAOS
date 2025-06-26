#ifndef KEYBOARD_H
#define KEYBOARD_H

void init_keyboard();
char read_key();
void read_line(char* buffer, int max_length);

#endif