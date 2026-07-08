#include <stdio.h>
#include <string.h>

#include "comparadores.h"

#include "../formas/forma.h"

int comparaDefault(FORMA a, FORMA b){
    if (a == NULL || b == NULL)
        return 0;

    if (getYForma(a) < getYForma(b))
        return -1;

    if (getYForma(a) > getYForma(b))
        return 1;

    if (getXForma(a) < getXForma(b))
        return -1;

    if (getXForma(a) > getXForma(b))
        return 1;

    if (getAreaForma(a) < getAreaForma(b))
        return -1;

    if (getAreaForma(a) > getAreaForma(b))
        return 1;

    return 0;
}

int comparaArea(FORMA a, FORMA b){
    if(a == NULL || b == NULL)
        return 0;

    double areaA = getAreaForma (a);
    double areaB = getAreaForma (b);

    if (areaA < areaB)
        return -1;

    if (areaA > areaB)
        return 1;

    return 0;
}

int comparaLargura(FORMA a, FORMA b){
    if(a == NULL || b == NULL)
        return 0;

    double lA = getLarguraForma (a);
    double lB = getLarguraForma (b);

    if (lA < lB)
        return -1;
    
    if (lA > lB)
        return 1;

    return 0;
}

int comparaAltura(FORMA a, FORMA b){
    if(a == NULL || b == NULL)
        return 0;

    double hA = getAlturaForma (a);
    double hB = getAlturaForma (b);

    if (hA < hB)
        return -1;

    if (hA > hB)
        return 1;

    return 0;
}

int comparaCor(FORMA a, FORMA b){
    if(a == NULL || b == NULL)
        return 0;

    char *corA = getCorPreenchimentoForma(a);
    char *corB = getCorPreenchimentoForma(b);

    if(corA == NULL && corB == NULL)
        return 0;

    if(corA == NULL)
        return -1;

    if(corB == NULL)
        return 1;

    int cmp = strcmp(corA, corB);

    if(cmp < 0)
        return -1;

    if(cmp > 0)
        return 1;

    return 0;
}

ComparadorForma obterComparador(CRITERIO crit){
    switch (crit)
    {
        case DEFAULT:
            return comparaDefault;

        case AREA:
            return comparaArea;

        case LARGURA:
            return comparaLargura;

        case ALTURA:
            return comparaAltura;

        case COR:
            return comparaCor;
    }

    return comparaDefault;
}