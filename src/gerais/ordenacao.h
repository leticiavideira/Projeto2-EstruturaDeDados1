#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "comparadores.h"
#include "../formas/forma.h"

typedef enum{
    SS,
    BS,
    IS,
    SHS,
    QS,
    MS
}ALGORITMO;

void ordenar(FORMA vet[], int n, ALGORITMO algoritmo, ComparadorForma comparar);

#endif