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
        printf("Uso correcto: ls [nombre del directorio]\n");
        return 0;
    }

    const char *path = argv[1];

    DIR *d = opendir(path);
    if (!d) {
        perror("Error al abrir el directorio");
        return 0;
    }
    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(d);

    return 0;
}