#ifndef avl.h
#define avl.h


tyoedef struct viaje {

    int codigoViaje;
    int capacidadMaxima;
    int alturaMaxima;


    struct viaje *izquierda;
    struct viaje *derecha;


    
    viaje;
}

viaje *crearnodo(int codigoViaje, int capacidadMaxima);


int alturamaxima(viaje *nodo);
int maximo(int a, int b);
int obtenerBalance(viaje *nodo);


viaje *rotarderecha (viaje *y);
viaje *rotarizquierda(viaje *x);


viaje *insertar (viaje *raiz, int codigoViaje, int capacidadMaxima);
viaje *buscarviaje(viaje *raiz, int codigoViaje);
viaje *eliminarviaje(viaje *raiz, int codigoViaje);


void mostrartodoslosviajes(viaje *raiz);
void preorden(viaje *raiz);
void postorden(viaje *raiz);


viaje minimoValorNodo(viaje *nodo);
void liberaravl(viaje *raiz);

#endif 
