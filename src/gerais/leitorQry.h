#ifndef LEITOR_QRY_H
#define LEITOR_QRY_H

#include "../estruturas/ABB.h"

#include "leitorDeArquivos.h"
#include "svg.h"

/*
 * @file leitorQry.h
 * @brief Interface para o módulo de processamento de arquivos QRY.
 *
 * Este módulo é responsável por interpretar e executar os comandos
 * presentes em um arquivo QRY sobre o conjunto de formas armazenado
 * em uma árvore binária de busca.
 *
 * Durante a execução, o módulo pode modificar as formas, gerar novas
 * formas, remover elementos, produzir registros em um arquivo texto
 * e atualizar a visualização em um arquivo SVG.
 *
 * O módulo utiliza um tipo opaco para encapsular seu estado interno,
 * incluindo as estruturas utilizadas durante o processamento do arquivo.
 */

/**
 * @brief Tipo abstrato que representa um leitor de arquivos QRY.
 */
typedef void* LEITOR_QRY;

/**
 * @brief Cria e inicializa um leitor de arquivos QRY.
 *
 * @param dirSaida Diretório onde será criado o arquivo de saída (.txt).
 * @param geo Informações do arquivo GEO utilizado.
 * @param qry Informações do arquivo QRY a ser executado.
 * @param banco Árvore contendo as formas carregadas do GEO.
 * @param svg Estrutura responsável pela geração do SVG.
 *
 * @return LEITOR_QRY Ponteiro para o leitor criado.
 * @return NULL Em caso de erro de alocação ou criação do arquivo de saída.
 */
LEITOR_QRY criarLeitorQry(char *dirSaida, DadosArquivo geo, DadosArquivo qry, ARVORE banco, SVG svg);

/**
 * @brief Executa todos os comandos presentes no arquivo QRY.
 *
 * Os comandos são lidos sequencialmente e aplicados sobre as formas
 * armazenadas na árvore, atualizando também os arquivos de saída quando
 * necessário.
 *
 * @param leitor Leitor QRY.
 */
void executarQry(LEITOR_QRY leitor);

/**
 * @brief Libera toda a memória associada ao leitor QRY.
 *
 * Fecha o arquivo texto de saída e libera as estruturas internas
 * utilizadas durante o processamento.
 *
 * @param leitor Leitor QRY.
 *
 * @note Após a chamada, o leitor não deve mais ser utilizado.
 */
void destruirLeitorQry(LEITOR_QRY leitor);

#endif