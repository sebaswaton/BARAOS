#include "filesystem.h"
#include "string.h"
#include "memory.h"
#include "screen.h"

#define MAX_FILES 100
#define MAX_FILENAME 64
#define MAX_CONTENT 512

typedef struct {
    char name[MAX_FILENAME];
    char path[256];
    char content[MAX_CONTENT];
    int is_directory;
    int exists;
} File;

static File filesystem[MAX_FILES];
static int file_count = 0;

void init_filesystem() {
    // Limpiar sistema de archivos
    for (int i = 0; i < MAX_FILES; i++) {
        filesystem[i].exists = 0;
    }
    
    // Crear directorio raíz
    strcpy(filesystem[0].name, "/");
    strcpy(filesystem[0].path, "");
    filesystem[0].is_directory = 1;
    filesystem[0].exists = 1;
    file_count = 1;
    
    // Crear algunos archivos y directorios de ejemplo
    create_directory("/", "home");
    create_directory("/", "bin");
    create_file("/", "readme.txt", "Bienvenido a BaraOS!\nSistema de archivos simple.");
    create_file("/home", "usuario.txt", "Archivo de usuario");
}

int create_file(char* path, char* name, char* content) {
    if (file_count >= MAX_FILES) {
        print_string("Error: Sistema de archivos lleno\n");
        return 0;
    }
    
    // Verificar si ya existe
    for (int i = 0; i < MAX_FILES; i++) {
        if (filesystem[i].exists && 
            strcmp(filesystem[i].path, path) == 0 && 
            strcmp(filesystem[i].name, name) == 0) {
            // Actualizar contenido si ya existe
            strcpy(filesystem[i].content, content);
            filesystem[i].is_directory = 0;
            print_string("Archivo actualizado: ");
            print_string(name);
            print_string("\n");
            return 1;
        }
    }
    
    // Crear nuevo archivo
    for (int i = 0; i < MAX_FILES; i++) {
        if (!filesystem[i].exists) {
            strcpy(filesystem[i].name, name);
            strcpy(filesystem[i].path, path);
            strcpy(filesystem[i].content, content);
            filesystem[i].is_directory = 0;
            filesystem[i].exists = 1;
            file_count++;
            print_string("Archivo creado: ");
            print_string(name);
            print_string("\n");
            return 1;
        }
    }
    
    return 0;
}

int create_directory(char* path, char* name) {
    if (file_count >= MAX_FILES) {
        print_string("Error: Sistema de archivos lleno\n");
        return 0;
    }
    
    // Verificar si ya existe
    for (int i = 0; i < MAX_FILES; i++) {
        if (filesystem[i].exists && 
            strcmp(filesystem[i].path, path) == 0 && 
            strcmp(filesystem[i].name, name) == 0) {
            print_string("El directorio ya existe: ");
            print_string(name);
            print_string("\n");
            return 0;
        }
    }
    
    // Crear nuevo directorio
    for (int i = 0; i < MAX_FILES; i++) {
        if (!filesystem[i].exists) {
            strcpy(filesystem[i].name, name);
            strcpy(filesystem[i].path, path);
            filesystem[i].content[0] = '\0';
            filesystem[i].is_directory = 1;
            filesystem[i].exists = 1;
            file_count++;
            print_string("Directorio creado: ");
            print_string(name);
            print_string("\n");
            return 1;
        }
    }
    
    return 0;
}

void list_directory(char* path) {
    int found = 0;
    
    for (int i = 0; i < MAX_FILES; i++) {
        if (filesystem[i].exists && strcmp(filesystem[i].path, path) == 0) {
            if (filesystem[i].is_directory) {
                print_string("[DIR]  ");
            } else {
                print_string("[FILE] ");
            }
            print_string(filesystem[i].name);
            print_string("\n");
            found = 1;
        }
    }
    
    if (!found) {
        print_string("Directorio vacio\n");
    }
}

int delete_item(char* path, char* name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (filesystem[i].exists && 
            strcmp(filesystem[i].path, path) == 0 && 
            strcmp(filesystem[i].name, name) == 0) {
            filesystem[i].exists = 0;
            file_count--;
            print_string("Eliminado: ");
            print_string(name);
            print_string("\n");
            return 1;
        }
    }
    
    print_string("No encontrado: ");
    print_string(name);
    print_string("\n");
    return 0;
}

void show_file_content(char* path, char* name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (filesystem[i].exists && 
            strcmp(filesystem[i].path, path) == 0 && 
            strcmp(filesystem[i].name, name) == 0) {
            if (filesystem[i].is_directory) {
                print_string("Error: ");
                print_string(name);
                print_string(" es un directorio\n");
                return;
            }
            print_string(filesystem[i].content);
            print_string("\n");
            return;
        }
    }
    
    print_string("Archivo no encontrado: ");
    print_string(name);
    print_string("\n");
}

void change_directory(char* current_path, char* target) {
    if (strcmp(target, "..") == 0) {
        // Ir al directorio padre
        if (strcmp(current_path, "/") != 0) {
            char* last_slash = strrchr(current_path, '/');
            if (last_slash != current_path) {
                *last_slash = '\0';
            } else {
                strcpy(current_path, "/");
            }
        }
        return;
    }
    
    if (strcmp(target, "/") == 0) {
        strcpy(current_path, "/");
        return;
    }
    
    // Buscar directorio
    for (int i = 0; i < MAX_FILES; i++) {
        if (filesystem[i].exists && 
            strcmp(filesystem[i].path, current_path) == 0 && 
            strcmp(filesystem[i].name, target) == 0 &&
            filesystem[i].is_directory) {
            
            if (strcmp(current_path, "/") == 0) {
                strcpy(current_path, "/");
                strcat(current_path, target);
            } else {
                strcat(current_path, "/");
                strcat(current_path, target);
            }
            return;
        }
    }
    
    print_string("Directorio no encontrado: ");
    print_string(target);
    print_string("\n");
}