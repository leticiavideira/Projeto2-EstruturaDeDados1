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
} ArvoreSt;

/* ======================== FUNÇÕES AUXILIARES ======================== */
static No* criarNo(FORMA f);
static No* inserirNo(No *raiz, FORMA f);
static FORMA buscaIdNo(No *raiz, int id);
static No* removerNo(No *raiz, FORMA f, FORMA *removida);
static No* maiorEsquerda(No *raiz);
static void destruirNos(No *raiz);
static void copiarEmOrdem(No *raiz, FORMA vet[], int *pos);

/* ======================== FUNÇÕES PRINCIPAIS ======================== */

ARVORE criarArvore() {
    ArvoreSt *a = (ArvoreSt *) malloc (sizeof (ArvoreSt));
        if (a == NULL)
            return NULL;

    a->raiz = NULL;
    a->tamanho = 0;
    return a;
}

void pushArvore (ARVORE a, FORMA f) {
    if (a == NULL || f == NULL)
        return;
    ArvoreSt *a1 = (ArvoreSt *) a;
    a1->raiz = inserirNo(a1->raiz, f);
    a1->tamanho++;
}

FORMA buscaIdArvore (ARVORE a, int id){
    if (a == NULL)
        return NULL;

    ArvoreSt *a1 = (ArvoreSt *) a;
    return buscaIdNo (a1->raiz, id);
}

FORMA popIdArvore (ARVORE a, int id){
    if (a == NULL)
        return NULL;
    ArvoreSt *a1 = (ArvoreSt *) a;

    FORMA f = buscaIdNo (a1->raiz, id);
        if (f == NULL)
            return NULL;

    FORMA removida = NULL;

    a1->raiz = removerNo (a1->raiz, f, &removida);
    if (removida != NULL)
        a1->tamanho--;
    return removida;
}

void percorrerArvore (ARVORE a);

int arvoreParaVetor (ARVORE a, FORMA vet[]){
    if (a == NULL)
        return -1;

    ArvoreSt *a1 = (ArvoreSt *) a;
    int pos = 0;
    copiarEmOrdem (a1->raiz, vet, &pos);
    return pos;
}

int tamanhoArvore (ARVORE a){
    if (a == NULL)
        return -1;

    ArvoreSt *a1 = (ArvoreSt *) a;

    return a1->tamanho;
}

int arvoreVazia (ARVORE a){
    if (a == NULL)
        return -1;

    ArvoreSt *a1 = (ArvoreSt *) a;
    return a1->tamanho == 0;
}

void limparArvore (ARVORE a) {
    if (a == NULL)
        return;

    ArvoreSt *a1 = (ArvoreSt *) a;

    destruirNos (a1->raiz);

    a1->raiz = NULL;
    a1->tamanho = 0;
}

void killArvore (ARVORE a) {
    if (a == NULL)
        return;

    ArvoreSt *a1 = (ArvoreSt *) a;

    limparArvore (a1);
    free (a1);
}

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

// FORMA f nunca deve ser NULL
static No* inserirNo(No *raiz, FORMA f) {
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
// f e removida nunca poderão ser NULL
static No* removerNo(No *raiz, FORMA f, FORMA *removida){
    if (raiz == NULL)
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
    FORMA lixo = NULL;
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
    killForma (raiz->forma);

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
