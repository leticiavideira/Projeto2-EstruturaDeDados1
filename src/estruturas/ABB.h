#ifndef ABB_H
#define ABB_H

#include "../formas/forma.h"

typedef void* ARVORE;

ARVORE criarArvore();

void pushArvore (ARVORE a, FORMA f);

FORMA buscaIdArvore (ARVORE a, int id);

FORMA removerIdArvore (ARVORE a, int id);

int tamanhoArvore (ARVORE a);

int arvoreVazia (ARVORE a);

void limparArvore (ARVORE a);

void killArvore (ARVORE a);

#endif