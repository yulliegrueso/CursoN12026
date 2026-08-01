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

