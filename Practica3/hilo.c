// Alumno: Pedro Alejandro Chavez Rivero - Concurrencia y Paralelismo
// Docente: Sergio Andres Noh Puch
// 09 de Septiembre del 2026
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int totalPuntos = 1000000;
int numHilos = 4;
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

        if (x*x + y*y <= 1.0) {
            localDentro++;
        }
    }

    pthread_mutex_lock(&mutex);
    puntosDentro += localDentro;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    pthread_t hilos[numHilos];

    for (int i = 0; i < numHilos; i++) {
        pthread_create(&hilos[i], NULL, hilo, NULL);
    }

    for (int i = 0; i < numHilos; i++) {
        pthread_join(hilos[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    double pi = 4.0 * puntosDentro / totalPuntos;

	printf("Resultado: \n");
	printf("--------------------------------\n");
	printf("\n");
    printf("Puntos: %d\n", puntosDentro);
    printf("\n");
    printf("Pi: %f\n", pi);

    return 0;
}