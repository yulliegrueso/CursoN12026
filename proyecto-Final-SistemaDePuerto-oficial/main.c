#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "destinos.h"
#include "pasajero.h"
#include "avl.h"
#include "reportes.h"

void mostrarMenu() {
    printf("\n===============================================\n");
    printf("   SISTEMA DE GESTION DE TERMINAL PORTUARIO   \n");
    printf("===============================================\n");
    printf("1. Registrar nuevo viaje (Insertar en AVL)\n");
    printf("2. Registrar pasajero en cola de espera (FIFO)\n");
    printf("3. Procesar / Embarcar siguiente pasajero\n");
    printf("4. Consultar viajes disponibles (Recorrido AVL)\n");
    printf("5. Generar reportes y estadisticas del puerto\n");
    printf("6. Salir\n");
    printf("===============================================\n");
    printf("Seleccione una opcion: ");
}

int main() {
    // 1. Crear las estructuras principales
    NodoAVL *arbolViajes = NULL;
    ColaPasajeros colaPuerto;
    inicializarCola(&colaPuerto);

    // 2. Puente con el modulo de reportes
    Destino *puertoPrincipal = crear_destino(1, "Terminal Principal", "Puerto C");

    int opcion = 0;

    do {
        mostrarMenu();

        if (scanf("%d", &opcion) != 1) {
            printf("\n[ERROR] Entrada invalida. Ingrese un numero entero.\n");
            while (getchar() != '\n'); // Limpiar el buffer si ingresan texto
            continue;
        }

        switch (opcion) {
            case 1: {
                int codigo = 0;
                int capacidad = 0;
                
                printf("\n--- REGISTRO DE NUEVO VIAJE ---\n");
                printf("Ingrese el codigo del viaje: ");
                scanf("%d", &codigo);
                printf("Ingrese la capacidad maxima de pasajeros: ");
                scanf("%d", &capacidad);

                if (capacidad <= 0) {
                    printf("[ERROR] La capacidad debe ser mayor a 0.\n");
                } else {
                    arbolViajes = insertar(arbolViajes, codigo, capacidad);
                    if (puertoPrincipal != NULL) {
                        puertoPrincipal->raiz_viajes = arbolViajes; 
                    }
                    printf("[OK] Viaje %d registrado exitosamente en el arbol AVL.\n", codigo);
                }
                break;
            }

            case 2: {
                printf("\n--- REGISTRO DE PASAJERO EN ESPERA ---\n");
                int tipoDocumento = 0;
                long long documento = 0; // Previene Integer Overflow en documentos largos

                printf("Ingrese el tipo de documento (1: CC, 2: TI, 3: PASAPORTE): ");
                scanf("%d", &tipoDocumento);
                printf("Ingrese el numero de documento (solo numeros): ");
                scanf("%lld", &documento);

                // Llamada a tu función de pasajero.h
                registrarPasajero(&colaPuerto, (int)documento, tipoDocumento);
                
                if (puertoPrincipal != NULL) {
                    puertoPrincipal->cola_pasajeros = colaPuerto;
                }
                break;
            }

            case 3: {
                printf("\n--- EMBARCAR / PROCESAR PASAJERO ---\n");
                
                if (contarPasajerosCola(&colaPuerto) == 0) {
                    printf("[INFO] No hay pasajeros actualmente en la cola de espera.\n");
                } else if (arbolViajes == NULL) {
                    printf("[ERROR] No hay viajes registrados en el sistema AVL para embarcar al pasajero.\n");
                } else {
                    Pasajero p;
                    if (embarcarPasajero(&colaPuerto)) {
                        printf("[OK] Pasajero con documento %d procesado y embarcado exitosamente.\n", p.documento);
                        if (arbolViajes != NULL) {
                            arbolViajes->pasajeros_embarcados++;
                        }
                    } else {
                        printf("[INFO] Pasajero procesado de la cola de espera.\n");
                    }

                    if (puertoPrincipal != NULL) {
                        puertoPrincipal->cola_pasajeros = colaPuerto;
                    }
                }
                break;
            }

            case 4: {
                printf("\n--- LISTADO DE VIAJES DISPONIBLES (INORDEN) ---\n");
                if (arbolViajes == NULL) {
                    printf("[INFO] No hay viajes registrados actualmente en el sistema.\n");
                } else {
                    mostrartodoslosviajes(arbolViajes);
                }
                break;
            }

            case 5: {
                printf("\n--- REPORTES Y ESTADISTICAS DEL PUERTO ---\n");
                
                if (puertoPrincipal != NULL) {
                    puertoPrincipal->raiz_viajes = arbolViajes;
                    puertoPrincipal->cola_pasajeros = colaPuerto;
                    
                    mostrar_reporte_estadistico(puertoPrincipal);
                } else {
                    printf("[ERROR] No se pudieron generar las estadisticas.\n");
                }
                break;
            }

            case 6:
                printf("\nSaliendo del sistema portuario... ¡Hasta luego!\n");
                break;

            default:
                printf("\n[OPCION INVALIDA] Seleccione un numero entre 1 y 6.\n");
        }

    } while (opcion != 6);

    // Liberación de memoria con los nombres exactos de tus headers
    liberaravl(arbolViajes);
    liberarCola(&colaPuerto); // Nombre exacto: liberarCola (camelCase)
    if (puertoPrincipal != NULL) {
        free(puertoPrincipal);
    }

    return 0;
}