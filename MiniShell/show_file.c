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
        printf("Uso correcto: cat [nombre del directorio]\n");
        return 0;
    }

    const char *path = argv[1];

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 0;
    }
    //Crea buffer para lectura del contenido del archivo
    char buffer[1024];
    ssize_t bytes_read;

    //Lee el archivo por bloques y lo escribe en la salida estandar
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    if (bytes_read == -1) {
        perror("Error al leer el archivo");
    }
    close(fd);

    return 0;

}
