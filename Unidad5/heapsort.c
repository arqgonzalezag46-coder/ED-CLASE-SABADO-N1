#include <stdio.h>

// Función heapify: asegura la propiedad de montículo en el subárbol en i
void heapify(int arr[], int n, int i) {
    int largest = i;         // Inicializar como raíz
    int left = 2 * i + 1;    // Hijo izquierdo
    int right = 2 * i + 2;   // Hijo derecho

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

// Función de Heap Sort
void heapSort(int arr[], int n) {
    // Construir el montículo (heap)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extraer elementos del montículo uno por uno
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main() {
    int data[] = {20, 3, 15, 7, 9, 1, 11};
    int n = sizeof(data) / sizeof(data[0]);

    heapSort(data, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return 0;
}

