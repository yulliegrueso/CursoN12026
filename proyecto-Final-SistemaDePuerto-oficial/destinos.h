#ifndef DESTINOS_H
#define DESTINOS_H

#include "pasajero.h"
#include "avl.h"


typedef struct Destino {
    int codigo;
    char nombre[50];
    char empresa[50];
    
    ColaPasajeros cola_pasajeros; 
    NodoAVL *raiz_viajes;          
    
    struct Destino *siguiente;     
} Destino;

Destino* crear_destino(int codigo, const char *nombre, const char *empresa);
void agregar_destino(Destino **cabeza, int codigo, const char *nombre, const char *empresa);
Destino* buscar_destino_por_codigo(Destino *cabeza, int codigo);
void mostrar_destinos(Destino *cabeza);
void modificar_destino(Destino *destino, const char *nuevo_nombre, const char *nueva_empresa);
int contar_pasajeros_en_espera(Destino *destino);
void liberar_destinos(Destino *cabeza);

#endif 