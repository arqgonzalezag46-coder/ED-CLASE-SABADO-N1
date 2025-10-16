#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_APELLIDO 100
#define GENDER_MAX 16

// Estructura del pasajero (lista doblemente enlazada)
typedef struct DPassenger {
    int id;
    char gender[GENDER_MAX];
    char surname[MAX_APELLIDO];
    struct DPassenger *next;
    struct DPassenger *prev;
} DPassenger;

// Listas para tiquetes vendidos y pasajeros abordados
DPassenger *sold_head = NULL, *sold_tail = NULL;
DPassenger *boarded_head = NULL, *boarded_tail = NULL;

// Variables globales de control
int capacity = 0;
int overbook_limit = 0;
int sold_count = 0;
int boarded_count = 0;
int boarding_started = 0;
int next_id = 1;

// Limpiar buffer de entrada
void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Establecer capacidad máxima del avión
void set_capacity() {
    if (capacity > 0) {
        printf("La capacidad ya fue establecida (%d).\n", capacity);
        return;
    }

    printf("Ingrese la capacidad máxima del avión: ");
    scanf("%d", &capacity);

    if (capacity <= 0) {
        printf("Capacidad inválida.\n");
        capacity = 0;
        return;
    }

    overbook_limit = capacity + (capacity * 10) / 100;
    printf("Capacidad establecida en %d pasajeros. Sobreventa permitida hasta %d.\n",
           capacity, overbook_limit);
}

// Agregar pasajero a la lista de vendidos
void push_sold(DPassenger *p) {
    if (!sold_head)
        sold_head = sold_tail = p;
    else {
        sold_tail->next = p;
        p->prev = sold_tail;
        sold_tail = p;
    }
}

// Extraer pasajero de la lista de vendidos
DPassenger *pop_sold() {
    if (!sold_head) return NULL;

    DPassenger *p = sold_head;
    sold_head = sold_head->next;

    if (sold_head)
        sold_head->prev = NULL;
    else
        sold_tail = NULL;

    p->next = p->prev = NULL;
    sold_count--;
    return p;
}

// Agregar pasajero a la lista de abordados
void push_boarded(DPassenger *p) {
    if (!boarded_head)
        boarded_head = boarded_tail = p;
    else {
        boarded_tail->next = p;
        p->prev = boarded_tail;
        boarded_tail = p;
    }
}

// Vender tiquete
void sell_ticket() {
    if (capacity == 0) {
        printf("Primero establezca la capacidad.\n");
        return;
    }
    if (boarding_started) {
        printf("No se pueden vender tiquetes: el abordaje ya inició.\n");
        return;
    }
    if (sold_count >= overbook_limit) {
        printf("Se alcanzó el límite de sobreventa.\n");
        return;
    }

    clear_input();
    char gender[GENDER_MAX], surname[MAX_APELLIDO];

    printf("Ingrese género (Femenino/Masculino/NoBinario): ");
    fgets(gender, sizeof(gender), stdin);
    gender[strcspn(gender, "\n")] = '\0';

    printf("Ingrese primer apellido: ");
    fgets(surname, sizeof(surname), stdin);
    surname[strcspn(surname, "\n")] = '\0';

    DPassenger *p = (DPassenger *)malloc(sizeof(DPassenger));
    p->id = next_id++;
    strcpy(p->gender, gender);
    strcpy(p->surname, surname);
    p->next = p->prev = NULL;

    push_sold(p);
    sold_count++;

    printf("Tiquete vendido exitosamente (ID %d).\n", p->id);
}

// Iniciar abordaje
void start_boarding() {
    if (capacity == 0) {
        printf("Primero establezca la capacidad.\n");
        return;
    }
    if (boarding_started) {
        printf("El abordaje ya inició.\n");
        return;
    }

    boarding_started = 1;
    printf("Iniciando abordaje...\n");

    while (boarded_count < capacity) {
        DPassenger *p = pop_sold();
        if (!p) break;
        push_boarded(p);
        boarded_count++;
        printf("Pasajero %s abordó.\n", p->surname);
    }

    printf("Abordaje completado. Total abordados: %d\n", boarded_count);
}

// Mostrar pasajeros abordados
void view_boarded() {
    if (!boarded_head) {
        printf("No hay pasajeros abordados.\n");
        return;
    }

    printf("\n=== Pasajeros Abordados ===\n");
    DPassenger *cur = boarded_head;
    while (cur) {
        printf("ID %d - %s - %s\n", cur->id, cur->surname, cur->gender);
        cur = cur->next;
    }
}

// Mostrar pasajeros que no abordaron
void view_not_boarded() {
    if (!sold_head) {
        printf("No hay pasajeros que no abordaron.\n");
        return;
    }

    printf("\n=== Pasajeros NO Abordados ===\n");
    DPassenger *cur = sold_head;
    while (cur) {
        printf("ID %d - %s - %s\n", cur->id, cur->surname, cur->gender);
        cur = cur->next;
    }
}

// Liberar toda la memoria dinámica usada
void free_all() {
    DPassenger *cur = sold_head;
    while (cur) {
        DPassenger *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    cur = boarded_head;
    while (cur) {
        DPassenger *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

// Programa principal
int main() {
    int opt;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Establecer capacidad\n");
        printf("2. Vender tiquete\n");
        printf("3. Iniciar abordaje\n");
        printf("4. Ver abordados\n");
        printf("5. Ver no abordados\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1: set_capacity(); break;
            case 2: sell_ticket(); break;
            case 3: start_boarding(); break;
            case 4: view_boarded(); break;
            case 5: view_not_boarded(); break;
            case 6: printf("Saliendo del programa...\n"); break;
            default: printf("Opción inválida.\n");
        }
    } while (opt != 6);

    free_all();
    return 0;
}