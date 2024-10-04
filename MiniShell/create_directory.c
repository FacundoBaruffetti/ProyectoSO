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
        printf("Uso correcto: mkdir [nombre del directorio]\n");
        return 0;
    }

    const char *path = argv[1];

    if (mkdir(path, 0755) != 0) {
        perror("Error al crear el directorio");
    } 
    else {
        printf("Directorio '%s' creado.\n", path);
    }

    return 0;
}
