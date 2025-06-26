#include "keyboard.h"
#include "screen.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

static char scancode_to_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

void init_keyboard() {
    // Habilitar interrupciones del teclado
}

char read_key() {
    while (1) {
        if (inb(KEYBOARD_STATUS_PORT) & 1) {
            unsigned char scancode = inb(KEYBOARD_DATA_PORT);
            
            if (scancode & 0x80) {
                // Tecla liberada, ignorar
                continue;
            }
            
            if (scancode < sizeof(scancode_to_ascii)) {
                char ascii = scancode_to_ascii[scancode];
                if (ascii != 0) {
                    return ascii;
                }
            }
        }
    }
}

void read_line(char* buffer, int max_length) {
    int index = 0;
    char c;
    
    while (index < max_length - 1) {
        c = read_key();
        
        if (c == '\n') {
            break;
        } else if (c == '\b') {
            if (index > 0) {
                index--;
                print_char('\b');
            }
        } else if (c >= 32 && c <= 126) {
            buffer[index] = c;
            index++;
            print_char(c);
        }
    }
    
    buffer[index] = '\0';
    print_char('\n');
}