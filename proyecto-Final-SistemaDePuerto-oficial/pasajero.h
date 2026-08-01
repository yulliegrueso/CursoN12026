#ifndef PASAJERO_H
#define PASAJERO_H

typedef struct Pasajero {
    int documento;
    int tipoDocumento; 
    int estado;        
    struct Pasajero *siguiente;
} Pasajero;

typedef struct ColaPasajeros {
    Pasajero *frente;
    Pasajero *final;
} ColaPasajeros;

void inicializar_cola(ColaPasajeros *cola);
int colaVacia(Pasajero *frente);
Pasajero* crearPasajero(int documento, int tipoDocumento);
int registrarPasajero(ColaPasajeros *cola, int documento, int tipoDocumento);
Pasajero* buscarPasajero(Pasajero *frente, int documento);
Pasajero* consultarPrimero(Pasajero *frente);
void mostrarPasajeros(Pasajero *frente);
int contarPasajerosCola(ColaPasajeros *cola);
int embarcarPasajero(ColaPasajeros *cola);
void liberarCola(ColaPasajeros *cola);

#endif 