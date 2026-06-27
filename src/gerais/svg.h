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

void gerarSnapshotOrdenacao(SVG svg, ARVORE banco);

void svgDefinirSelecao(SVG svg, double x, double y, double w, double h);

void svgLimparSelecao(SVG svg);

void svgMarcarAncora(SVG svg, FORMA forma);

void svgLimparMarcadores(SVG svg);

#endif