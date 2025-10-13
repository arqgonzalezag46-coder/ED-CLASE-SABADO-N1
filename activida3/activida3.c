#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_APELLIDOS 110
#define MAX_DOCNUM 16
#define DOC_CC "CC"
#define DOC_TI "TI"
#define DOC_PA "PA" 

// Nodo para la lista enlazada de pasajeros
typedef struct passenger {
    char doc_type[4]; // tipo de documento CC, TI, PA
    char doc_number[MAX_DOCNUM]; // numero de documento
    char last_name[MAX_APELLIDOS]; // primer apellido
    struct passenger* next; // puntero al siguiente pasajero
} Passenger;

typedef struct {
    Passenger *head; // cabeza de la lista enlazada
    int size; // tamaño de la lista
} List;

// inicializar la lista
void init_list(List * l) {
    l->head = NULL;
    l->size = 0;
}
// validacion de tipo de documento
int valid_doc_type(const char *s) {
    return (strcmp(s, "CC") == 0 || strcmp(s, "TI") == 0 || strcmp(s, "PA") == 0);
}

// validar apellido
int valid_LastName(const char *s) {
if (strlen(s) < 1 || strlen(s) > ( MAX_APELLIDOS - 1)) {
    return 0;
}
for (int i = 0; s[i] != '\0'; i++) {
    if (!isalpha(s[i])) {
        return 0;
    }
}
return 1;
// agregar pasajero al final de la lista
int agregar_pasajero(List *l, const char *doc_type, const char *doc_number, const char *last_name) {
    // reservar memoria para el nuevo pasajero
    Passenger *nuevo = (Passenger*)malloc(sizeof(Passenger));
    if (!nuevo) 
        return 0; // error de memoria
        // copiar los datos del nodo
        strcpy(nuevo-> doc_type, doc_type);
        strcpy(nuevo-> doc_number, doc_number);
        strcpy(nuevo-> last_name, last_name);
        nuevo-> next = NULL;
        // si la lista esta vacia, el nuevo pasajero sera la cabeza
        if (l-> head ==NULL) {
            l-> head = nuevo;
        }
        else {
            // recorremos hasta el ultimo nodo
            Passenger *actual = l-> head;
            while (
                actual-> next != NULL
            ) {
            actual = actual-> next;

            }
            actual-> next = nuevo; // enlazamos el nuevo pasajero al final de la lista
        }
        // aumentar el tamaño de la lista
        l-> size++;
        return 1; // exito

        // mostrar la lista de pasajeros
        void print_list(List *l) {
            if (l-> head == NULL) {
                printf("No hay pasajero registrado en la lista: \n");
                return;
            }
            printf("Lista de pasajeros registrados: \n");
            Passenger *cur = l-> head;
            int i = 1;
            while (cur) {
                printf(" %2d) %s | %s | %s \n", i, cur-> doc_type, cur-> doc_number, cur-> last_name);
                cur = cur-> next;
                i++;

            }
        }
        // liberar espaicio en la memoria
        void liberar_lista(List *l) {
            Passenger *cur = l-> head;
            while (cur) {
                Passenger *temp = cur;
                cur = cur_next;
                free(temp);
            }
            l-> head= NULL;
            l-> size = 0;

        }

        // funcion principal
        int main() {
            List lista;
            init_list(&lista);

            int capacidad;
            printf("Sistema de Gestion de Pasajeros: \n");// lista enlazadas simples
            printf("Ingrese la capacidad maxima del avion: ");
            scnaf("%d", &capacidad);
            while (getchar() != '\n');

            int extra = (capacidad *10) / 100; // 10% de capacidad extra o overbooking
            int max_tiquetes = capacidad + extra;
            printf("Capacidad real: %d asientos \n", capacidad);
            printf("Overbooking permitido: %d \n", extra);
            printf("Total maximo de pasajeros que se pueden registrar: %d \n\n", max_tiquetes);
            
            int opcion;
            int vendidos = 0, abordados = 0;

            while (1) {
                printf("\n------Menu-----\n");
                printf("1) Registrar pasajeros\n");
                printf("2) Mostrar pasajeros registrados\n");
                printf("3) Abordar  siguente pasajero\n");
                printf("4) Abordar a todos hasta llenar el avion\n");
                printf("5) Mostrar estado actual del vuelo\n");
                printf("6) Salir\n");
                printf(" Opcion: ");
                scanf("%d", &opcion);
                while (getchar() != '\n');

                if (opcion == 1) {
                    if (vendidos >= max_tiquetes) {
                        printf("No se pueden registrar mas pasajeros. (Limite alcanzado)\n");
                        continue;

                    }

                    char tipo[4], numero[MAX_DOCNUM], apellido[MAX_APELLIDOS];

                    // Tipo de documento
                    printf("Numero de documento (CC, TI, PA): ");
                    read_line(numero, sizeof(numero));

                    // Apellido
                    printf("Primer apellido: ");
                    read_line(apellido, sizeof(apellido));

                    if (agregar_pasajero(&lista, tipo, numero, apellido)) {
                        vendidos++;
                        printf("Pasajero registrados exitosamente. \n");
                    } else {
                        printf("Error al reservar memoria. \n");
                    }

                    }
                }
                else if (opcion == 2) {
                    mostrar_lista(&lista);

                }
                else if (opcion == 3) {
                    if (abordados >= capacidad) {
                        printf("El avion ya esta lleno. \n");
                        continue;
                    }
                    Passenger *p = eliminar_primero(&lista);
                    if (abordados >= capacidad) {
                        printf("El avion ya esta lleno. \n");
                        continue;
                    }
                    Passsenger *p = eliminar_primero(&lista);
                    if (!p) {
                        printf("No hay pasajeros para abordar. \n");
                    } else {
                        abordados++;
                        printf("Abordando pasajeros: %s %s %s \n", p-> doc_number, p-> doc_type);
                        free(p);
                    }
                    
                    }
                    else if (opcion == 4) {
                        int count = 0;
                        while(abordados < caapacidad) {
                            Passenger *p = eliminaar_priimero(&lista);
                            if(!p)
                            break;
                            abordados++;
                            count++;
                            printf("abordando pasajeros: %s %s %s \n", p-> last_name, p-> doc_number, p-> doc_type);
                            
                            fee(p);

                        }
                        if (count == 0) 
                        printf("No hay pasajeros para abordar. \n");
                        else
                        printf("%d pasajeros abordanron. \n", count);

                    }
                    else if (opcion == 5) {
                        printf("\n Estado actual del vuelo: \n");
                        printf(" Capacidad real: %d\n", capacidad);
                        printf(" Maximo con overbooking: %d\n", max_tiquetes);
                        printf(" registrados: %d\n", vendidos);
                        printf(" Abordados: %d\n", abordados);
                        printf(" En espera: %d\n", lista.size);

                    }

                    else if (opcion == 6) {
                        printf(" Liberando memoria...\n");
                        liberar_lista(&lista);
                        printf(" Saliendo del sistema. \n");
                        break;

                    }
                    else {
                        printf("Opcion no valida. vuelva a intentarlo.\n");
                        
                    }
                }
                return 0;
            }

        }
    }
}