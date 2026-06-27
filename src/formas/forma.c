#include <stdio.h>
#include <stdlib.h>

#include "forma.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "estiloTexto.h"

typedef struct {
    FormaTipo tipo;
    void *data;
} FormaSt;

FORMA criarForma(FormaTipo tipo, void *data) {
    if (data == NULL)
        return NULL;
    FormaSt *f = malloc(sizeof(FormaSt));
    if (!f) exit(1);

    f->tipo = tipo;
    f->data = data;

    return f;
}

double getXForma (FORMA f){
    if (f == NULL)
        return -1;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {
        case FORMA_CIRCULO:
            return getX_C(forma->data);

        case FORMA_RETANGULO:
            return getX_R(forma->data);

        case FORMA_LINHA:
            return getX1_L(forma->data);

        case FORMA_TEXTO:
            return getX_T(forma->data);

        default:
            return -1;
    }
}

double getYForma (FORMA f) {
    if (f == NULL)
        return -1;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {
        case FORMA_CIRCULO:
            return getY_C(forma->data);

        case FORMA_RETANGULO:
            return getY_R(forma->data);

        case FORMA_LINHA:
            return getY1_L(forma->data);

        case FORMA_TEXTO:
            return getY_T(forma->data);

        default:
            return -1;
    }
}

double getAreaForma (FORMA f) {
    if (f == NULL)
        return -1;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {
        case FORMA_CIRCULO:
            return calcularArea_C(forma->data);

        case FORMA_RETANGULO:
            return calcularArea_R(forma->data);

        case FORMA_LINHA:
            return calcularArea_L(forma->data);

        case FORMA_TEXTO:
            return calcularArea_T(forma->data);

        default:
            return -1;
    }
}

double getLarguraForma (FORMA f){
    if (f == NULL)
        return -1;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {
        case FORMA_CIRCULO:
            return getLargura_C(forma->data);

        case FORMA_RETANGULO:
            return getW_R(forma->data);

        case FORMA_LINHA:
            return getLargura_L(forma->data);

        case FORMA_TEXTO:
            return getLargura_T(forma->data);

        default:
            return -1;
    }
}

double getAlturaForma (FORMA f){
    if (f == NULL)
        return -1;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {
        case FORMA_CIRCULO:
            return getAltura_C(forma->data);

        case FORMA_RETANGULO:
            return getH_R(forma->data);

        case FORMA_LINHA:
            return getAltura_L(forma->data);

        case FORMA_TEXTO:
            return getAltura_T(forma->data);

        default:
            return -1;
    }
}

char* getCorPreenchimentoForma (FORMA f){
    if (f == NULL)
        return -1;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {
        case FORMA_CIRCULO:
            return getCorP_C(forma->data);

        case FORMA_RETANGULO:
            return getCorP_R(forma->data);

        case FORMA_LINHA:
            return getCor_L(forma->data);

        case FORMA_TEXTO:
            return getCorp_T(forma->data);

        default:
            return -1;
    }
}

char* getCorBordaForma(FORMA f){
    if(f == NULL)
        return NULL;

    FormaSt *forma = (FormaSt*) f;

    switch(forma->tipo){

        case FORMA_CIRCULO:
            return getCorB_C(forma->data);

        case FORMA_RETANGULO:
            return getCorB_R(forma->data);

        case FORMA_LINHA:
            return getCor_L(forma->data);

        case FORMA_TEXTO:
            return getCorb_T(forma->data);

        default:
            return NULL;
    }
}

double getRaioForma(FORMA f){
    if(f == NULL)
        return -1;

    FormaSt *forma = (FormaSt*) f;

    if(forma->tipo == FORMA_CIRCULO)
        return getR_C(forma->data);

    return -1;
}

double getX2Forma(FORMA f){
    if(f == NULL)
        return -1;

    FormaSt *forma = (FormaSt*) f;

    if(forma->tipo == FORMA_LINHA)
        return getX2_L(forma->data);

    return -1;
}

double getY2Forma(FORMA f){
    if(f == NULL)
        return -1;

    FormaSt *forma = (FormaSt*) f;

    if(forma->tipo == FORMA_LINHA)
        return getY2_L(forma->data);

    return -1;
}

char getAncoraTextoForma(FORMA f){
    if(f == NULL)
        return '\0';

    FormaSt *forma = (FormaSt*) f;

    if(forma->tipo == FORMA_TEXTO)
        return getA_T(forma->data);

    return '\0';
}

char* getConteudoTextoForma(FORMA f){
    if(f == NULL)
        return NULL;

    FormaSt *forma = (FormaSt*) f;

    if(forma->tipo == FORMA_TEXTO)
        return getTxto_T(forma->data);

    return NULL;
}

char* getNomeForma (FORMA f) {
    if (f == NULL) 
        return NULL;

    switch (getTipoForma(f)) {
        case FORMA_CIRCULO:   return "circulo";
        case FORMA_RETANGULO: return "retangulo";
        case FORMA_LINHA:     return "linha";
        case FORMA_TEXTO:     return "texto";
        default:              return "desconhecido";
    }
}

int getIdForma(FORMA f) {
    if (f == NULL)
        return -1;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {
        case FORMA_CIRCULO:
            return getId_C(forma->data);

        case FORMA_RETANGULO:
            return getId_R(forma->data);

        case FORMA_LINHA:
            return getId_L(forma->data);

        case FORMA_TEXTO:
            return getId_T(forma->data);

        default:
            return -1;
    }
}

