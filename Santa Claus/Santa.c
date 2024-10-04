#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define REPETITIONS 100  // Número de repeticiones

// Declaración de semáforos
sem_t s_santa, s_reno, s_elfo;
pthread_mutex_t mutex_s;

void* renos(void* arg){
    for(int i = 0; i < REPETITIONS; i++){
        int renoActual = 0;
        if(sem_trywait(&s_reno) == 0){
            printf('Voy a buscar a Santa, soy el ultimo Reno\n');
            sem_post(&s_santa);
            sem_wait(&s_reno); //Dejo de ciclar
        }
        else{
            renoActual++;
            printf('llega el reno %d\n', renoActual);
        }
    }
    return NULL;
}

void* elfos(void* arg){
    for(int i = 0; i < REPETITIONS; i++){
        int elfoActual = 0;
        if(sem_trywait(&s_elfo) == 0){
            elfoActual = 0;
            printf('Voy a buscar a Santa, soy el ultimo Elfo\n');
            sem_post(&s_santa);
            sem_wait(&s_elfo); //Espera a que santa atienda a los 3 elfos
        }
        else{
            elfoActual++;
            printf('llega el elfo %d\n', elfoActual);
        }
    }
    return NULL;

}

void* santa(void* arg){
    for(int i = 0; i < REPETITIONS; i++){
        //Intento atender a los renos
        if(sem_trywait(&s_reno) == -1){
            sem_wait(&s_santa);
            pthread_mutex_lock(&mutex_s);
                printf('Santa acomoda a los Renos\n');
            pthread_mutex_unlock(&mutex_s);
        }
        else{
            sem_post(&s_reno);
        }

        //Intento atender a los elfos
        if(sem_trywait(&s_elfo) == -1){
            sem_wait(&s_santa);
            pthread_mutex_lock(&mutex_s);
                printf('Santa ayuda a los Elfos\n');
            pthread_mutex_unlock(&mutex_s);
            for(int j = 0; j < 5; j++){      //#Signals = 3 x elfo + wait para detener ciclo Elfos + descuento Trywait
                sem_post(&s_elfo);          //Puedo recibir a 3 elfos mas
            }
        }
        else{
            sem_post(&s_elfo);
        }
    }
    return NULL;
}

int main(){
    pthread_t thread_s, thread_r, thread_e;

    //Inicializacion de los semaforos
    sem_init(&s_santa, 0, 0);
    sem_init(&s_elfo, 0, 3);
    sem_init(&s_reno, 0, 9);

    //Inicializacion de los mutex
    pthread_mutex_init(&mutex_s, NULL);

    // Creación de los hilos
    pthread_create(&thread_s, NULL, santa, NULL);
    pthread_create(&thread_r, NULL, renos, NULL);
    pthread_create(&thread_e, NULL, elfos, NULL);

    // Espera a que los hilos terminen
    pthread_join(thread_s, NULL);
    pthread_join(thread_r, NULL);
    pthread_join(thread_e, NULL);

    // Destrucción de los semáforos
    sem_destroy(&s_santa);
    sem_destroy(&s_elfo);
    sem_destroy(&s_reno);

    printf('\n');
    return 0;
}