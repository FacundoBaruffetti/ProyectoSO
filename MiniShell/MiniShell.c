#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

void show_help();
void create_directory(const char *path);
void remove_directory(const char *path);
void create_file(const char *path);
void list_directory(const char *path);
void show_file(const char *path);
void change_permissions(const char *path);

int get_command_id(const char *command);

int main() {
    char input[1024];

    // Bucle infinito para mantener el shell en ejecución
    while (1) {
        printf("mini-shell> ");
        
        // Leer la entrada del usuario
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Error al leer la entrada");
            continue;
        }

        // Eliminar el salto de línea al final
        input[strcspn(input, "\n")] = 0;

        // Salir si el usuario ingresa "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Tokenizar la entrada para separar el comando y los argumentos
        char *command = strtok(input, " ");
        char *argument = strtok(NULL, "");
    
        

        int cmd_id = get_command_id(command);

        switch(cmd_id){
            case 1: 
                show_help();
                break;
            case 2:
                if(argument != NULL){
                    create_directory(argument);
                }
                else{
                    printf("Uso correcto: mkdir [nombre del directorio]\n");
                }
                break;
            case 3: 
                if(argument != NULL){
                    remove_directory(argument);
                }
                else{
                    printf("Uso correcto: rmdir [nombre del directorio]\n");
                }
                break;
            case 4:
                if(argument != NULL){
                    create_file(argument);
                }
                else{
                    printf("Uso correcto: touch [nombre del archivo]\n");
                }
                break;
            case 5:
                if(argument != NULL){
                    list_directory(argument);
                }
                else{
                    printf("Uso correcto: ls [nombre del directorio]\n");
                }
                break;
            case 6:
                if(argument != NULL){
                    show_file(argument);
                }
                else{
                    printf("Uso correcto: cat [nombre del archivo]\n");
                }
                break;
            case 7:
                if(argument != NULL){
                    change_permissions(argument);
                }
                else{
                    printf("Uso correcto: chmod [nombre del directorio] [permisos octales]\n");
                }
                break;
            default:
                printf("Comando no reconocido. Escribe 'help' para ver los comandos disponibles\n");    
        }
        
    }

    return 0;
}

void show_help() {
    pid_t pid = fork();

    if (pid < 0) {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso que maneja el comando de ayuda");
        return;
    }

    if (pid == 0) {
        execl("./show_help", "show_help", (char *)NULL);
        
        perror("Error al ejecutar proceso que maneja el comando de ayuda");
    } 
    else {
        wait(NULL);
    }
}


void create_directory(const char *path) {
    pid_t pid = fork();

    if (pid < 0) {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso que maneja la creación del directorio");
        return;
    }

    if (pid == 0) {
        execl("./create_directory", "create_directory", path, (char *)NULL);
        perror("Error al ejecutar proceso que maneja la creación del directorio");
    } 
    else {
        wait(NULL);
    }
}

void remove_directory(const char *path) {
    pid_t pid = fork();

    if (pid < 0) {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso que maneja la eliminación del directorio");
        return;
    }

    if (pid == 0) {
        execl("./remove_directory", "remove_directory", path, (char *)NULL);
        perror("Error al ejecutar proceso que maneja la eliminación del directorio");
    } 
    else {
        wait(NULL);
    }
}

void create_file(const char *path) {
    pid_t pid = fork();

    if (pid < 0) {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso que maneja la creacion del archivo");
        return;
    }

    if (pid == 0) {
        execl("./create_file", "create_file", path, (char *)NULL);
        perror("Error al ejecutar proceso que maneja la creacion del archivo");
    } 
    else {
        wait(NULL);
    }
}

void list_directory(const char *path) {
    pid_t pid = fork();

    if (pid < 0) {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso que lista el contenido del directorio");
        return;
    }

    if (pid == 0) {
        execl("./list_directory", "list_directory", path, (char *)NULL);
        perror("Error al ejecutar proceso que lista el contenido del directorio");
    } 
    else {
        wait(NULL);
    }
}

void show_file(const char *path) {
    pid_t pid = fork();

    if (pid < 0) {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso que muestra el contenido del archivo");
        return;
    }

    if (pid == 0) {
        execl("./show_file", "show_file", path, (char *)NULL);
        perror("Error al ejecutar proceso que muestra el contenido del archivo");
    } 
    else {
        wait(NULL);
    }
}

void change_permissions(const char *path) {
    pid_t pid = fork();

    if (pid < 0) {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso que modifica los permisos de un archivo");
        return;
    }

    if (pid == 0) {
        execl("./change_permissions", "change_permissions", path, (char *)NULL);
        perror("Error al ejecutar proceso que modifica los permisos de un archivo");
    } 
    else {
        wait(NULL);
    }
}

int get_command_id(const char *command) {
    if (strcmp(command, "help") == 0) {
        return 1;
    } else if (strcmp(command, "mkdir") == 0) {
        return 2;
    } else if (strcmp(command, "rmdir") == 0) {
        return 3;
    } else if (strcmp(command, "touch") == 0) {
        return 4;
    } else if (strcmp(command, "ls") == 0) {
        return 5;
    } else if (strcmp(command, "cat") == 0) {
        return 6;
    } else if (strcmp(command, "chmod") == 0) {
        return 7;
    } else {
        return 0;  // Comando no reconocido
    }
}