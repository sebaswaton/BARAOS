#ifndef FILESYSTEM_H
#define FILESYSTEM_H

void init_filesystem();
int create_file(char* path, char* name, char* content);
int create_directory(char* path, char* name);
void list_directory(char* path);
int delete_item(char* path, char* name);
void show_file_content(char* path, char* name);
void change_directory(char* current_path, char* target);

#endif