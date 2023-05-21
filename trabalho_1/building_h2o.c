#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OXYGEN_LIMIT 5
#define HYDROGEN_LIMIT 10

int oxygen_amount = 0;
int hydrogen_amount = 0;
int h2o_amount = 0;

sem_t sem_hydrogen;
sem_t sem_oxygen;
pthread_mutex_t mutex;
pthread_mutex_t print_mutex;
pthread_barrier_t barrier;

void clear_console() {
    printf("\e[1;1H\e[2J"); // Clear console
}

void animation() {
    sleep(1);

    pthread_mutex_lock(&print_mutex);
    clear_console();

    printf("_________\n");
    for (int i = OXYGEN_LIMIT; i > 0; i--) {
        printf("|");
        if (i <= hydrogen_amount)
            printf("H  ");
        else
            printf("   ");
        if (i <= oxygen_amount)
            printf("   O");
        else
            printf("    ");

        if (i == OXYGEN_LIMIT)
            printf("|  Oxigênios aguardando ligação: %d\n", oxygen_amount);
        else if (i == OXYGEN_LIMIT - 1)
            printf("|  Hidrogênios aguardando ligação: %d\n", hydrogen_amount);
        else
            printf("|\n");
    }
    printf("~~~~~~~~~\n");
    printf("Moleculas de água geradas: %d\n", h2o_amount);
    printf("~~~~~~~~~\n");

    for (int i = 0; i < h2o_amount; i++) {
        printf("***H2O***\n");
    }

    printf("\n\n");
    pthread_mutex_unlock(&print_mutex);
}

void generate_h2o() {
    h2o_amount++;
    animation();
}

void* hydrogen_thread(void* v) {
    sleep(rand() % 2);

    pthread_mutex_lock(&mutex);
    hydrogen_amount += 1;
    animation();

    if (hydrogen_amount >= 2 && oxygen_amount >= 1) {
        sem_post(&sem_hydrogen);
        sem_post(&sem_hydrogen);
        hydrogen_amount -= 2;
        sem_post(&sem_oxygen);
        oxygen_amount -= 1;
    } else {
        pthread_mutex_unlock(&mutex);
    }

    sem_wait(&sem_hydrogen);
    pthread_barrier_wait(&barrier);
}

void* oxygen_thread(void* v) {
    sleep(rand() % 2);

    pthread_mutex_lock(&mutex);
    oxygen_amount += 1;
    animation();

    if (hydrogen_amount >= 2) {
        sem_post(&sem_hydrogen);
        sem_post(&sem_hydrogen);
        hydrogen_amount -= 2;
        sem_post(&sem_oxygen);
        oxygen_amount -= 1;
    } else {
        pthread_mutex_unlock(&mutex);
    }

    sem_wait(&sem_oxygen);
    generate_h2o();
    pthread_barrier_wait(&barrier);
    pthread_mutex_unlock(&mutex);
}

int main() {
    pthread_t thr_oxy[OXYGEN_LIMIT];
    pthread_t thr_hydro[HYDROGEN_LIMIT];

    sem_init(&sem_hydrogen, 0, 0);
    sem_init(&sem_oxygen, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&print_mutex, NULL);
    pthread_barrier_init(&barrier, NULL, 3);

    for (int i = 0; i < OXYGEN_LIMIT; i++) {
        pthread_create(&thr_oxy[i], NULL, oxygen_thread, NULL);
    }
    for (int i = 0; i < HYDROGEN_LIMIT; i++) {
        pthread_create(&thr_hydro[i], NULL, hydrogen_thread, NULL);
    }

    for (int i = 0; i < OXYGEN_LIMIT; i++) {
        pthread_join(thr_oxy[i], NULL);
    }
    for (int i = 0; i < HYDROGEN_LIMIT; i++) {
        pthread_join(thr_hydro[i], NULL);
    }

    return 0;
}
