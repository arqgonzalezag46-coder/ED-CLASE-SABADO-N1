#include <stdio.h>

int main() {
    int numeros[10];  

    printf("=== MEMORIA ESTÁTICA ===\n");
    printf("Arreglo de 10 enteros (memoria fija):\n");

    for (int i = 0; i < 10; i++) {
        numeros[i] = (i + 1) * 5;
        printf("numeros[%d] = %d\n", i, numeros[i]);
    }

    printf("\n--- Reflexión ---\n");
    printf("1. El tamaño del arreglo está definido en compilación.\n");
    printf("2. La memoria se almacena en el stack.\n");
    printf("3. Se libera automáticamente al finalizar la función.\n");
    printf("4. Es rápida, pero no se puede modificar su tamaño.\n");

    return 0;
}