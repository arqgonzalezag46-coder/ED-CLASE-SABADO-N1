#include <stdio.h>

// Funcion heapify: asegura la propiedad de monticulo en el subarbol en i
void heapify(int arr[], int n, int i) {
    int largest = i;         // Inicializar como raiz
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

// Funcion de Heap Sort
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
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

    return 0;
}
