#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "comparadores.h"
#include "../formas/forma.h"
#include "../estruturas/ABB.h"
#include "svg.h"

typedef enum{
    SS,
    BS,
    IS,
    SHS,
    QS,
    MS
}ALGORITMO;

void ordenar(FORMA vet[], int n, int k, ALGORITMO algoritmo, ComparadorForma comparar, SVG svg, ARVORE banco);

#endif