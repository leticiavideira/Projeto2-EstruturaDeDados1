#ifndef ABB_H
#define ABB_H

#include "../formas/forma.h"

/*
 * @file ABB.h
 * @brief Interface para o módulo de Árvore Binária de Busca (ABB).
 *
 * Este arquivo define a interface pública para criação, manipulação e destruição
 * de uma árvore binária de busca que armazena elementos do tipo FORMA.
 *
 * Os elementos são organizados de acordo com a função de comparação padrão
 * utilizada pelo sistema, permitindo inserção, busca e remoção eficientes.
 *
 * O módulo utiliza um tipo opaco (handle) para encapsular a implementação
 * interna da árvore, garantindo abstração e segurança na manipulação da
 * estrutura de dados.
 */

/**
 * @brief Tipo abstrato que representa uma árvore binária de busca.
 */
typedef void* ARVORE;

/**
 * @brief Cria e inicializa uma árvore binária de busca vazia.
 *
 * @return ARVORE Ponteiro para a árvore criada.
 * @return NULL Em caso de erro de alocação.
 */
ARVORE criarArvore();

/**
 * @brief Insere uma forma na árvore.
 *
 * A posição da forma é determinada automaticamente pela função de
 * comparação utilizada pela árvore.
 *
 * @param a Árvore.
 * @param f Forma a ser inserida.
 *
 * @note Caso a árvore ou a forma sejam NULL, nenhuma ação é realizada.
 */
void pushArvore (ARVORE a, FORMA f);

/**
 * @brief Busca uma forma pelo seu identificador.
 *
 * @param a Árvore.
 * @param id Identificador da forma.
 *
 * @return FORMA Ponteiro para a forma encontrada.
 * @return NULL Caso a árvore seja NULL ou o identificador não exista.
 */
FORMA buscaIdArvore (ARVORE a, int id);

/**
 * @brief Remove da árvore a forma com o identificador informado.
 *
 * A forma removida é retornada ao usuário, mas não é destruída pelo módulo.
 *
 * @param a Árvore.
 * @param id Identificador da forma.
 *
 * @return FORMA Ponteiro para a forma removida.
 * @return NULL Caso a árvore seja NULL ou a forma não seja encontrada.
 */
FORMA popIdArvore (ARVORE a, int id);

/**
 * @brief Copia os elementos da árvore para um vetor.
 *
 * As formas são copiadas seguindo o percurso em ordem (in-order),
 * resultando em um vetor ordenado segundo o critério da árvore.
 *
 * @param a Árvore.
 * @param vet Vetor onde os elementos serão armazenados.
 *
 * @return int Quantidade de elementos copiados.
 * @return int -1 Em caso de erro (árvore NULL).
 */
int arvoreParaVetor (ARVORE a, FORMA vet[]);

/**
 * @brief Retorna a quantidade de elementos armazenados na árvore.
 *
 * @param a Árvore.
 *
 * @return int Número de elementos.
 * @return int -1 Em caso de erro (árvore NULL).
 */
int tamanhoArvore (ARVORE a);

/**
 * @brief Verifica se a árvore está vazia.
 *
 * @param a Árvore.
 *
 * @return int 1 se estiver vazia.
 * @return int 0 se possuir elementos.
 * @return int -1 Em caso de erro (árvore NULL).
 */
int arvoreVazia (ARVORE a);

/**
 * @brief Remove todos os elementos da árvore.
 *
 * Todas as formas armazenadas são destruídas e os nós internos são
 * liberados, mantendo a estrutura da árvore válida para reutilização.
 *
 * @param a Árvore.
 */
void limparArvore (ARVORE a);

/**
 * @brief Libera toda a memória associada à árvore.
 *
 * Remove todos os elementos da árvore e libera sua estrutura interna.
 *
 * @param a Árvore.
 *
 * @note Após a chamada, a árvore não deve mais ser utilizada.
 */
void killArvore (ARVORE a);

/**
 * @brief Obtém o maior identificador presente na árvore.
 *
 * @param arv Árvore.
 *
 * @return int Maior identificador encontrado.
 * @return int 0 Caso a árvore esteja vazia.
 */
int obterMaiorIdArvore(ARVORE arv);

#endif