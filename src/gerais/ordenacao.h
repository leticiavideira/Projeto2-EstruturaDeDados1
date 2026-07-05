#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "comparadores.h"
#include "../formas/forma.h"
#include "../estruturas/ABB.h"
#include "svg.h"

/*
 * @file ordenacao.h
 * @brief Interface para o módulo de ordenação de formas.
 *
 * Este módulo disponibiliza uma interface única para ordenar vetores de
 * objetos do tipo FORMA utilizando diferentes algoritmos de ordenação e
 * diferentes critérios de comparação.
 *
 * Durante a execução da ordenação, o módulo pode gerar snapshots em um
 * arquivo SVG, permitindo visualizar passo a passo o funcionamento do
 * algoritmo escolhido.
 */

/**
 * @brief Algoritmos de ordenação disponíveis.
 */
typedef enum{
    SS,
    BS,
    IS,
    SHS,
    QS,
    MS
}ALGORITMO;

/**
 * @brief Ordena um vetor de formas.
 *
 * O algoritmo utilizado é determinado pelo parâmetro algoritmo, enquanto
 * o critério de ordenação é definido pela função de comparação recebida.
 *
 * Durante a execução, podem ser gerados snapshots da ordenação no arquivo
 * SVG informado.
 *
 * @param vet Vetor de formas.
 * @param n Quantidade de elementos do vetor.
 * @param algoritmo Algoritmo de ordenação a ser utilizado.
 * @param comparar Função utilizada para comparar duas formas.
 * @param svg Arquivo SVG onde os snapshots serão registrados.
 * @param banco Árvore contendo todas as formas do sistema.
 */
void ordenar(FORMA vet[], int n, ALGORITMO algoritmo, ComparadorForma comparar, SVG svg, ARVORE banco);

#endif