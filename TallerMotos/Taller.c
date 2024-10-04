#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define REPETITIONS 100  // Número de repeticiones 

// Declaración de semáforos
sem_t s_ruedas, s_chasis, s_motor, s_pintorR, s_pintorV, s_pintura, s_extra, s_extra_Turno;
pthread_mutex_t mutex_p;

void* ruedas(void* arg) {
    for(int i = 0; i < REPETITIONS; i++){
    sem_wait(&s_ruedas);  // Espera a que haya ruedas disponibles
        printf("Colocando ruedas...\n");
    sem_post(&s_chasis);  // Avisa que ya colocó las ruedas
    }
    sleep(1);
    return NULL;
}

void* chasis(void* arg){
    for(int i = 0; i < REPETITIONS; i++){
    sem_wait(&s_chasis); 
    sem_wait(&s_chasis); // Espera a que haya 2 chasis disponible
        printf("Colocando chasis...\n");
    sem_post(&s_motor);  // Avisa que ya colocó el chasis   
    }
    sleep(1);
    return NULL;
}

void* motor(void* arg){
    for(int i = 0; i < REPETITIONS; i++){
    sem_wait(&s_motor);  // Espera a que haya motor disponible
        printf("Colocando motor...\n");
    sem_post(&s_pintorR);
    sem_post(&s_pintorV);  // Avisa que ya colocó el motor
    }
    sleep(1);
    return NULL;
}

void* pintorR(void* arg){
    for(int i = 0; i < REPETITIONS; i++){
    sem_wait(&s_pintorR);  // Espera a que haya pintorR disponible
    pthread_mutex_lock(&mutex_p);
        if(sem_trywait(&s_pintura) == 0){
            printf("Pintando de rojo...\n");
            sem_post(&s_extra);
        }
        else{
            sem_post(&s_pintura);
        }    
    pthread_mutex_unlock(&mutex_p);
    }
    return NULL;
}

void* pintorV(void* arg){
    for(int i = 0; i < REPETITIONS; i++){
    sem_wait(&s_pintorV);  // Espera a que haya pintorV disponible
    pthread_mutex_lock(&mutex_p);
        if(sem_trywait(&s_pintura) == 0){
            printf("Pintando de verde...\n");
            sem_post(&s_extra);
        }
        else{
            sem_post(&s_pintura);
        }    
    pthread_mutex_unlock(&mutex_p);
    }
    return NULL;
    
}

void* extra(){
    for(int i = 0; i < REPETITIONS; i++){
    sem_wait(&s_extra);  // Espera a que haya extra disponible
    if(sem_trywait(&s_extra_Turno) == 0){
        printf("Colocando extras...\n");
    }
    else{
        sem_post(&s_extra_Turno);
    }
    sem_post(&s_ruedas);
    sem_post(&s_ruedas);
    }

    sleep(1);
    return NULL;
}

int main() {
    pthread_t thread_a, thread_b, thread_c, thread_d, thread_e, thread_f;

    //Inicializacion de los semaforos
    sem_init(&s_ruedas, 0, 2);
    sem_init(&s_chasis, 0, 0);
    sem_init(&s_motor, 0, 0);
    sem_init(&s_pintorR, 0, 0);
    sem_init(&s_pintorV, 0, 0);
    sem_init(&s_pintura, 0, 1);
    sem_init(&s_extra, 0, 0);
    sem_init(&s_extra_Turno, 0, 0);
    
    //inicialización de mutex's'
    pthread_mutex_init(&mutex_p, NULL);

    // Creación de los hilos
    pthread_create(&thread_a, NULL,ruedas, NULL);
    pthread_create(&thread_b, NULL, chasis, NULL);
    pthread_create(&thread_c, NULL, motor, NULL);
    pthread_create(&thread_d, NULL, pintorR, NULL);
    pthread_create(&thread_e, NULL, pintorV, NULL);
    pthread_create(&thread_f, NULL, extra, NULL);

    // Espera a que los hilos terminen
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    pthread_join(thread_c, NULL);
    pthread_join(thread_d, NULL);
    pthread_join(thread_e, NULL);
    pthread_join(thread_f, NULL);

    // Destrucción de los semáforos
    sem_destroy(&s_ruedas);
    sem_destroy(&s_chasis);
    sem_destroy(&s_motor);
    sem_destroy(&s_pintorR);
    sem_destroy(&s_pintorV);
    sem_destroy(&s_pintura);
    sem_destroy(&s_extra);
    sem_destroy(&s_extra_Turno);

    printf("\n");  // Salto de línea final
    return 0;
}