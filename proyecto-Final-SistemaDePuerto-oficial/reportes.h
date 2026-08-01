#ifndef REPORTES_H
#define REPORTES_H

#include "destinos.h"

typedef struct {
    int total_registrados;
    int total_embarcados;
    int total_en_espera;
    double promedio_espera_por_destino;
    Destino *destino_mayor_espera;
    Destino *destino_menor_espera;
} EstadisticasGlobales;

void calcular_estadisticas_globales(Destino *lista_destinos, EstadisticasGlobales *est);
void mostrar_reporte_estadistico(Destino *lista_destinos);
void mostrar_resumen_operativo(Destino *lista_destinos);

#endif