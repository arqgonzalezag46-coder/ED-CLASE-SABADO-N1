#include <stdio.h>
#include <stdlib.h>

int main() {
    // --- Memoria estática ---
    int numeros[5];  
    printf("=== MEMORIA ESTÁTICA ===\n");
    for (int i = 0; i < 5; i++) {
        numeros[i] = i * 10;
        printf("numeros[%d] = %d\n", i, numeros[i]);
    }

    // --- Memoria dinámica ---
    int n;
    printf("\n=== MEMORIA DINÁMICA ===\n");
    printf("Ingrese el tamaño del arreglo: ");
    scanf("%d", &n);

    int *dinamico = (int*) malloc(n * sizeof(int)); 
    if (dinamico == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        dinamico[i] = i * 10;
        printf("dinamico[%d] = %d\n", i, dinamico[i]);
    }

    free(dinamico); 
    printf("\nMemoria dinámica liberada correctamente.\n");

    return 0;
}
