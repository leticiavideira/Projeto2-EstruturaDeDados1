#include <stdio.h>

#include "ordenacao.h"


/* ======================== FUNÇÕES AUXILIARES ======================== */
static void troca(FORMA *a, FORMA *b);

static void selectionSort(FORMA vet[], int n, ComparadorForma comparar);
static void bubbleSort(FORMA vet[], int n, ComparadorForma comparar);
static void insertionSort(FORMA vet[], int n, ComparadorForma comparar);
static void shellSort(FORMA vet[], int n, ComparadorForma comparar);
static void quickSort(FORMA vet[], int inicio, int fim, ComparadorForma comparar);
static int particiona(FORMA vet[], int inicio, int fim, ComparadorForma comparar);
static void mergeSort(FORMA vet[], int inicio, int fim, ComparadorForma comparar);
static void merge(FORMA vet[], int inicio, int meio, int fim, ComparadorForma comparar);

/* ======================== FUNÇÃO PRINCIPAL ======================== */

void ordenar(FORMA vet[], int n, ALGORITMO algoritmo, ComparadorForma comparar){
    switch (algoritmo){
        case SS:
            selectionSort(vet, n, comparar);
            break;

        case BS:
            bubbleSort(vet, n, comparar);
            break;

        case IS:
            insertionSort(vet, n, comparar);
            break;

        case SHS:
            shellSort(vet, n, comparar);
            break;

        case QS:
            quickSort(vet, 0, n - 1, comparar);
            break;

        case MS:
            mergeSort(vet, 0, n - 1, comparar);
            break;
    }
}

/* ======================== IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ======================== */
static void troca(FORMA *a, FORMA *b){
    FORMA aux = *a;
    *a = *b;
    *b = aux;
}

static void selectionSort(FORMA vet[], int n, ComparadorForma comparar){
    for (int i = 0; i < n - 1; i++){
        int menor = i;

        for (int j = i + 1; j < n; j++){
            if (comparar(vet[j], vet[menor]) < 0)
                menor = j;
        }

        if (menor != i)
            troca(&vet[i], &vet[menor]);
    }
}

static void bubbleSort(FORMA vet[], int n, ComparadorForma comparar){
    for (int i = 0; i < n - 1; i++){
        int trocou = 0;

        for (int j = 0; j < n - 1 - i; j++){
            if (comparar(vet[j + 1], vet[j]) < 0){
                troca(&vet[j], &vet[j + 1]);
                trocou = 1;
            }
        }

        if (!trocou)
            break;
    }
}

static void insertionSort(FORMA vet[], int n, ComparadorForma comparar){
    for (int i = 1; i < n; i++){
        FORMA chave = vet[i];

        int j = i - 1;

        while (j >= 0 && comparar(chave, vet[j]) < 0){
            vet[j + 1] = vet[j];
            j--;
        }

        vet[j + 1] = chave;
    }
}

static void shellSort(FORMA vet[], int n, ComparadorForma comparar){
    for (int gap = n / 2; gap > 0; gap /= 2){

        for (int i = gap; i < n; i++){

            FORMA aux = vet[i];
            int j = i;

            while (j >= gap && comparar(aux, vet[j - gap]) < 0){
                vet[j] = vet[j - gap];
                j -= gap;
            }

            vet[j] = aux;
        }
    }
}

static void quickSort(FORMA vet[], int inicio, int fim, ComparadorForma comparar){
    if (inicio < fim){
        int p = particiona(vet, inicio, fim, comparar);

        quickSort(vet, inicio, p - 1, comparar);
        quickSort(vet, p + 1, fim, comparar);
    }
}

static int particiona(FORMA vet[], int inicio, int fim, ComparadorForma comparar){
    FORMA pivo = vet[fim];

    int i = inicio - 1;

    for (int j = inicio; j < fim; j++){

        if (comparar(vet[j], pivo) <= 0){
            i++;
            troca(&vet[i], &vet[j]);
        }
    }

    troca(&vet[i + 1], &vet[fim]);

    return i + 1;
}

static void mergeSort(FORMA vet[], int inicio, int fim, ComparadorForma comparar){
    if (inicio >= fim)
        return;

    int meio = (inicio + fim) / 2;

    mergeSort(vet, inicio, meio, comparar);
    mergeSort(vet, meio + 1, fim, comparar);

    merge(vet, inicio, meio, fim, comparar);
}

static void merge(FORMA vet[], int inicio, int meio, int fim, ComparadorForma comparar){
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    FORMA esq[n1];
    FORMA dir[n2];

    for (int i = 0; i < n1; i++)
        esq[i] = vet[inicio + i];

    for (int i = 0; i < n2; i++)
        dir[i] = vet[meio + 1 + i];

    int i = 0;
    int j = 0;
    int k = inicio;

    while (i < n1 && j < n2){

        if (comparar(esq[i], dir[j]) <= 0)
            vet[k++] = esq[i++];
        else
            vet[k++] = dir[j++];
    }

    while (i < n1)
        vet[k++] = esq[i++];

    while (j < n2)
        vet[k++] = dir[j++];
}