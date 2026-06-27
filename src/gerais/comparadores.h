#ifndef COMPARADORES_H
#define COMPARADORES_H

#include "../formas/forma.h"

/*
    return -1;  // a vem antes de b
    return 0;   // a e b são equivalentes
    return 1;   // a vem depois de b
*/

typedef enum{
    DEFAULT,
    AREA,
    LARGURA,
    ALTURA,
    COR
}CRITERIO;

typedef int (*ComparadorForma)(FORMA, FORMA);

int comparaDefault(FORMA a, FORMA b);

int comparaArea(FORMA a, FORMA b);

int comparaLargura(FORMA a, FORMA b);

int comparaAltura(FORMA a, FORMA b);

int comparaCor(FORMA a, FORMA b);

ComparadorForma obterComparador(CRITERIO crit);

#endif