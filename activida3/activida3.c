#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LASTNAME 110
#define MAX_DOCNUM 16

typedef struct Passenger {
    char doc_type[4];
    char doc_number[MAX_DOCNUM];
    char last_name[MAX_LASTNAME];
    struct Passenger* next;
} Passenger;

typedef struct {
    Passenger* head;
    int size;
} List;

void init_list(List* l) {
    l->head = NULL;
    l->size = 0;
}

int valid_doc_type(const char* s) {
    return strcmp(s, "CC") == 0 || strcmp(s, "TI") == 0 || strcmp(s, "PA") == 0;
}

int valid_lastname(const char* s) {
    if (strlen(s) < 1 || strlen(s) >= MAX_LASTNAME) return 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isalpha(s[i])) return 0;
    }
    return 1;
}

int agregar_pasajero(List* l, const char* doc_type, const char* doc_number, const char* last_name) {
    Passenger* nuevo = (Passenger*)malloc(sizeof(Passenger));
    if (!nuevo) return 0;
    strcpy(nuevo->doc_type, doc_type);
    strcpy(nuevo->doc_number, doc_number);
    strcpy(nuevo->last_name, last_name);
    nuevo->next = NULL;

    if (l->head == NULL) {
        l->head = nuevo;
    } else {
        Passenger* actual = l->head;
        while (actual->next) actual = actual->next;
        actual->next = nuevo;
    }
    l->size++;
    return 1;
}

void print_list(List* l) {
    if (!l->head) {
        printf("No hay pasajeros registrados.\n");
        return;
    }
    printf("Lista de pasajeros:\n");
    Passenger* cur = l->head;
    int i = 1;
    while (cur) {
        printf("%d) %s | %s | %s\n", i, cur->doc_type, cur->doc_number, cur->last_name);
        cur = cur->next;
        i++;
    }
}

Passenger* eliminar_primero(List* l) {
    if (!l->head) return NULL;
    Passenger* temp = l->head;
    l->head = l->head->next;
    temp->next = NULL;
    l->size--;
    return temp;
}

void liberar_lista(List* l) {
    Passenger* cur = l->head;
    while (cur) {
        Passenger* temp = cur;
        cur = cur->next;
        free(temp);
    }
    l->head = NULL;
    l->size = 0;
}

void read_line(char* buffer, int size) {
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
}

int main() {
    List lista;
    init_list(&lista);

    int capacidad;
    printf("Ingrese la capacidad maxima del avion: ");
    scanf("%d", &capacidad);
    while (getchar() != '\n');

    int extra = capacidad / 10; // 10% overbooking
    int max_tiquetes = capacidad + extra;
    printf("Capacidad real: %d\nOverbooking permitido: %d\nTotal maximo: %d\n\n",
           capacidad, extra, max_tiquetes);

    int vendidos = 0, abordados = 0;
    int opcion;

    do {
        printf("\n--- Menu ---\n");
        printf("1) Registrar pasajero\n");
        printf("2) Mostrar pasajeros\n");
        printf("3) Abordar siguiente\n");
        printf("4) Abordar todos hasta llenar avion\n");
        printf("5) Mostrar estado del vuelo\n");
        printf("6) Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n');

        if (opcion == 1) {
            if (vendidos >= max_tiquetes) {
                printf("No se pueden registrar mas pasajeros.\n");
                continue;
            }
            char tipo[4], numero[MAX_DOCNUM], apellido[MAX_LASTNAME];
            do {
                printf("Tipo de documento (CC, TI, PA): ");
                read_line(tipo, sizeof(tipo));
            } while (!valid_doc_type(tipo));

            printf("Numero de documento: ");
            read_line(numero, sizeof(numero));

            do {
                printf("Primer apellido: ");
                read_line(apellido, sizeof(apellido));
            } while (!valid_lastname(apellido));

            if (agregar_pasajero(&lista, tipo, numero, apellido)) {
                vendidos++;
                printf("Pasajero registrado.\n");
            } else {
                printf("Error al registrar pasajero.\n");
            }

        } else if (opcion == 2) {
            print_list(&lista);

        } else if (opcion == 3) {
            if (abordados >= capacidad) {
                printf("El avion ya esta lleno.\n");
                continue;
            }
            Passenger* p = eliminar_primero(&lista);
            if (!p) {
                printf("No hay pasajeros para abordar.\n");
            } else {
                printf("Abordando: %s | %s | %s\n", p->doc_type, p->doc_number, p->last_name);
                free(p);
                abordados++;
            }

        } else if (opcion == 4) {
            int count = 0;
            while (abordados < capacidad && lista.size > 0) {
                Passenger* p = eliminar_primero(&lista);
                printf("Abordando: %s | %s | %s\n", p->doc_type, p->doc_number, p->last_name);
                free(p);
                abordados++;
                count++;
            }
            if (count == 0) printf("No hay pasajeros para abordar.\n");
            else printf("%d pasajeros abordaron.\n", count);

        } else if (opcion == 5) {
            printf("Estado actual del vuelo:\n");
            printf("Capacidad real: %d\n", capacidad);
            printf("Maximo con overbooking: %d\n", max_tiquetes);
            printf("Registrados: %d\n", vendidos);
            printf("Abordados: %d\n", abordados);
            printf("En espera: %d\n", lista.size);

        } else if (opcion == 6) {
            printf("Liberando memoria y saliendo...\n");
            liberar_lista(&lista);
            break;
        } else {
            printf("Opcion invalida.\n");
        }

    } while (1);

    return 0;
}