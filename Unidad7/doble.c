#include <stdio.h>

#define MAX 50  // capacidad máxima simulada

// Estructura del nodo
typedef struct {
    char apellido[30];
    int ant;  // índice del nodo anterior
    int sig;  // índice del nodo siguiente
} Nodo;

// Variables globales
Nodo memoria[MAX];   // bloque de memoria simulada
int cab = -1;        // inicio de la lista
int libre = 0;       // próximo espacio libre
int capacidad = 0;
int vendidos = 0;
int abordados = 0;

// Prototipos
void establecer();
void vender();
void abordar();
void verAbordados();
void verNoAbordados();

int main() {
    int opc;
    do {
        printf("\n=== MENU PRINCIPAL DOBLE.C ===\n");
        printf("1. Establecer capacidad del avion\n");
        printf("2. Vender tiquete\n");
        printf("3. Iniciar abordaje\n");
        printf("4. Ver abordados\n");
        printf("5. Ver no abordados\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: establecer(); break;
            case 2: vender(); break;
            case 3: abordar(); break;
            case 4: verAbordados(); break;
            case 5: verNoAbordados(); break;
            case 6: printf("\nSaliendo del programa...\n"); break;
            default: printf("\nOpcion invalida.\n"); break;
        }
    } while (opc != 6);

    return 0;
}

// -------------------------------------------------------------
// 1. Establecer capacidad
void establecer() {
    if (capacidad > 0) {
        printf("\nLa capacidad ya fue establecida: %d asientos.\n", capacidad);
        return;
    }
    printf("\nIngrese la capacidad del avion (max %d): ", MAX);
    scanf("%d", &capacidad);

    if (capacidad <= 0 || capacidad > MAX) {
        printf("Capacidad invalida.\n");
        capacidad = 0;
    } else {
        printf("Capacidad establecida correctamente.\n");
    }
}

// -------------------------------------------------------------
// 2. Vender tiquete (crear "nodo" en memoria simulada)
void vender() {
    if (capacidad == 0) {
        printf("\nPrimero debe establecer la capacidad del avion.\n");
        return;
    }
    if (vendidos >= capacidad) {
        printf("\nTodos los tiquetes han sido vendidos.\n");
        return;
    }

    printf("\nIngrese el apellido del pasajero: ");
    scanf("%s", memoria[libre].apellido);

    memoria[libre].ant = -1;
    memoria[libre].sig = -1;

    if (cab == -1) {
        cab = libre;
    } else {
        int temp = cab;
        while (memoria[temp].sig != -1)
            temp = memoria[temp].sig;
        memoria[temp].sig = libre;
        memoria[libre].ant = temp;
    }

    libre++;
    vendidos++;
    printf("Tiquete vendido correctamente.\n");
}

// -------------------------------------------------------------
// 3. Abordar pasajeros
void abordar() {
    if (vendidos == 0) {
        printf("\nNo hay pasajeros para abordar.\n");
        return;
    }

    int temp = cab;
    while (temp != -1) {
        char r;
        printf("¿El pasajero %s abordo? (s/n): ", memoria[temp].apellido);
        scanf(" %c", &r);
        if (r == 's' || r == 'S') {
            abordados++;
        }
        temp = memoria[temp].sig;
    }
    printf("\nAbordaje completado.\n");
}

// -------------------------------------------------------------
// 4. Ver abordados
void verAbordados() {
    if (abordados == 0)
        printf("\nNingun pasajero ha abordado.\n");
    else
        printf("\nTotal abordados: %d\n", abordados);
}

// -------------------------------------------------------------
// 5. Ver no abordados
void verNoAbordados() {
    if (vendidos == 0)
        printf("\nNo se han vendido tiquetes.\n");
    else
        printf("\nTotal no abordados: %d\n", vendidos - abordados);
}
