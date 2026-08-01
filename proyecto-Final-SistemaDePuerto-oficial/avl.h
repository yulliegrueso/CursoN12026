#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct viaje {
    int codigoViaje;
    int capacidadMaxima;
    int pasajeros_embarcados; 
    int alturaMaxima;
    struct viaje *izquierda;
    struct viaje *derecha;
} viaje, NodoAVL;

// Prototipos de funciones
NodoAVL *crearnodo(int codigoViaje, int capacidadMaxima);
int alturamaxima(NodoAVL *nodo);
int obtenerBalance(NodoAVL *nodo);
NodoAVL *rotarderecha(NodoAVL *y);
NodoAVL *rotarizquierda(NodoAVL *x);
NodoAVL *insertar(NodoAVL *raiz, int codigoViaje, int capacidadMaxima);
NodoAVL *buscarviaje(NodoAVL *raiz, int codigoViaje);
NodoAVL *eliminarviaje(NodoAVL *raiz, int codigoViaje);
void mostrartodoslosviajes(NodoAVL *raiz);
void preorden(NodoAVL *raiz);
void postorden(NodoAVL *raiz);
NodoAVL minimoValorNodo(NodoAVL *nodo);
void liberaravl(NodoAVL *raiz);

#endif 