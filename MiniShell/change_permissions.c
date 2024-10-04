#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Uso correcto: chmod [nombre del directorio]\n");
        return 0;
    }

    const char *path = argv[1];

    // Tokenizar el argumento para separar el archivo y los permisos
    char *file = strtok((char *)path, " ");
    char *perm_str = strtok(NULL, " ");

    if (file == NULL || perm_str == NULL) {
        printf("Uso correcto: chmod [archivo] [permisos octales]\n");
        return 0;
    }

    // Convertir los permisos a un entero en base octal
    mode_t mode = strtol(perm_str, NULL, 8);

    // Llamar a chmod() para cambiar los permisos
    if (chmod(file, mode) == -1) {
        perror("Error al cambiar permisos");
    } else {
        printf("Permisos de '%s' cambiados a %s.\n", file, perm_str);
    }

    return 0;
}
