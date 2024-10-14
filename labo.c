#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t lanzador_jabalina, lanazador_martillo, corredor, s_instalaciones, contador_corredores;
pthread_mutex_t instalaciones;

void *lanzador_jabalina(void *arg) {
    while (1) {
        sem_wait(&lanzador_jabalina);
        pthread_mutex_lock(&instalaciones);		
        if(sem_trywait(&s_instalaciones) != 0){	
            pthread_mutex_lock(&instalaciones);	
            printf("Lanzador de jabalina en instalaciones\n");
		}
		else{
			sem_post(&s_instalaciones);
            printf("Lanzador de jabalina no pudo entrar\n");
		}
        pthread_mutex_unlock(&instalaciones);

        pthread_mutex_lock(&instalaciones);
        sem_wait(&s_instalaciones);
        printf("Se va lanzador de jabalina\n");
        pthread_mutex_unlock(&instalaciones);
    }

}

void *lanzador_martillo(void *arg) {
    while (1) {
        sem_wait(&lanzador_martillo);
        pthread_mutex_lock(&instalaciones);		
        if(sem_trywait(&s_instalaciones) != 0){	
            pthread_mutex_lock(&instalaciones);	
            printf("Lanzador de martillo en instalaciones\n");
        }
        else{
            sem_post(&s_instalaciones);
            printf("Lanzador de martillo no pudo entrar\n");
        }
        pthread_mutex_unlock(&instalaciones);

        pthread_mutex_lock(&instalaciones);
        sem_wait(&s_instalaciones);
        printf("Se va lanzador de martillo\n");
        pthread_mutex_unlock(&instalaciones);
    }
}

void *corredor(void *arg) {
    while (1) {
        sem_wait(&corredor);
        pthread_mutex_lock(&instalaciones);	
        if(sem_trywait(&s_instalaciones) != 0){			
            printf("Entra primer corredor\n");
            sem_post(&s_instalaciones);
            sem_post(&contador_corredores);			
        }
        else{
            if(sem_trywait(&contador_corredores) != 0){			
                printf("Hay lanzadores y soy corredor\n");
                sem_post(&s_instalaciones);		
            }
            else{
                sem_post(&s_instalaciones);		
                sem_post(&contador_corredores);
                sem_post(&contador_corredores);
                printf("habia corredores y entro otro corredor\n");		
            }

        }
        pthread_mutex_unlock(&instalaciones);

        pthread_mutex_lock(&instalaciones);
        sem_wait(&contador_corredores);
        printf("Se va corredor\n");

        if(sem_trywait(&contador_corredores) != 0){
            printf("era el ultimo corredor\n");
            sem_post(&s_instalaciones);
        }
        pthread_mutex_unlock(&instalaciones);
    }
}

int main() {
    pthread_t t1, t2, t3;

    // Initialize semaphores
    sem_init(&lanzador_jabalina, 0, 0);
    sem_init(&lanazador_martillo, 0, 0);
    sem_init(&corredor, 0, 0);
    sem_init(&s_instalaciones, 0, 1);
    sem_init(&contador_corredores, 0, 0);

    // Initialize mutex
    pthread_mutex_init(&instalaciones, NULL);

    // Create threads
    pthread_create(&t1, NULL, lanzador_jabalina, NULL);
    pthread_create(&t2, NULL, lanzador_martillo, NULL);
    pthread_create(&t3, NULL, corredor, NULL);

   
    for (int i = 0; i < 100; i++) {
        int event = rand() % 3;
        switch (event) {
            case 0:
                sem_post(&lanzador_jabalina);
                break;
            case 1:
                sem_post(&lanazador_martillo);
                break;
            case 2:
                sem_post(&corredor);
                break;
        }
        sleep(1); // Simulate time between athletes
    }

    // Join threads (not reachable in this example)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&lanzador_jabalina);
    sem_destroy(&lanazador_martillo);
    sem_destroy(&corredor);
    sem_destroy(&s_instalaciones);
    sem_destroy(&contador_corredores);
    pthread_mutex_destroy(&instalaciones);

    return 0;
}