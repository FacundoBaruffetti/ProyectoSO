#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MSGSZ 128

typedef struct msgbuf {
    long mtype;
    char mtext[MSGSZ];
} message_buf;

int main() {
    int msqid;
    key_t key = 1234;
    message_buf sbuf, rbuf;
    size_t buf_length;

    if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    if (fork() == 0) {
        char msqid_str[10];
        snprintf(msqid_str, sizeof(msqid_str), "%d", msqid);
        execl("/lanzador_jabalina", "/lanzador_jabalina", msqid_str, NULL);
        perror("execl");
        exit(1);
    }
    if (fork() == 0) {
        char msqid_str[10];
        snprintf(msqid_str, sizeof(msqid_str), "%d", msqid);
        execl("/lanzador_martillo", "/lanzador_martillo", msqid_str, NULL);
        perror("execl");
        exit(1);
    }
    if (fork() == 0) {
        char msqid_str[10];
        snprintf(msqid_str, sizeof(msqid_str), "%d", msqid);
        execl("/corredor", "/corredor", msqid_str, NULL);
        perror("execl");
        exit(1);
    }

    //Creacion aleatoria de atletas
    for (int i = 0; i < 100; i++) {
        int event = rand() % 3;
        sbuf.mtype = event + 1;
        snprintf(sbuf.mtext, MSGSZ, "Event %d", event);
        buf_length = strlen(sbuf.mtext) + 1;

        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            perror("msgsnd");
            exit(1);
        }

        // Wait for a message indicating the installations are free, except if the event is for corredor (event == 2)
        if (event != 2) {
            if (msgrcv(msqid, &rbuf, MSGSZ, 4, 0) < 0) {
            perror("msgrcv");
            exit(1);
            }
            printf("Se liberaron las instalaciones: %s\n", rbuf.mtext);
        } else {
            // Check if there are any messages indicating the installations are free
            if (msgrcv(msqid, &rbuf, MSGSZ, 4, IPC_NOWAIT) >= 0) {
            printf("Se liberaron las instalaciones: %s\n", rbuf.mtext);
            }
        }

        sleep(1); // Simulate time between athletes
        }

        // Wait for child processes to finish
        for (int i = 0; i < 3; i++) {
        wait(NULL);
        }

        // Remove message queue
        if (msgctl(msqid, IPC_RMID, NULL) < 0) {
        perror("msgctl");
        exit(1);
        }

        return 0;
    }
