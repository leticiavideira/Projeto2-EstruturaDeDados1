#ifndef SVG_H
#define SVG_H

#include "../estruturas/ABB.h"
#include "../formas/forma.h"
#include "leitorDeArquivos.h"

typedef void* SVG;

SVG criarSVG(char *dirSaida, DadosArquivo geo, DadosArquivo qry);

void destruirSVG(SVG svg);

void gerarSVGInicial(SVG svg, ARVORE banco);

void gerarSVGFinal(SVG svg, ARVORE banco);

/*
 * Gera um snapshot durante a ordenação.
 *
 * banco : contém todas as formas do projeto.
 * vet   : vetor atualmente sendo ordenado.
 * n     : quantidade de elementos do vetor.
 *
 * O SVG desenha:
 *  - todas as formas do banco;
 *  - a seleção atual;
 *  - os marcadores;
 *  - a disposição temporária das formas do vetor.
 */
void gerarSnapshotOrdenacao(SVG svg, ARVORE banco, FORMA vet[], int n);

void svgDefinirSelecao(SVG svg, double x, double y, double w, double h);

void svgLimparSelecao(SVG svg);

void svgMarcarAncora(SVG svg, FORMA forma);

void svgLimparMarcadores(SVG svg);

void svgIniciarMarcadores(SVG svg);

void svgFinalizarMarcadores(SVG svg);

void svgDefinirLayoutOrdenacao(SVG svg, double x, double y, double dw);

#endif