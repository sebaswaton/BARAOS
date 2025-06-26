#ifndef SCREEN_H
#define SCREEN_H

void init_screen();
void clear_screen();
void print_char(char c);
void print_string(char* str);
void scroll_screen();
void update_cursor();
void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

#endif