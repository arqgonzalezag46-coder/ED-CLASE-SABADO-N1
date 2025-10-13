#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

typedef struct Passenger {
    char doc_number[20];
    char doc_type[20];
    char genero[20];
    char apellido[30];
    struct Passenger *sig;
} Passenger;

// Prototipos
void read_line(char *str, int n);
void establecer_capacidad(int *capacidad, int *max_venta);
Passenger* vender_tiquete(Passenger **head, int capacidad, int vendidos, int max_venta);
Passenger* eliminar_primero(Passenger **head);

int main() {
    Passenger *lista = NULL;
    int capacidad = 0, max_venta = 0, vendidos = 0, abordados = 0;
    int opcion;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Establecer capacidad del avion\n");
        printf("2. Vender tiquete\n");
        printf("3. Iniciar abordaje\n");
        printf("4. Ver pasajeros abordados\n");
        printf("5. Ver pasajeros no abordados\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        if (opcion == 1) {
            establecer_capacidad(&capacidad, &max_venta);
        }
        else if (opcion == 2) {
            Passenger *nuevo = vender_tiquete(&lista, capacidad, vendidos, max_venta);
            if (nuevo != NULL) {
                vendidos++;
                printf("🎫 Tiquete vendido correctamente (%d/%d)\n", vendidos, max_venta);
            }
        }
        else if (opcion == 3) {
            printf("\n--- Iniciando abordaje ---\n");
            while (abordados < capacidad && lista != NULL) {
                Passenger *p = eliminar_primero(&lista);
                if (p != NULL) {
                    printf("Abordando pasajero: %s %s, %s, %s\n", p->doc_type, p->doc_number, p->genero, p->apellido);
                    abordados++;
                    free(p);
                }
            }
            printf("\nAbordaje completado.\n");
        }
        else if (opcion == 4) {
            printf("\nTotal abordados: %d\n", abordados);
        }
        else if (opcion == 5) {
            printf("\nTotal no abordados: %d\n", vendidos - abordados);
        }
        else if (opcion == 6) {
            // liberar lista restante
            while (lista != NULL) {
                Passenger *p = eliminar_primero(&lista);
                free(p);
            }
            printf("Saliendo del programa...\n");
        }
        else {
            printf("Opcion invalida.\n");
        }

    } while (opcion != 6);

    return 0;
}

// -----------------------------
// Funciones auxiliares
// -----------------------------
void read_line(char *str, int n) {
    fgets(str, n, stdin);
    str[strcspn(str, "\n")] = 0;
}

void establecer_capacidad(int *capacidad, int *max_venta) {
    if (*capacidad > 0) {
        printf("La capacidad ya fue establecida: %d asientos.\n", *capacidad);
        return;
    }
    printf("Ingrese la capacidad del avion: ");
    scanf("%d", capacidad);
    getchar();
    *max_venta = *capacidad + (*capacidad / 10);
    printf("Capacidad establecida: %d pasajeros (+10%% sobreventa: %d total)\n", *capacidad, *max_venta);
}

Passenger* vender_tiquete(Passenger **head, int capacidad, int vendidos, int max_venta) {
    if (vendidos >= max_venta) {
        printf("No se pueden vender más tiquetes. Se alcanzó la sobreventa máxima.\n");
        return NULL;
    }

    Passenger *nuevo = (Passenger*) malloc(sizeof(Passenger));
    if (!nuevo) {
        printf("Error de memoria.\n");
        return NULL;
    }

    printf("Ingrese genero (Femenino/Masculino/No Binario): ");
    read_line(nuevo->genero, MAX_NAME);
    printf("Ingrese primer apellido: ");
    read_line(nuevo->apellido, MAX_NAME);
    printf("Ingrese tipo de documento: ");
    read_line(nuevo->doc_type, MAX_NAME);
    printf("Ingrese numero de documento: ");
    read_line(nuevo->doc_number, MAX_NAME);

    nuevo->sig = NULL;
    if (*head == NULL) {
        *head = nuevo;
    } else {
        Passenger *temp = *head;
        while (temp->sig != NULL)
            temp = temp->sig;
        temp->sig = nuevo;
    }
    return nuevo;
}

Passenger* eliminar_primero(Passenger **head) {
    if (*head == NULL) return NULL;
    Passenger *temp = *head;
    *head = (*head)->sig;
    return temp;
}