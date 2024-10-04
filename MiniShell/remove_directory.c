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
        printf("Uso correcto: rmdir [nombre del directorio]\n");
        return 0;
    }

    const char *path = argv[1];

    if (rmdir(path) != 0) {
        perror("Error al eliminar el directorio");
    } else {
        printf("Directorio '%s' eliminado.\n", path);
    }
    return 0;

}

