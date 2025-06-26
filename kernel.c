#include "screen.h"
#include "keyboard.h"
#include "filesystem.h"
#include "string.h"
#include "memory.h"

#define MAX_COMMAND_LENGTH 256

void kernel_main() {
    char command[MAX_COMMAND_LENGTH];
    char current_path[256] = "/";
    
    // Inicializar componentes
    init_screen();
    init_keyboard();
    init_filesystem();
    
    // Mostrar banner de bienvenida
    print_string("==============================\n");
    print_string("      Bienvenido a BaraOS     \n");
    print_string("  Sistema de Gestion de Archivos\n");
    print_string("==============================\n\n");
    print_string("Escribe 'help' para ver comandos disponibles\n\n");
    
    // Loop principal del sistema
    while (1) {
        print_string(current_path);
        print_string("$ ");
        
        // Leer comando del usuario
        read_line(command, MAX_COMMAND_LENGTH);
        
        // Procesar comando
        if (strlen(command) > 0) {
            execute_command(command, current_path);
        }
    }
}

void execute_command(char* command, char* current_path) {
    char* parts[10];
    int part_count = split_string(command, ' ', parts, 10);
    
    if (part_count == 0) return;
    
    if (strcmp(parts[0], "help") == 0) {
        show_help();
    }
    else if (strcmp(parts[0], "clear") == 0) {
        clear_screen();
    }
    else if (strcmp(parts[0], "ls") == 0) {
        list_directory(current_path);
    }
    else if (strcmp(parts[0], "pwd") == 0) {
        print_string(current_path);
        print_string("\n");
    }
    else if (strcmp(parts[0], "mkdir") == 0) {
        if (part_count < 2) {
            print_string("Uso: mkdir <nombre_directorio>\n");
        } else {
            create_directory(current_path, parts[1]);
        }
    }
    else if (strcmp(parts[0], "touch") == 0) {
        if (part_count < 2) {
            print_string("Uso: touch <nombre_archivo>\n");
        } else {
            create_file(current_path, parts[1], "");
        }
    }
    else if (strcmp(parts[0], "rm") == 0) {
        if (part_count < 2) {
            print_string("Uso: rm <nombre>\n");
        } else {
            delete_item(current_path, parts[1]);
        }
    }
    else if (strcmp(parts[0], "cd") == 0) {
        if (part_count < 2) {
            strcpy(current_path, "/");
        } else {
            change_directory(current_path, parts[1]);
        }
    }
    else if (strcmp(parts[0], "cat") == 0) {
        if (part_count < 2) {
            print_string("Uso: cat <nombre_archivo>\n");
        } else {
            show_file_content(current_path, parts[1]);
        }
    }
    else if (strcmp(parts[0], "echo") == 0) {
        handle_echo_command(parts, part_count, current_path);
    }
    else {
        print_string("Comando no encontrado: ");
        print_string(parts[0]);
        print_string("\nEscribe 'help' para ver comandos disponibles\n");
    }
}

void show_help() {
    print_string("Comandos disponibles en BaraOS:\n");
    print_string("  help              - Mostrar esta ayuda\n");
    print_string("  clear             - Limpiar pantalla\n");
    print_string("  ls                - Listar archivos y directorios\n");
    print_string("  pwd               - Mostrar directorio actual\n");
    print_string("  mkdir <nombre>    - Crear directorio\n");
    print_string("  touch <archivo>   - Crear archivo vacio\n");
    print_string("  rm <nombre>       - Eliminar archivo/directorio\n");
    print_string("  cd <directorio>   - Cambiar directorio\n");
    print_string("  cat <archivo>     - Mostrar contenido de archivo\n");
    print_string("  echo <texto> > <archivo> - Escribir texto a archivo\n\n");
}

void handle_echo_command(char** parts, int count, char* current_path) {
    if (count < 4 || strcmp(parts[count-2], ">") != 0) {
        print_string("Uso: echo <texto> > <archivo>\n");
        return;
    }
    
    char content[512] = "";
    for (int i = 1; i < count - 2; i++) {
        strcat(content, parts[i]);
        if (i < count - 3) strcat(content, " ");
    }
    
    create_file(current_path, parts[count-1], content);
}