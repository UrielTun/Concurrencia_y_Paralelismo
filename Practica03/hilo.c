// Docente: Sergio Andres Noh Puch
// 09 de Septiembre del 2026

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int totalPuntos = 100000000;
int numHilos;
int puntosDentro = 0;

pthread_mutex_t mutex;

float random_rango(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

void* hilo(void* arg) {
    float x, y;
    int iteraciones = totalPuntos / numHilos;
    int localDentro = 0;

    for (int i = 0; i < iteraciones; i++) {
        x = random_rango(-1.0, 1.0);
        y = random_rango(-1.0, 1.0);

        if (x * x + y * y <= 1.0) {
            localDentro++;
        }
    }

    pthread_mutex_lock(&mutex);
    puntosDentro += localDentro;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Uso: %s <numero_de_hilos>\n", argv[0]);
        return 1;
    }

    numHilos = atoi(argv[1]);

    if (numHilos <= 0) {
        printf("El numero de hilos debe ser mayor que 0.\n");
        return 1;
    }

    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);

    pthread_t hilos[numHilos];

    // Inicio del cronometro
    struct timespec inicio, fin;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    for (int i = 0; i < numHilos; i++) {
        pthread_create(&hilos[i], NULL, hilo, NULL);
    }

    for (int i = 0; i < numHilos; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Fin del cronometro
    clock_gettime(CLOCK_MONOTONIC, &fin);

    pthread_mutex_destroy(&mutex);

    double tiempo = (fin.tv_sec - inicio.tv_sec) +
                    (fin.tv_nsec - inicio.tv_nsec) / 1000000000.0;

    double pi = 4.0 * puntosDentro / totalPuntos;

    printf("\nResultado:\n");
    printf("--------------------------------\n");
    printf("Puntos: %d\n", puntosDentro);
    printf("Pi: %f\n", pi);
    printf("Hilos: %d\n", numHilos);
    printf("Tiempo: %.6f segundos\n", tiempo);

    return 0;
}