#ifndef SVG_H
#define SVG_H

#include "../estruturas/ABB.h"
#include "../formas/forma.h"
#include "leitorDeArquivos.h"

/*
 * @file svg.h
 * @brief Interface para geração de arquivos SVG.
 *
 * Este módulo é responsável pela criação dos arquivos SVG produzidos pelo
 * sistema, incluindo a representação inicial e final das formas, além de
 * snapshots gerados durante a execução dos algoritmos de ordenação.
 *
 * Também mantém informações auxiliares de visualização, como regiões de
 * seleção, marcadores de âncora, pontos destacados e o layout utilizado
 * para ilustrar a ordenação.
 *
 * O módulo utiliza um tipo opaco para encapsular sua implementação interna.
 */

/**
 * @brief Tipo abstrato que representa um gerador de arquivos SVG.
 */
typedef void* SVG;

/**
 * @brief Cria e inicializa um gerador de SVG.
 *
 * @param dirSaida Diretório onde os arquivos SVG serão gerados.
 * @param geo Informações do arquivo GEO.
 * @param qry Informações do arquivo QRY (pode ser NULL).
 *
 * @return SVG Ponteiro para a estrutura criada.
 * @return NULL Em caso de erro de alocação.
 */
SVG criarSVG(char *dirSaida, DadosArquivo geo, DadosArquivo qry);

/**
 * @brief Libera toda a memória associada ao gerador SVG.
 *
 * @param svg Gerador SVG.
 *
 * @note Após a chamada, a estrutura não deve mais ser utilizada.
 */
void destruirSVG(SVG svg);

/**
 * @brief Gera o arquivo SVG correspondente ao estado inicial das formas.
 *
 * @param svg Gerador SVG.
 * @param banco Árvore contendo todas as formas.
 */
void gerarSVGInicial(SVG svg, ARVORE banco);

/**
 * @brief Gera o arquivo SVG correspondente ao estado final das formas.
 *
 * Além das formas armazenadas, também são desenhados os elementos
 * auxiliares de visualização (seleção, marcadores e pontos).
 *
 * @param svg Gerador SVG.
 * @param banco Árvore contendo todas as formas.
 */
void gerarSVGFinal(SVG svg, ARVORE banco);

/**
 * @brief Gera um snapshot durante a execução de um algoritmo de ordenação.
 *
 * O SVG gerado contém:
 * - todas as formas armazenadas na árvore;
 * - a região de seleção atual;
 * - os marcadores de âncora;
 * - os pontos destacados;
 * - a disposição temporária do vetor sendo ordenado.
 *
 * @param svg Gerador SVG.
 * @param banco Árvore contendo todas as formas.
 * @param vet Vetor atualmente sendo ordenado.
 * @param n Quantidade de elementos do vetor.
 */
void gerarSnapshotOrdenacao(SVG svg, ARVORE banco, FORMA vet[], int n);

/**
 * @brief Define a região de seleção exibida nos SVGs.
 *
 * @param svg Gerador SVG.
 * @param x Coordenada x da região.
 * @param y Coordenada y da região.
 * @param w Largura da região.
 * @param h Altura da região.
 */
void svgDefinirSelecao(SVG svg, double x, double y, double w, double h);

/**
 * @brief Remove a região de seleção atualmente exibida.
 *
 * @param svg Gerador SVG.
 */
void svgLimparSelecao(SVG svg);

/**
 * @brief Adiciona um marcador na âncora de uma forma.
 *
 * @param svg Gerador SVG.
 * @param forma Forma cuja âncora será marcada.
 */
void svgMarcarAncora(SVG svg, FORMA forma);

/**
 * @brief Remove todos os marcadores de âncora.
 *
 * @param svg Gerador SVG.
 */
void svgLimparMarcadores(SVG svg);

/**
 * @brief Inicializa a lista de marcadores.
 *
 * Equivale a iniciar uma nova sequência de marcações.
 *
 * @param svg Gerador SVG.
 */
void svgIniciarMarcadores(SVG svg);

/**
 * @brief Define o layout utilizado para visualizar uma ordenação.
 *
 * @param svg Gerador SVG.
 * @param x Coordenada x inicial.
 * @param y Coordenada y inicial.
 * @param dw Espaçamento horizontal entre elementos.
 */
void svgDefinirLayoutOrdenacao(SVG svg, double x, double y, double dw);

/**
 * @brief Define a região de seleção a ser desenhada.
 *
 * @param s Gerador SVG.
 * @param x Coordenada x.
 * @param y Coordenada y.
 * @param w Largura.
 * @param h Altura.
 */
void svgDesenharSelecao(SVG s, double x, double y, double w, double h);

/**
 * @brief Adiciona um ponto destacado ao SVG.
 *
 * @param s Gerador SVG.
 * @param x Coordenada x do ponto.
 * @param y Coordenada y do ponto.
 */
void svgMarcarPonto(SVG s, double x, double y);

/**
 * @brief Remove todos os pontos destacados.
 *
 * @param s Gerador SVG.
 */
void svgLimparPontos (SVG s);

/**
 * @brief Finaliza o layout de visualização da ordenação.
 *
 * Após a chamada, os snapshots deixam de desenhar a disposição
 * temporária do vetor ordenado.
 *
 * @param s Gerador SVG.
 */
void svgFinalizarLayoutOrdenacao(SVG s);

#endif