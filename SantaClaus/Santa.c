#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define REPETITIONS 100 // Número de repeticiones

// Declaración de semáforos
sem_t s_santa, s_reno, s_elfo, s_elfoB, s_renoB;
pthread_mutex_t mutex_s, mutex_r, mutex_e;

void* renos(void* arg){
    int renoActual = 0;
    for(int i = 0; i < REPETITIONS; i++){
        sem_wait(&s_renoB);
            pthread_mutex_lock(&mutex_r);                               //Inicializar Semaforo en n-1
            if(sem_trywait(&s_reno) != 0){    
                renoActual = 0;                          
                printf("Voy a buscar a Santa, soy el ultimo Reno\n");
                sem_post(&s_santa);
            }
            else{
                renoActual++;
                printf("llega el reno %d\n", renoActual);
                sem_post(&s_renoB);
            }
            pthread_mutex_unlock(&mutex_r);
        
    }
    return NULL;
}

void* elfos(void* arg){
    int elfoActual = 0;
    for(int i = 0; i < REPETITIONS; i++){
        sem_wait(&s_elfoB);
        pthread_mutex_lock(&mutex_e);
        if(sem_trywait(&s_elfo) != 0){
            elfoActual = 0;
            printf("Voy a buscar a Santa, soy el ultimo Elfo\n");
            sem_post(&s_santa);
        }
        else{
            elfoActual++;
            printf("llega el elfo %d\n", elfoActual);
            sem_post(&s_elfoB);
        }
        pthread_mutex_unlock(&mutex_e);
    }
    return NULL;

}

void* santa(void* arg){
    for(int i = 0; i < REPETITIONS; i++){
        sem_wait(&s_santa);

        //Intento atender a los renos
            pthread_mutex_lock(&mutex_s);
            if(sem_trywait(&s_reno) != 0){
                printf("Santa ayuda a los Renos\n");
                for(int j = 0; j < 8; j++){     
                    sem_post(&s_reno);          //Puedo recibir a 9 renos mas
                }
                sem_post(&s_renoB);
            }else{
                sem_post(&s_reno);
            }
            //Veo si tambien tengo que atender a los elfos (s_santa = 2)
            if(sem_trywait(&s_santa) != 0){
                printf("Santa solo tiene una tarea\n");
            }
            else{
                printf("Santa tiene 2 tareas, sigue trabajando\n");
            }
            pthread_mutex_unlock(&mutex_s);

        //Intento atender a los elfos
        pthread_mutex_lock(&mutex_s);
        if(sem_trywait(&s_elfo) != 0){
            printf("Santa ayuda a los Elfos\n");
            for(int j = 0; j < 2; j++){     
                sem_post(&s_elfo);          //Puedo recibir a 3 elfos mas
            }
            sem_post(&s_elfoB);
        }else{
            sem_post(&s_elfo);
        }
        pthread_mutex_unlock(&mutex_s);
    }
    return NULL;
}

int main(){
    pthread_t thread_s, thread_r, thread_e;

    //Inicializacion de los semaforos
    sem_init(&s_santa, 0, 0);
    sem_init(&s_elfo, 0, 2);
    sem_init(&s_reno, 0, 8);
    sem_init(&s_elfoB, 0, 1);
    sem_init(&s_renoB, 0, 1);

    //Inicializacion de los mutex
    pthread_mutex_init(&mutex_s, NULL);
    pthread_mutex_init(&mutex_r, NULL);
    pthread_mutex_init(&mutex_e, NULL);

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
    sem_destroy(&s_elfoB);
    sem_destroy(&s_renoB);

    printf("\n");
    return 0;
}