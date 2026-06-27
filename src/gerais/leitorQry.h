#ifndef LEITOR_QRY_H
#define LEITOR_QRY_H

#include "../estruturas/ABB.h"

#include "leitorDeArquivos.h"
#include "svg.h"

typedef void* LEITOR_QRY;

LEITOR_QRY criarLeitorQry(char *dirSaida, DadosArquivo geo, DadosArquivo qry, ARVORE banco, SVG svg);

void executarQry(LEITOR_QRY leitor);

void destruirLeitorQry(LEITOR_QRY leitor);

#endif