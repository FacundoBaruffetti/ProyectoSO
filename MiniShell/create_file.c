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
        printf("Uso correcto: touch [nombre del archivo]\n");
        return 0;
    }

    const char *path = argv[1];

    //Crea el archivo con permisos de lectura/escritura para el propietario, y permisos de lectura para otros
    int fd = open(path, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error al crear el archivo");
    } else {
        close(fd);
    }
    return 0;
}
