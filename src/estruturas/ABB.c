#include <stdio.h>
#include <stdlib.h>

#include "ABB.h"

#include "../gerais/comparadores.h"
#include "../formas/forma.h"


typedef struct No{
    FORMA forma;
    struct No* esq;
    struct No* dir;
} No;

typedef struct {
    No* raiz;
    int tamanho;
} StArvore;

/* ======================== FUNÇÕES AUXILIARES ======================== */
static No* criarNo(FORMA f);
static No* inserirNo(No *raiz, FORMA f);
static FORMA buscaIdNo(No *raiz, int id);
static No* removerNo(No *raiz, FORMA f, FORMA *removida);
static No* maiorEsquerda(No *raiz);
static void destruirNos(No *raiz);
static void copiarEmOrdem(No *raiz, FORMA vet[], int *pos);

/* ======================== FUNÇÕES PRINCIPAIS ======================== */

ARVORE criarArvore();

void pushArvore (ARVORE a, FORMA f) {

}

FORMA buscaIdArvore (ARVORE a, int id);

FORMA popIdArvore (ARVORE a, int id);

void percorrerArvore (ARVORE a);

int arvoreParaVetor (ARVORE a, FORMA vet[]);

int tamanhoArvore (ARVORE a);

int arvoreVazia (ARVORE a);

void limparArvore (ARVORE a);

void killArvore (ARVORE a);

/* ======================== IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ======================== */
static No* criarNo(FORMA f){
    if (f == NULL)
        return NULL;

    No *novo = malloc (sizeof (No));
        if(novo == NULL)
            return NULL;
    
    novo->forma = f;
    novo->dir = NULL;
    novo->esq = NULL;

    return novo;
}

static No* inserirNo(No *raiz, FORMA f) {
    if (f == NULL)
        return NULL;
    if (raiz == NULL)
        return criarNo (f);

    int cmp = comparaDefault (f, raiz->forma);

    if (cmp < 0){
        raiz->esq = inserirNo (raiz->esq, f);

    } else if (cmp > 0){
        raiz->dir = inserirNo (raiz->dir, f);
    }

    return raiz;
}

static FORMA buscaIdNo(No *raiz, int id){
    if (raiz == NULL)
        return NULL;

    if (getIdForma(raiz->forma) == id)
        return raiz->forma;

    FORMA achou = buscaIdNo (raiz->esq, id);

    if (achou != NULL)
        return achou;

    return buscaIdNo (raiz->dir, id);


}
static No* removerNo(No *raiz, FORMA f, FORMA *removida){
    if (raiz == NULL || f == NULL || removida == NULL)
        return NULL;

    int cmp = comparaDefault (f, raiz->forma);

    if (cmp < 0){
        raiz->esq = removerNo (raiz->esq, f, removida);
        return raiz;
    }

    if (cmp > 0){
        raiz->dir = removerNo (raiz->dir, f, removida);
        return raiz;
    }
    *removida = raiz->forma;

    // Para folha
    if (raiz->esq == NULL && raiz->dir == NULL){
        free (raiz);
        return NULL;
    }
    
    //Para apenas filho direito
    if (raiz->esq == NULL){
        No *aux = raiz->dir;
        free(raiz);
        return aux;
    }

    // Para apenas filho esquerdo
    if (raiz->dir == NULL){
        No *aux = raiz->esq;
        free(raiz);
        return aux;
    }

    //Para 2 filhos
    No *pred = maiorEsquerda(raiz->esq);
    raiz->forma = pred->forma;
    FORMA lixo;
    raiz->esq = removerNo (raiz->esq, pred->forma, &lixo);
    return raiz;

}

static No* maiorEsquerda(No *raiz) {
    if (raiz == NULL)
        return NULL;

    while (raiz->dir != NULL)
        raiz = raiz->dir;

    return raiz;
}

static void destruirNos(No *raiz) {
    if (raiz == NULL)
        return;

    destruirNos (raiz->esq);
    destruirNos (raiz->dir);

    free (raiz);
}

static void copiarEmOrdem(No *raiz, FORMA vet[], int *pos) {
    if (raiz == NULL)
        return;
    
    copiarEmOrdem (raiz->esq, vet, pos);
    vet[*pos] = raiz->forma;
    (*pos)++;

    copiarEmOrdem (raiz->dir, vet, pos);
}
