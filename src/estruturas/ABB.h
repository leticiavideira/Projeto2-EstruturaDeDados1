#ifndef ABB_H
#define ABB_H

#include "../formas/forma.h"

typedef void* ARVORE;

ARVORE criarArvore();

void pushArvore (ARVORE a, FORMA f);

FORMA buscaIdArvore (ARVORE a, int id);

FORMA popIdArvore (ARVORE a, int id);

void percorrerArvore (ARVORE a);

int arvoreParaVetor (ARVORE a, FORMA vet[]);

int tamanhoArvore (ARVORE a);

int arvoreVazia (ARVORE a);

void limparArvore (ARVORE a);

void killArvore (ARVORE a);

int obterMaiorIdArvore(ARVORE arv);

#endif