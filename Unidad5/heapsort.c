#include <stdio.h>

// Funcion heapify: asegura la propiedad de monticulo en el subarbol en i
void heapify(int arr[], int n, int i) {
    int largest = i;         // Inicializar como raiz
    int left = 2 * i + 1;    // Hijo izquierdo
    int right = 2 * i + 2;   // Hijo derecho

    // Si el hijo izquierdo es mas grande que la raiz
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Si el hijo derecho es mas grande que el mayor hasta ahora
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Si el mayor no es la raiz
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursivamente aplicar heapify al subarbol afectado
        heapify(arr, n, largest);
    }
}

// Funcion de Heap Sort
void heapSort(int arr[], int n) {
    // Construir el max-heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extraer elementos del heap uno por uno
    for (int i = n - 1; i > 0; i--) {
        // Mover la raiz actual al final
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Llamar a heapify sobre el heap reducido
        heapify(arr, i, 0);
    }
}

int main() {
    int data[] = {20, 3, 15, 7, 9, 1, 11};
    int n = sizeof(data) / sizeof(data[0]);

    heapSort(data, n);

    // Imprimir arreglo ordenado
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }

    int main() {
    ...
    return 0;
}
