#include <stdio.h>
#include <stdlib.h>
#include "pasajero.h"

void inicializar_cola(ColaPasajeros *cola) {
    if (cola != NULL) {
        cola->frente = NULL;
        cola->final = NULL;
    }
}

int colaVacia(Pasajero *frente) {
    return (frente == NULL);
}

Pasajero* crearPasajero(int documento, int tipoDocumento) {
    // Validar tipo de documento permitido (1: Cédula, 2: Pasaporte, 3: Tarjeta de Identidad)
    if (tipoDocumento < 1 || tipoDocumento > 3) {
        printf("Error: Tipo de documento inválido (%d). Permitidos: 1 (C.C), 2 (Pasaporte), 3 (T.I).\n", tipoDocumento);
        return NULL;
    }

    Pasajero* nuevoPasajero = (Pasajero*)malloc(sizeof(Pasajero));
    if (nuevoPasajero == NULL) {
        printf("Error al asignar memoria para el pasajero.\n");
        return NULL;
    }

    nuevoPasajero->documento = documento;
    nuevoPasajero->tipoDocumento = tipoDocumento;
    nuevoPasajero->estado = 0; // 0: En espera
    nuevoPasajero->siguiente = NULL;

    return nuevoPasajero;
}

int registrarPasajero(ColaPasajeros *cola, int documento, int tipoDocumento) {
    if (cola == NULL) return 0;

    Pasajero *nuevo = crearPasajero(documento, tipoDocumento);
    if (nuevo == NULL) return 0;

    if (colaVacia(cola->frente)) {
        cola->frente = nuevo;
        cola->final = nuevo;
    } else {
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }

    printf("Pasajero con documento %d registrado en la cola correctamente.\n", documento);
    return 1;
}

Pasajero* buscarPasajero(Pasajero *frente, int documento) {
    Pasajero *actual = frente;
    while (actual != NULL) {
        if (actual->documento == documento) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

Pasajero* consultarPrimero(Pasajero *frente) {
    return frente;
}

void mostrarPasajeros(Pasajero *frente) {
    Pasajero *actual = frente;

    if (actual == NULL) {
        printf("No hay pasajeros en la cola.\n");
        return;
    }

    printf("\n--- Pasajeros en la cola ---\n");
    while (actual != NULL) {
        char *tipoStr = (actual->tipoDocumento == 1) ? "Cédula de Ciudadanía" :
                        (actual->tipoDocumento == 2) ? "Pasaporte" : "Tarjeta de Identidad";

        printf("Documento: %d | Tipo: %s | Estado: %s\n",
               actual->documento,
               tipoStr,
               actual->estado == 0 ? "En espera" : "Embarcado");

        actual = actual->siguiente;
    }
    printf("----------------------------\n");
}

int contarPasajerosCola(ColaPasajeros *cola) {
    if (cola == NULL) return 0;

    int contador = 0;
    Pasajero *actual = cola->frente;

    while (actual != NULL) {
        if (actual->estado == 0) {
            contador++;
        }
        actual = actual->siguiente;
    }

    return contador;
}


int embarcarPasajero(ColaPasajeros *cola) {
    if (cola == NULL || colaVacia(cola->frente)) {
        printf("No hay pasajeros en espera para embarcar.\n");
        return 0;
    }

    Pasajero *pasajeroAEmbarcar = cola->frente;
    
    
    cola->frente = cola->frente->siguiente;

    if (cola->frente == NULL) {
        cola->final = NULL; 
    }

    printf("Pasajero con documento %d ha sido embarcado exitosamente.\n", pasajeroAEmbarcar->documento);

    free(pasajeroAEmbarcar); 
    return 1;
}

void liberarCola(ColaPasajeros *cola) {
    if (cola == NULL) return;

    Pasajero *actual = cola->frente;
    while (actual != NULL) {
        Pasajero *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    cola->frente = NULL;
    cola->final = NULL;
}