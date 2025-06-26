#include "screen.h"

#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define WHITE_ON_BLACK 0x0F

static int cursor_x = 0;
static int cursor_y = 0;

void init_screen() {
    clear_screen();
}

void clear_screen() {
    char* video_mem = (char*)VIDEO_MEMORY;
    
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * 2; i += 2) {
        video_mem[i] = ' ';
        video_mem[i + 1] = WHITE_ON_BLACK;
    }
    
    cursor_x = 0;
    cursor_y = 0;
    update_cursor();
}

void print_char(char c) {
    char* video_mem = (char*)VIDEO_MEMORY;
    
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\r') {
        cursor_x = 0;
    } else if (c == '\b') {
        if (cursor_x > 0) {
            cursor_x--;
            int pos = (cursor_y * SCREEN_WIDTH + cursor_x) * 2;
            video_mem[pos] = ' ';
            video_mem[pos + 1] = WHITE_ON_BLACK;
        }
    } else {
        int pos = (cursor_y * SCREEN_WIDTH + cursor_x) * 2;
        video_mem[pos] = c;
        video_mem[pos + 1] = WHITE_ON_BLACK;
        cursor_x++;
    }
    
    if (cursor_x >= SCREEN_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    
    if (cursor_y >= SCREEN_HEIGHT) {
        scroll_screen();
        cursor_y = SCREEN_HEIGHT - 1;
    }
    
    update_cursor();
}

void print_string(char* str) {
    while (*str) {
        print_char(*str);
        str++;
    }
}

void scroll_screen() {
    char* video_mem = (char*)VIDEO_MEMORY;
    
    // Mover todas las líneas hacia arriba
    for (int i = 0; i < (SCREEN_HEIGHT - 1) * SCREEN_WIDTH * 2; i++) {
        video_mem[i] = video_mem[i + SCREEN_WIDTH * 2];
    }
    
    // Limpiar la última línea
    for (int i = (SCREEN_HEIGHT - 1) * SCREEN_WIDTH * 2; i < SCREEN_HEIGHT * SCREEN_WIDTH * 2; i += 2) {
        video_mem[i] = ' ';
        video_mem[i + 1] = WHITE_ON_BLACK;
    }
}

void update_cursor() {
    int pos = cursor_y * SCREEN_WIDTH + cursor_x;
    
    // Enviar la posición al controlador de video
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

void outb(unsigned short port, unsigned char data) {
    asm volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

unsigned char inb(unsigned short port) {
    unsigned char result;
    asm volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}