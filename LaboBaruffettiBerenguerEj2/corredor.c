#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

#define MSGSZ 128

typedef struct msgbuf {
    long mtype;
    char mtext[MSGSZ];
} message_buf;

int main(int argc, char *argv[]) {

    int msqid = atoi(argv[1]);
    message_buf rbuf;
    message_buf sbuf;
    sbuf.mtype = 4; // Tipo de mensaje para el padre

    while (1) {
        // Recibir mensaje de tipo 3 (corredor) de manera no bloqueante
        if (msgrcv(msqid, &rbuf, MSGSZ, 3, IPC_NOWAIT) < 0) {
            // Si no hay mensajes, continuar
            usleep(100000); // Esperar 100ms antes de intentar de nuevo
            continue;
        }
        printf("Corredor en instalaciones\n");
        sleep(1);
        printf("Se va corredor\n");

        // Enviar mensaje al padre indicando que se liberaron las instalaciones
        strcpy(sbuf.mtext, "Instalaciones liberadas");
        if (msgsnd(msqid, &sbuf, strlen(sbuf.mtext) + 1, 0) < 0) {
            perror("msgsnd");
            exit(1);
        }
    }

    return 0;
}
