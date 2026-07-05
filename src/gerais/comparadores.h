#ifndef COMPARADORES_H
#define COMPARADORES_H

#include "../formas/forma.h"

/*
 * @file comparadores.h
 * @brief Interface para funções de comparação entre formas.
 *
 * Este módulo disponibiliza diferentes critérios de comparação entre objetos
 * do tipo FORMA, permitindo sua utilização em algoritmos de ordenação,
 * árvores binárias de busca e outras estruturas que dependem de uma relação
 * de ordem entre elementos.
 *
 * Todas as funções de comparação seguem a convenção:
 *   - retorno negativo: o primeiro elemento vem antes do segundo;
 *   - retorno zero: os elementos são equivalentes para o critério adotado;
 *   - retorno positivo: o primeiro elemento vem depois do segundo.
 */

 /**
 * @brief Critérios de comparação disponíveis.
 */
typedef enum{
    DEFAULT,
    AREA,
    LARGURA,
    ALTURA,
    COR
}CRITERIO;

/**
 * @brief Tipo de ponteiro para função de comparação entre formas.
 */
typedef int (*ComparadorForma)(FORMA, FORMA);

/**
 * @brief Compara duas formas utilizando o critério padrão.
 *
 * O critério padrão compara, nesta ordem:
 * - coordenada y;
 * - coordenada x;
 * - área.
 *
 * @param a Primeira forma.
 * @param b Segunda forma.
 *
 * @return int Valor negativo se a < b.
 * @return int 0 se as formas forem equivalentes.
 * @return int Valor positivo se a > b.
 */
int comparaDefault(FORMA a, FORMA b);

/**
 * @brief Compara duas formas pela área.
 *
 * @param a Primeira forma.
 * @param b Segunda forma.
 *
 * @return int Valor negativo se a área de a for menor.
 * @return int 0 se as áreas forem iguais.
 * @return int Valor positivo se a área de a for maior.
 */
int comparaArea(FORMA a, FORMA b);

/**
 * @brief Compara duas formas pela largura.
 *
 * @param a Primeira forma.
 * @param b Segunda forma.
 *
 * @return int Valor negativo se a largura de a for menor.
 * @return int 0 se as larguras forem iguais.
 * @return int Valor positivo se a largura de a for maior.
 */
int comparaLargura(FORMA a, FORMA b);

/**
 * @brief Compara duas formas pela altura.
 *
 * @param a Primeira forma.
 * @param b Segunda forma.
 *
 * @return int Valor negativo se a altura de a for menor.
 * @return int 0 se as alturas forem iguais.
 * @return int Valor positivo se a altura de a for maior.
 */
int comparaAltura(FORMA a, FORMA b);

/**
 * @brief Compara duas formas pela cor de preenchimento.
 *
 * A comparação é realizada em ordem lexicográfica utilizando as strings
 * das cores de preenchimento.
 *
 * @param a Primeira forma.
 * @param b Segunda forma.
 *
 * @return int Valor negativo se a cor de a vier antes.
 * @return int 0 se as cores forem iguais.
 * @return int Valor positivo se a cor de a vier depois.
 */
int comparaCor(FORMA a, FORMA b);

/**
 * @brief Retorna a função de comparação correspondente ao critério informado.
 *
 * @param crit Critério de comparação desejado.
 *
 * @return ComparadorForma Ponteiro para a função de comparação.
 *
 * @note Caso o critério informado seja inválido, retorna o comparador padrão.
 */
ComparadorForma obterComparador(CRITERIO crit);

#endif