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
        if (msgrcv(msqid, &rbuf, MSGSZ, 2, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }
        printf("Lanzador de martillo en instalaciones\n");
        sleep(1);
        printf("Se va lanzador de martillo\n");

        // Enviar mensaje al padre indicando que se liberaron las instalaciones
        strcpy(sbuf.mtext, "Instalaciones liberadas");
        if (msgsnd(msqid, &sbuf, strlen(sbuf.mtext) + 1, 0) < 0) {
            perror("msgsnd");
            exit(1);
        }
    }

    return 0;
}
