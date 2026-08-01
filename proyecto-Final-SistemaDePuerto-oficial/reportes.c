#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "reportes.h"

static void contar_embarcados_avl(NodoAVL *raiz, int *total_embarcados) {
    if (raiz == NULL) return;
    
    *total_embarcados += raiz->pasajeros_embarcados;
    
    contar_embarcados_avl(raiz->izquierda, total_embarcados);
    contar_embarcados_avl(raiz->derecha, total_embarcados);
}

void calcular_estadisticas_globales(Destino *lista_destinos, EstadisticasGlobales *est) {
    if (est == NULL) return;

    est->total_registrados = 0;
    est->total_embarcados = 0;
    est->total_en_espera = 0;
    est->promedio_espera_por_destino = 0.0;
    est->destino_mayor_espera = NULL;
    est->destino_menor_espera = NULL;

    if (lista_destinos == NULL) return;

    int num_destinos = 0;
    int max_espera = -1;
    int min_espera = INT_MAX;

    Destino *actual = lista_destinos;
    while (actual != NULL) {
        num_destinos++;
        int espera_actual = contar_pasajeros_en_espera(actual);
        est->total_en_espera += espera_actual;

        if (espera_actual > max_espera) {
            max_espera = espera_actual;
            est->destino_mayor_espera = actual;
        }

        if (espera_actual < min_espera) {
            min_espera = espera_actual;
            est->destino_menor_espera = actual;
        }

        contar_embarcados_avl(actual->raiz_viajes, &(est->total_embarcados));

        actual = actual->siguiente;
    }

    if (num_destinos > 0) {
        est->promedio_espera_por_destino = (double)est->total_en_espera / num_destinos;
    }
    
    est->total_registrados = est->total_en_espera + est->total_embarcados;
}

void mostrar_reporte_estadistico(Destino *lista_destinos) {
    EstadisticasGlobales est;
    calcular_estadisticas_globales(lista_destinos, &est);

    printf("\n========================================================\n");
    printf("     REPORTE ESTADISTICO Y METRICAS DEL TERMINAL       \n");
    printf("========================================================\n");
    
    if (lista_destinos == NULL) {
        printf(" No hay destinos registrados en el sistema actualmente.\n");
        printf("========================================================\n");
        return;
    }

    printf(" - Total de Pasajeros Registrados : %d\n", est.total_registrados);
    printf(" - Total de Pasajeros Embarcados  : %d\n", est.total_embarcados);
    printf(" - Total de Pasajeros en Espera   : %d\n", est.total_en_espera);
    printf(" - Promedio Espera por Destino    : %.2f pasajeros\n", est.promedio_espera_por_destino);
    printf("--------------------------------------------------------\n");
    
    if (est.destino_mayor_espera != NULL) {
        printf(" - Destino con MAYOR cola de espera : %s (Codigo: %d) [%d esperando]\n",
               est.destino_mayor_espera->nombre,
               est.destino_mayor_espera->codigo,
               contar_pasajeros_en_espera(est.destino_mayor_espera));
    }

    if (est.destino_menor_espera != NULL) {
        printf(" - Destino con MENOR cola de espera : %s (Codigo: %d) [%d esperando]\n",
               est.destino_menor_espera->nombre,
               est.destino_menor_espera->codigo,
               contar_pasajeros_en_espera(est.destino_menor_espera));
    }

    printf("========================================================\n\n");
}