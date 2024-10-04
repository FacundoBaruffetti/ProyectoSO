#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

int main() {
    
    printf("Comandos disponibles:\n");
    printf("help - Mostrar ayuda\n");
    printf("mkdir [directorio] - Crear un directorio\n");
    printf("rmdir [directorio] - Eliminar un directorio\n");
    printf("touch [archivo] - Crear un archivo\n");
    printf("ls [directorio] - Listar el contenido del directorio\n");
    printf("cat [archivo] - Mostrar el contenido de un archivo\n");
    printf("chmod [archivo] [permisos] - Modificar los permisos del archivo\n");

    return 0;
}
