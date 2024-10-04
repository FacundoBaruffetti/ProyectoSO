#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
include <unistd.h>

void crear_hijo(pipe1, pipe2);

int main() {

    int pipe1[2]; // Pipe de padre a hijo1
    int pipe2[2]; // Pipe de padre a hijo2
    int pipe3[2]; // Pipe de padre a hijo3
    int pipe4[2]; // Pipe de padre a hijo4

    int pipe5[2]; // Pipe de hijo1 a padre
    int pipe6[2]; // Pipe de hijo2 a padre
    int pipe7[2]; // Pipe de hijo3 a padre
    int pipe8[2]; // Pipe de hijo4 a padre

    //Creacion de los hijos y sus respectivos pipes
    crear_hijo(pipe1, pipe5);
    crear_hijo(pipe2, pipe6);
    crear_hijo(pipe3, pipe7);
    crear_hijo(pipe4, pipe8);

    //Operar segun corresponda

}

void crear_hijo(int pipe1[2], pipe2[2]){
    pid_t pid;
    
    // Crear el primer pipe (padre a hijo)
    if (pipe(pipe1) == -1) {
        perror("Error al crear pipe1");
        exit(1);
    }

    // Crear el segundo pipe (hijo a padre)
    if (pipe(pipe2) == -1) {
        perror("Error al crear pipe2");
        exit(1);
    }

    // Crear el proceso hijo
    pid = fork();

    if (pid == 0) {
        // Cerrar el extremo de escritura del primer pipe
        close(pipe1[1]);
        // Cerrar el extremo de lectura del segundo pipe
        close(pipe2[1]);

        dup2(pipe1[0], STDIN_FILENO);  // Redirigir la entrada estándar
        dup2(pipe2[0], STDOUT_FILENO); // Redirigir la salida estándar

        //execlp(...)
    }
    else{
        // Cerrar el extremo de lectura del primer pipe
        close(pipe1[0]);
        // Cerrar el extremo de lectura del segundo pipe
        close(pipe2[0]);   
    }
}