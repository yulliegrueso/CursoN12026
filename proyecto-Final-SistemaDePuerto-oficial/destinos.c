#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "destinos.h"
#include "pasajero.h" 
#include "avl.h"

Destino* crear_destino(int codigo, const char *nombre, const char *empresa) {
    Destino *nuevo = (Destino*) malloc(sizeof(Destino));
    if (!nuevo) {
        printf("Error al asignar memoria para el destino.\n");
        return NULL;
    }
    nuevo->codigo = codigo;
    strncpy(nuevo->nombre, nombre, sizeof(nuevo->nombre) - 1);
    strncpy(nuevo->empresa, empresa, sizeof(nuevo->empresa) - 1);
    nuevo->nombre[sizeof(nuevo->nombre) - 1] = '\0';
    nuevo->empresa[sizeof(nuevo->empresa) - 1] = '\0';
    
    inicializarCola(&(nuevo->cola_pasajeros));
    nuevo->raiz_viajes = NULL;
    nuevo->siguiente = NULL;

    return nuevo;
}

void agregar_destino(Destino **cabeza, int codigo, const char *nombre, const char *empresa) {
    if (buscar_destino_por_codigo(*cabeza, codigo) != NULL) {
        printf("Error: Ya existe un destino con el código %d.\n", codigo);
        return;
    }

    Destino *nuevo = crear_destino(codigo, nombre, empresa);
    if (!nuevo) return;

    if (*cabeza == NULL) {
        *cabeza = nuevo;
    } else {
        Destino *actual = *cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    printf("Destino '%s' registrado exitosamente.\n", nombre);
}

Destino* buscar_destino_por_codigo(Destino *cabeza, int codigo) {
    Destino *actual = cabeza;
    while (actual != NULL) {
        if (actual->codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

void mostrar_destinos(Destino *cabeza) {
    if (cabeza == NULL) {
        printf("No hay destinos registrados.\n");
        return;
    }

    printf("\n=== LISTA DE DESTINOS REGISTRADOS ===\n");
    Destino *actual = cabeza;
    while (actual != NULL) {
        printf("Código: %d | Nombre: %s | Empresa: %s | Pasajeros en espera: %d\n",
               actual->codigo, actual->nombre, actual->empresa,
               contar_pasajeros_en_espera(actual));
        actual = actual->siguiente;
    }
    printf("=====================================\n");
}

void modificar_destino(Destino *destino, const char *nuevo_nombre, const char *nueva_empresa) {
    if (destino == NULL) return;
    if (strlen(nuevo_nombre) > 0) {
        strncpy(destino->nombre, nuevo_nombre, sizeof(destino->nombre) - 1);
    }
    if (strlen(nueva_empresa) > 0) {
        strncpy(destino->empresa, nueva_empresa, sizeof(destino->empresa) - 1);
    }
    printf("Datos del destino actualizados con éxito.\n");
}

int contar_pasajeros_en_espera(Destino *destino) {
    if (!destino) return 0;
    return contarPasajerosCola(&(destino->cola_pasajeros));
}


void liberar_destinos(Destino *cabeza) {
    Destino *actual = cabeza;
    while (actual != NULL) {
        Destino *temp = actual;
        actual = actual->siguiente;

        
        liberarCola(&(temp->cola_pasajeros));
        
        
        liberaravl(temp->raiz_viajes);

        free(temp);
    }
}