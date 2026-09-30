#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int totalPuntos = 1000000;

float random_rango(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

int main() {
    srand(time(NULL));
    int puntosDentro = 0;

    // Un solo bucle secuencial en un único núcleo
    for (int i = 0; i < totalPuntos; i++) {
        float x = random_rango(-1.0, 1.0);
        float y = random_rango(-1.0, 1.0);

        if (x * x + y * y <= 1.0) {
            puntosDentro++;
        }
    }

    double pi = 4.0 * puntosDentro / totalPuntos;
    printf("Pi (SISD): %f\n", pi);
    return 0;
}