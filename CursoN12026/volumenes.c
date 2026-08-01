#include "volumenes.h"

#define PI 3.1416

float volumenEsfera(float radio){
    return (4.0/3.0) * PI * radio * radio * radio;
}

float volumenCubo(float lado){
    return lado * lado * lado;
}