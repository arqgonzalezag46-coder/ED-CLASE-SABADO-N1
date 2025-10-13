#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    char apellido[30];
    struct nodo *sig;
} nodo;

nodo *primero = NULL;
nodo *ultimo = NULL;  

int capacidad = 0;
int vendidos = 0;
int abordaje_iniciado = 0;
int maxVenta = 0;

void establecer();
void vender();
void iniciarAbordaje();
void verAbordados();
void verNoAbordados();
void liberarLista();

int main() {
    int opc;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Establecer capacidad\n");
        printf("2. Vender tiquete\n");
        printf("3. Iniciar abordaje\n");
        printf("4. Ver abordados\n");
        printf("5. Ver no abordados\n");
        printf("6. Salir\n");
        printf("Seleccione opcion: ");
        if (scanf("%d", &opc) != 1) { 
            while (getchar() != '\n');
            opc = 0;
        }
        switch(opc) {
            case 1: establecer(); break;
            case 2: vender(); break;
            case 3: iniciarAbordaje(); break;
            case 4: verAbordados(); break;
            case 5: verNoAbordados(); break;
            case 6: printf("Saliendo...\n"); break;
            default: if (opc!=6) printf("Opcion no valida.\n");
        }
    } while(opc != 6);

    liberarLista();
    return 0;
}

void establecer() {
    if (capacidad != 0) {
        printf("La capacidad ya fue establecida: %d\n", capacidad);
        return;
    }
    printf("Ingrese la capacidad maxima del avion: ");
    if (scanf("%d", &capacidad) != 1 || capacidad <= 0) {
        printf("Valor invalido.\n");
        capacidad = 0;
        while (getchar() != '\n');
        return;
    }
    maxVenta = capacidad + (capacidad * 10) / 100; 
    printf("Capacidad: %d. Maximo con sobreventa: %d\n", capacidad, maxVenta);
}

void vender() {
    if (capacidad == 0) {
        printf("Primero establezca la capacidad.\n");
        return;
    }
    if (abordaje_iniciado) {
        printf("No se pueden vender mas tiquetes. El abordaje ya inicio.\n");
        return;
    }
    if (vendidos >= maxVenta) {
        printf("Se alcanzo el limite de sobreventa (%d).\n", maxVenta);
        return;
    }

    char ape[30];
    printf("Ingrese el primer apellido del pasajero (sin espacios): ");
    if (scanf("%29s", ape) != 1) {
        printf("Entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }

    nodo *nuevo = (nodo*) malloc(sizeof(nodo));
    if (!nuevo) {
        printf("Error: memoria insuficiente.\n");
        return;
    }
    
    int i=0;
    while (ape[i] != '\0' && i < 29) { nuevo->apellido[i] = ape[i]; i++; }
    nuevo->apellido[i] = '\0';

    nuevo->sig = NULL;

    if (primero == NULL) { 
        primero = ultimo = nuevo;
    } else {
        ultimo->sig = nuevo;
        ultimo = nuevo;
    }

    vendidos++;
    printf("Tiquete vendido a %s. Total vendidos: %d\n", nuevo->apellido, vendidos);
}

void iniciarAbordaje() {
    if (capacidad == 0) {
        printf("Primero establezca la capacidad.\n");
        return;
    }
    if (abordaje_iniciado) {
        printf("El abordaje ya fue iniciado.\n");
        return;
    }
    if (vendidos == 0) {
        printf("No hay pasajeros para abordar.\n");
        return;
    }
    abordaje_iniciado = 1;
    printf("Abordaje iniciado. Solo suben %d pasajeros (capacidad).\n", capacidad);
}

void verAbordados() {
    if (!abordaje_iniciado) {
        printf("Aun no se ha iniciado el abordaje.\n");
        return;
    }
    printf("\n--- Pasajeros que abordaron ---\n");
    nodo *act = primero;
    int cont = 0;
    while (act != NULL && cont < capacidad) {
        printf("%d) %s\n", cont+1, act->apellido);
        act = act->sig;
        cont++;
    }
    if (cont==0) printf("(Ninguno)\n");
}

void verNoAbordados() {
    if (!abordaje_iniciado) {
        printf("Aun no se ha iniciado el abordaje.\n");
        return;
    }
    printf("\n--- Pasajeros que NO abordaron ---\n");
    nodo *act = primero;
    int cont = 0;
    while (act != NULL && cont < capacidad) {
        act = act->sig;
        cont++;
    }
    int idx = 0;
    while (act != NULL) {
        idx++;
        printf("%d) %s\n", idx, act->apellido);
        act = act->sig;
    }
    if (idx==0) printf("(Ninguno)\n");
}

void liberarLista() {
    nodo *tmp;
    while (primero != NULL) {
        tmp = primero;
        primero = primero->sig;
        free(tmp);
    }
    ultimo = NULL;
}
