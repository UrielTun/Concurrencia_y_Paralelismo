#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_PUNTOS 1000000

int main() {
    // 1. Reservar memoria para los arreglos
    float *x = (float *)malloc(TOTAL_PUNTOS * sizeof(float));
    float *y = (float *)malloc(TOTAL_PUNTOS * sizeof(float));

    if (x == NULL || y == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    srand(time(NULL));

    // 2. Generar las coordenadas secuencialmente (fuera de la directiva SIMD)
    for (int i = 0; i < TOTAL_PUNTOS; i++) {
        x[i] = -1.0f + ((float)rand() / RAND_MAX) * 2.0f;
        y[i] = -1.0f + ((float)rand() / RAND_MAX) * 2.0f;
    }

    int puntosDentro = 0;

    // 3. Bucle vectorizado con SIMD
    #pragma omp simd reduction(+:puntosDentro)
    for (int i = 0; i < TOTAL_PUNTOS; i++) {
        if (x[i] * x[i] + y[i] * y[i] <= 1.0f) {
            puntosDentro++;
        }
    }

    // 4. Se asegura la conversión a flotante (double) para evitar división entera
    double pi = 4.0 * (double)puntosDentro / (double)TOTAL_PUNTOS;

    printf("Resultado SIMD:\n");
    printf("--------------------------------\n");
    printf("Puntos dentro: %d\n", puntosDentro);
    printf("Pi: %f\n", pi);

    free(x);
    free(y);

    return 0;
}