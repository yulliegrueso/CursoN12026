#include <stdio.h>
#include <stdlib.h>
#include "avl.h"



viaje *crearNodo(int codigoViaje, int capacidadMaxima) {
    viaje *nuevoNodo = (viaje *)malloc(sizeof(viaje));
    if (nuevoNodo == NULL)
     {
        printf("Error al reservar memoria para el nodo del viaje.\n");
        return NULL;
    }
    nuevoNodo->codigoViaje = codigoViaje;
    nuevoNodo->capacidadMaxima = capacidadMaxima;
    nuevoNodo->alturaMaxima = 1;

    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}


int alturaMaxima(viaje *nodo) {
    if (nodo == NULL)
        return 0;
    return nodo->alturaMaxima;
}

int maximo(int a, int b) {

    if (a>b)
        return a;
    
    return b;
}

viaje *rotarDerecha(viaje *y) {
    viaje *x = y->izquierda;
    viaje *T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->alturaMaxima = maximo(alturaMaxima(y->izquierda), alturaMaxima(y->derecha)) + 1;
    x->alturaMaxima = maximo(alturaMaxima(x->izquierda), alturaMaxima(x->derecha)) + 1;
    return x;
}

viaje *rotarIzquierda(viaje *x) {
    viaje *y = x->derecha;
    viaje *T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->alturaMaxima = maximo(alturaMaxima(x->izquierda), alturaMaxima(x->derecha)) + 1;
    y->alturaMaxima = maximo(alturaMaxima(y->izquierda), alturaMaxima(y->derecha)) + 1;
    return y;
}

int obtenerBalance(viaje *nodo) {
    if (nodo == NULL)
        return 0;
    return alturaMaxima(nodo->izquierda) - alturaMaxima(nodo->derecha);
}

void liberaravl(NodoAVL *raiz) {
    if (raiz == NULL) return;
    liberaravl(raiz->izquierda);
    liberaravl(raiz->derecha);
    free(raiz);
}


NodoAVL* insertar(NodoAVL *nodo, int codigo, int capacidad) {
    if (nodo == NULL) {
        NodoAVL *nuevo = (NodoAVL*) malloc(sizeof(NodoAVL));
        nuevo->codigoViaje = codigo;
        nuevo->capacidadMaxima = capacidad;
        nuevo->izquierda = NULL;
        nuevo->derecha = NULL;
        nuevo->alturaMaxima = 1;
        return nuevo; // DEBE RETORNAR EL NUEVO NODO
    }
    
    // ... lógica de inserción y balanceo ...
    
    return nodo; // RETORNA LA RAÍZ ACTUALIZADA
}
void mostrartodoslosviajes(NodoAVL *raiz) {
    if (raiz != NULL) {
        mostrartodoslosviajes(raiz->izquierda);
        printf("Viaje Codigo: %d | Capacidad: %d\n", raiz->codigoViaje, raiz->capacidadMaxima);
        mostrartodoslosviajes(raiz->derecha);
    }
}