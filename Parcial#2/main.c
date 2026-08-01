#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nodo de la cola
typedef struct NodoCola{
    char documento[20];
    int tiempoProcesamiento;
    struct NodoCola *sig;
}NodoCola;

// Nodo de la pila
typedef struct NodoPila{
    char documento[20];
    char usuario[30];
    char clave[30];
    struct NodoPila *sig;
}NodoPila;


NodoCola *frente=NULL;
NodoCola *fin=NULL;

NodoPila *tope=NULL;


int esNumero(char cadena[]){

    int i;

    for(i=0; cadena[i] != '\0'; i++){

        if(cadena[i] < '0' || cadena[i] > '9'){
            return 0;
        }

    }

    return 1;
}
int existeDocumento(char documento[]){

    NodoCola *auxCola;
    NodoPila *auxPila;

    auxCola = frente;

    while(auxCola != NULL){

        if(strcmp(auxCola->documento, documento) == 0){
            return 1;
        }

        auxCola = auxCola->sig;
    }

    auxPila = tope;

    while(auxPila != NULL){

        if(strcmp(auxPila->documento, documento) == 0){
            return 1;
        }

        auxPila = auxPila->sig;
    }

    return 0;
}


// Registrar solicitud
void registrar(){

    NodoCola *nuevo;
    int tiempoProcesamiento;
    
    nuevo=(NodoCola*)malloc(sizeof(NodoCola));

    if(nuevo==NULL){
        printf("\nError al reservar memoria.\n");
        return;
    }

    printf("\nNumero de documento: ");
    scanf("%19s", nuevo->documento);

    // VALIDAR QUE SOLO TENGA NUMEROS
    if(!esNumero(nuevo->documento)){

        printf("\nError: el documento solo debe contener numeros.\n");

        free(nuevo);
        return;
    }

    // VALIDAR QUE NO EXISTA
    if(existeDocumento(nuevo->documento)){

        printf("\nError: el documento ya existe.\n");

        free(nuevo);
        return;
    }

    nuevo->sig=NULL;

    if(frente==NULL){

        frente=nuevo;
        fin=nuevo;

    }else{

        fin->sig=nuevo;
        fin=nuevo;

    }

    printf("\nTiempo de procesamiento (en minutos): ");
    scanf("%d", &nuevo->tiempoProcesamiento);


    printf("\nSolicitud registrada correctamente.\n");
}

// Mostrar el tiempo promedio
void tiempoPromedio(){
    NodoCola *nuevo;

    if(frente==NULL){

        printf("\nNo existen solicitudes.\n");
        return;

    }

    else{

        int suma=0, contador=0;
        float promedioMinutos, promedioHoras;

        nuevo=frente;

        while(nuevo!=NULL){

            suma+=nuevo->tiempoProcesamiento;
            contador++;

            nuevo=nuevo->sig;

        }

        promedioMinutos=(float)suma/contador;
        promedioHoras=(float)promedioMinutos/60;

        printf("\nTiempo promedio de procesamiento: %.1f minutos\n", promedioMinutos);
        printf("Tiempo promedio de procesamiento: %.1f horas\n", promedioHoras);
    }
}

// Mostrar cola
void mostrarCola(){
    NodoCola *aux;

    if(frente==NULL){

        printf("\nNo existen solicitudes.\n");
        return;

    }

    aux=frente;

    printf("\n===== SOLICITUDES =====\n");

    while(aux!=NULL){

        printf("Documento: %s\n",aux->documento);
        printf("Tiempo de procesamiento: %d minutos\n", aux->tiempoProcesamiento);
            
        aux=aux->sig;

    }

}

// Sacar el primer estudiante

NodoCola* retirar(){

    NodoCola *aux;

    if(frente==NULL){

        return NULL;

    }

    aux=frente;

    frente=frente->sig;

    if(frente==NULL){

        fin=NULL;

    }

    aux->sig=NULL;

    return aux;

}

// Liberar cola

void liberarCola(){

    NodoCola *aux;

    while(frente!=NULL){

        aux=frente;

        frente=frente->sig;

        free(aux);

    }

    fin=NULL;

}


// FUNCIONES DE LA PILA


// Crear usuario y contraseña

void push(char documento[]){

    NodoPila *nuevo;

    nuevo=(NodoPila*)malloc(sizeof(NodoPila));

    if(nuevo==NULL){

        printf("\nError al reservar memoria.\n");
        return;

    }

    strcpy(nuevo->documento, documento);

    sprintf(nuevo->usuario,"U%s",documento);

    sprintf(nuevo->clave,"C%s",documento);

    nuevo->sig=tope;

    tope=nuevo;

    printf("\nCredencial creada correctamente.\n");
    printf("Usuario: %s\n",nuevo->usuario);
    printf("Clave: %s\n",nuevo->clave);

}

// Atender estudiante

void atenderEstudiante(){

    NodoCola *aux;

    aux=retirar();

    if(aux==NULL){

        printf("\nNo existen solicitudes pendientes.\n");
        return;

    }

    printf("\nAtendiendo estudiante...\n");
    printf("Documento: %s\n",aux->documento);

    push(aux->documento);

    free(aux);

}

// Consultar última credencial

void consultarCredencial(){

    if(tope==NULL){

        printf("\nNo existen credenciales.\n");
        return;

    }

    printf("\n===== ULTIMA CREDENCIAL =====\n");

    printf("Documento: %s\n",tope->documento);
    printf("Usuario: %s\n",tope->usuario);
    printf("Clave: %s\n",tope->clave);

}

// Retirar última credencial

void retirarCredencial(){

    NodoPila *aux;

    if(tope==NULL){

        printf("\nNo existen credenciales.\n");
        return;

    }

    aux=tope;

    printf("\nCredencial eliminada.\n");
    printf("Documento: %s\n",aux->documento);

    tope=tope->sig;

    free(aux);

}

// Mostrar todas las credenciales

void mostrarCredenciales(){

    NodoPila *aux;

    if(tope==NULL){

        printf("\nNo existen credenciales almacenadas.\n");
        return;

    }

    aux=tope;

    printf("\n===== CREDENCIALES =====\n");

    while(aux!=NULL){

        printf("\nDocumento: %s\n",aux->documento);
        printf("Usuario: %s\n",aux->usuario);
        printf("Clave: %s\n",aux->clave);

        aux=aux->sig;

    }

}

// Liberar pila

void liberarPila(){

    NodoPila *aux;

    while(tope!=NULL){

        aux=tope;

        tope=tope->sig;

        free(aux);

    }

}

int main(){
    int opcion;    
    do {

        printf("\n===== MENU =====\n");
        printf("1. Registrar solicitud\n");
        printf("2. Mostrar solicitudes\n");
        printf("3. Atender estudiante\n");
        printf("4. Consultar ultima credencial\n");
        printf("5. Retirar ultima credencial\n");
        printf("6. Mostrar todas las credenciales\n");
        printf("7. Mostrar el tiempo promedio de registros\n");
        printf("8. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion){
            case 1:
                registrar();
                break;
            case 2:
                mostrarCola();
                break;
            case 3:
                atenderEstudiante();
                break;
            case 4:
                consultarCredencial();
                break;
            case 5:
                retirarCredencial();
                break;
            case 6:
                mostrarCredenciales();
                break;
            case 7:
                tiempoPromedio();
                break;
            case 8:
                liberarCola();
                liberarPila();
                printf("\nSaliendo del programa...\n");
                break;
            default:
                printf("\nOpcion invalida.\n");
        }
    } while(opcion != 8);
return 0;    
}