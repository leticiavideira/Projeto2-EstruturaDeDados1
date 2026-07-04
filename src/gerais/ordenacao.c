#include <stdio.h>

#include "ordenacao.h"


/* ======================== FUNÇÕES AUXILIARES ======================== */
static void troca(FORMA *a, FORMA *b);

static void selectionSort(FORMA vet[], int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco);
static void bubbleSort(FORMA vet[], int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco);
static void insertionSort(FORMA vet[], int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco);
static void shellSort(FORMA vet[], int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco);
static void quickSort(FORMA vet[], int inicio, int fim, int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco);
static int particiona(FORMA vet[], int inicio, int fim, int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco);
static void mergeSort(FORMA vet[], int inicio, int fim, int k, ComparadorForma comparar, SVG svg, ARVORE banco);
static void merge(FORMA vet[], int inicio, int meio, int fim, int k, ComparadorForma comparar, SVG svg, ARVORE banco);

/* ======================== FUNÇÃO PRINCIPAL ======================== */

void ordenar(FORMA vet[], int n, int k, ALGORITMO algoritmo, ComparadorForma comparar, SVG svg, ARVORE banco){
    switch (algoritmo){
        case SS:
            selectionSort(vet, n, k, comparar, svg, banco);
            break;

        case BS:
            bubbleSort(vet, n, k, comparar, svg, banco);
            break;

        case IS:
            insertionSort(vet, n, k, comparar, svg, banco);
            break;

        case SHS:
            shellSort(vet, n, k, comparar, svg, banco);
            break;

        case QS:
            quickSort(vet, 0, n - 1, n, k, comparar, svg, banco);
            break;

        case MS:
            mergeSort(vet, 0, n - 1, k, comparar, svg, banco);
            break;
    }
}

/* ======================== IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ======================== */
static void troca(FORMA *a, FORMA *b){
    FORMA aux = *a;
    *a = *b;
    *b = aux;
}

static void selectionSort(FORMA vet[], int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco){
    for(int i = 0; i < n - 1; i++){

        int menor = i;

        for(int j = i + 1; j < n; j++){

            if(comparar(vet[j], vet[menor]) < 0)
                menor = j;
        }

        if(menor != i){
            troca(&vet[i], &vet[menor]);

            gerarSnapshotOrdenacao(svg, banco, vet, n);
        }
    }
}

static void bubbleSort(FORMA vet[], int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco){
    for(int i = 0; i < n - 1; i++){

        int trocou = 0;

        for(int j = 0; j < n - 1 - i; j++){

            if(comparar(vet[j + 1], vet[j]) < 0){

                troca(&vet[j], &vet[j+1]);

                trocou = 1;
   
                gerarSnapshotOrdenacao(svg,banco,vet,n);
            }
        }

        if(!trocou)
            break;
    }
}

static void insertionSort(FORMA vet[], int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco){
    for(int i = 1; i < n; i++){

        FORMA chave = vet[i];

        int j = i - 1;

        while(j >= 0 && comparar(chave, vet[j]) < 0){
            vet[j+1] = vet[j];

            j--;

            gerarSnapshotOrdenacao(svg,banco,vet,n);
        }

        vet[j+1] = chave;

        gerarSnapshotOrdenacao(svg,banco,vet,n);
    }
}

static void shellSort(FORMA vet[], int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco){
    for (int gap = n / 2; gap > 0; gap /= 2){

        for (int i = gap; i < n; i++){

            FORMA aux = vet[i];
            int j = i;

            while (j >= gap && comparar(aux, vet[j - gap]) < 0){
                vet[j] = vet[j - gap];
                gerarSnapshotOrdenacao(
                    svg,
                    banco,
                    vet,
                    n
                );
                j -= gap;
            }

            if (j != i){
                vet[j] = aux;
                gerarSnapshotOrdenacao(
                    svg,
                    banco,
                    vet,
                    n
                );
            }
        }
    }
}

static void quickSort(FORMA vet[], int inicio, int fim, int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco){
    if (inicio < fim){
        int p = particiona(vet, inicio, fim, n, k, comparar, svg, banco);

        quickSort(vet, inicio, p - 1, n, k, comparar, svg, banco);
        quickSort(vet, p + 1, fim, n, k, comparar, svg, banco);
    }
}

static int particiona(FORMA vet[], int inicio, int fim, int n, int k, ComparadorForma comparar, SVG svg, ARVORE banco){
    FORMA pivo = vet[fim];

    int i = inicio - 1;

    for (int j = inicio; j < fim; j++){

        if (comparar(vet[j], pivo) <= 0){
            i++;

            if (i != j){
                troca(&vet[i], &vet[j]);
                gerarSnapshotOrdenacao(
                    svg,
                    banco,
                    vet,
                    n
                );
            }
        }
    }

    if (i+1 !=  fim){
        troca(&vet[i + 1], &vet[fim]);
        gerarSnapshotOrdenacao(
            svg,
            banco,
            vet,
            n
        );
    }
    return i + 1;
}

static void mergeSort(FORMA vet[], int inicio, int fim, int k, ComparadorForma comparar, SVG svg, ARVORE banco){
    if (inicio >= fim)
        return;

    int meio = (inicio + fim) / 2;

    mergeSort(vet, inicio, meio, k, comparar, svg, banco);
    mergeSort(vet, meio + 1, fim, k, comparar, svg, banco);

    merge(vet, inicio, meio, fim, k, comparar, svg, banco);
}

static void merge(FORMA vet[], int inicio, int meio, int fim, int k, ComparadorForma comparar, SVG svg, ARVORE banco){
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    FORMA *esq = malloc(sizeof(FORMA)*n1);
    FORMA *dir = malloc(sizeof(FORMA)*n2);

    for (int i = 0; i < n1; i++)
        esq[i] = vet[inicio + i];

    for (int i = 0; i < n2; i++)
        dir[i] = vet[meio + 1 + i];

    int i = 0;
    int j = 0;
    int k = inicio;

    while (i < n1 && j < n2){

        if (comparar(esq[i], dir[j]) <= 0){
            vet[k++] = esq[i++];
            gerarSnapshotOrdenacao(
                svg,
                banco,
                vet,
                fim + 1
            );
            
        }else{
            vet[k++] = dir[j++];
            gerarSnapshotOrdenacao(
                svg,
                banco,
                vet,
                fim + 1
            );
        }
    }

    while (i < n1){
        vet[k++] = esq[i++];
        gerarSnapshotOrdenacao(
            svg,
            banco,
            vet,
            fim + 1
        );
    }

    while (j < n2){
        vet[k++] = dir[j++];
        gerarSnapshotOrdenacao(
            svg,
            banco,
            vet,
            fim + 1
        );
    }

    
    free(esq);
    free(dir);
}