void getAncoraForma(FORMA f, double *x, double *y) {
    if (f == NULL)
        return;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {

        case FORMA_CIRCULO: {
            CIRCULO c = forma->data;
            *x = getX_C(c);
            *y = getY_C(c);
            break;
        }

        case FORMA_RETANGULO: {
            RETANGULO r = forma->data;
            *x = getX_R(r);
            *y = getY_R(r);
            break;
        }

        case FORMA_TEXTO: {
            TEXTO t = forma->data;
            *x = getX_T(t);
            *y = getY_T(t);
            break;
        }

        case FORMA_LINHA: {
            LINHA l = forma->data;

            double x1 = getX1_L(l);
            double y1 = getY1_L(l);
            double x2 = getX2_L(l);
            double y2 = getY2_L(l);

            // regra da âncora da linha
            if (x1 < x2 || (x1 == x2 && y1 <= y2)) {
                *x = x1;
                *y = y1;
            } else {
                *x = x2;
                *y = y2;
            }
            break;
        }

        default:
            *x = 0;
            *y = 0;
    }
}

FormaTipo getTipoForma(FORMA f) {
    if (f == NULL)
        return 0;
    return ((FormaSt*)f)->tipo;
}

void* getDataForma(FORMA f) {
    if (f == NULL)
        return NULL;
    return ((FormaSt*)f)->data;
}

void setIdForma(FORMA f, int id){

    if(f == NULL)
        return;

    FormaSt *forma = (FormaSt*) f;

    switch(forma->tipo){

        case FORMA_CIRCULO:
            setId_C(forma->data, id);
            break;

        case FORMA_RETANGULO:
            setId_R(forma->data, id);
            break;

        case FORMA_LINHA:
            setId_L(forma->data, id);
            break;

        case FORMA_TEXTO:
            setId_T(forma->data, id);
            break;

        default:
            break;
    }
}

void setCorBordaForma(FORMA f, char *cor) {
    if (f == NULL || cor == NULL)
        return;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {

        case FORMA_CIRCULO:
            setCorB_C(forma->data, cor);
            break;

        case FORMA_RETANGULO:
            setCorB_R(forma->data, cor);
            break;

        case FORMA_LINHA:
            setCor_L(forma->data, cor);
            break;

        case FORMA_TEXTO:
            setCorb_T(forma->data, cor);
            break;

        case FORMA_ESTILO_TEXTO:
            break;
    }
}

void setCorPreenchimentoForma(FORMA f, char *cor) {
    if (f == NULL || cor == NULL)
        return;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {

        case FORMA_CIRCULO:
            setCorP_C(forma->data, cor);
            break;

        case FORMA_RETANGULO:
            setCorP_R(forma->data, cor);
            break;

        case FORMA_TEXTO:
            setCorp_T(forma->data, cor);
            break;

        default:
            break; // linha não tem preenchimento
    }
}

void moverForma(FORMA f, double dx, double dy) {
    if (f == NULL)
        return;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {

        case FORMA_CIRCULO: {
            CIRCULO c = forma->data;
            setX_C(c, getX_C(c) + dx);
            setY_C(c, getY_C(c) + dy);
            break;
        }

        case FORMA_RETANGULO: {
            RETANGULO r = forma->data;
            setX_R(r, getX_R(r) + dx);
            setY_R(r, getY_R(r) + dy);
            break;
        }

        case FORMA_LINHA: {
            LINHA l = forma->data;
            setX1_L(l, getX1_L(l) + dx);
            setY1_L(l, getY1_L(l) + dy);
            setX2_L(l, getX2_L(l) + dx);
            setY2_L(l, getY2_L(l) + dy);
            break;
        }

        case FORMA_TEXTO: {
            TEXTO t = forma->data;
            setX_T(t, getX_T(t) + dx);
            setY_T(t, getY_T(t) + dy);
            break;
        }

        case FORMA_ESTILO_TEXTO:
            break;
    }
}

void printFormaTXT(FILE *txt, FORMA f) {
    if (txt == NULL || f == NULL)
        return;

    FormaTipo t = getTipoForma(f);

    if (t == FORMA_CIRCULO) {
        CIRCULO c = getDataForma(f);

        fprintf(txt, "   -> circulo id=%d x=%.2f y=%.2f r=%.2f corb=%s corp=%s\n",
            getId_C(c), getX_C(c), getY_C(c), getR_C(c),
            getCorB_C(c), getCorP_C(c));
    }

    else if (t == FORMA_RETANGULO) {
        RETANGULO r = getDataForma(f);

        fprintf(txt, "   -> retangulo id=%d x=%.2f y=%.2f w=%.2f h=%.2f corb=%s corp=%s\n",
            getId_R(r), getX_R(r), getY_R(r),
            getW_R(r), getH_R(r),
            getCorB_R(r), getCorP_R(r));
    }

    else if (t == FORMA_LINHA) {
        LINHA l = getDataForma(f);

        fprintf(txt, "   -> linha id=%d (%.2f,%.2f)-(%.2f,%.2f) cor=%s\n",
            getId_L(l),
            getX1_L(l), getY1_L(l),
            getX2_L(l), getY2_L(l),
            getCor_L(l));
    }

    else if (t == FORMA_TEXTO) {
        TEXTO t = getDataForma(f);

        fprintf(txt, "   -> texto id=%d x=%.2f y=%.2f txt=%s\n",
            getId_T(t),
            getX_T(t), getY_T(t),
            getTxto_T(t));
    }
}

void killForma(FORMA f) {
    if (f == NULL)
        return;
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {
        case FORMA_CIRCULO:
            kill_C(forma->data);
            break;

        case FORMA_RETANGULO:
            kill_R(forma->data);
            break;

        case FORMA_LINHA:
            kill_L(forma->data);
            break;

        case FORMA_TEXTO:
            kill_T(forma->data);
            break;

        case FORMA_ESTILO_TEXTO:
            killEstiloTexto(forma->data);
            break;
    }

    free(forma);
}