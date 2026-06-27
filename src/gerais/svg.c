#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"

#include "../formas/forma.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/linha.h"
#include "../formas/texto.h"

typedef struct {

    char *dirSaida;

    DadosArquivo geo;
    DadosArquivo qry;

    int snapshotAtual;

    int selecaoAtiva;

    double selX;
    double selY;
    double selW;
    double selH;

    FORMA *marcadas;
    int qtdMarcadas;
    int capMarcadas;

    double ordX;
    double ordY;
    double ordDW;

    int layoutOrdenacaoAtivo;

} SvgSt;

/* ======================== FUNÇÕES AUXILIARES ======================== */

static char *duplicarString(const char *s);
static char *removerExtensao(char *nome);
static char *montarNomeInicial(SvgSt *svg);
static char *montarNomeFinal(SvgSt *svg);
static char *montarNomeSnapshot(SvgSt *svg);
static FILE *abrirSVG(char *nome);  
static void fecharSVG(FILE *arq);
static void desenharForma(FILE *arq,FORMA f);  
static void desenharBanco(FILE *arq,ARVORE banco);
static void desenharVetorOrdenacao(FILE *arq, SvgSt *svg, FORMA vet[], int n);


/* ======================== FUNÇÔES PRINCIPAIS ======================== */
SVG criarSVG(char *dirSaida,
             DadosArquivo geo,
             DadosArquivo qry){

    SvgSt *svg=malloc(sizeof(SvgSt));

    if(svg==NULL)
        return NULL;

    svg->dirSaida=duplicarString(dirSaida);

    svg->geo=geo;
    svg->qry=qry;

    svg->snapshotAtual=1;

    svg->selecaoAtiva=0;

    svg->selX=0;
    svg->selY=0;
    svg->selW=0;
    svg->selH=0;

    svg->qtdMarcadas=0;
    svg->capMarcadas=8;

    svg->marcadas=malloc(sizeof(FORMA)*svg->capMarcadas);
        if(svg->marcadas == NULL){
        free(svg->dirSaida);
        free(svg);
        return NULL;
}

    svg->layoutOrdenacaoAtivo = 0;

    svg->ordX = 0;
    svg->ordY = 0;
    svg->ordDW = 0;

    return svg;
}

void destruirSVG(SVG s){

    if(s==NULL)
        return;

    SvgSt *svg=s;

    free(svg->marcadas);

    free(svg->dirSaida);

    free(svg);
}

//DESENHAR SELEÇÃO E MARCADORES
static void desenharSelecao(FILE *arq, SvgSt *svg){

    if(!svg->selecaoAtiva)
        return;

    fprintf(arq,
        "<rect "
        "x='%.2lf' "
        "y='%.2lf' "
        "width='%.2lf' "
        "height='%.2lf' "
        "fill='none' "
        "stroke='red' "
        "stroke-width='2' "
        "stroke-dasharray='5,5'/>\n",

        svg->selX,
        svg->selY,
        svg->selW,
        svg->selH);
}

static void desenharMarcadores(FILE *arq, SvgSt *svg){

    for(int i=0;i<svg->qtdMarcadas;i++){

        double x,y;

        getAncoraForma(svg->marcadas[i],&x,&y);

        fprintf(arq,
            "<rect "
            "x='%.2lf' "
            "y='%.2lf' "
            "width='6' "
            "height='6' "
            "fill='red'/>\n",

            x-3,
            y-3);
    }
}

//SVG INICIAL
void gerarSVGInicial(SVG s, ARVORE banco){

    if(s==NULL || banco==NULL)
        return;

    SvgSt *svg=s;

    char *nome=montarNomeInicial(svg);

    FILE *arq=abrirSVG(nome);

    free(nome);

    if(arq==NULL)
        return;

    desenharBanco(arq,banco);

    fecharSVG(arq);
}

//SVG FINAL
void gerarSVGFinal(SVG s, ARVORE banco){

    if(s==NULL || banco==NULL)
        return;

    SvgSt *svg=s;

    char *nome=montarNomeFinal(svg);

    FILE *arq=abrirSVG(nome);

    free(nome);

    if(arq==NULL)
        return;

    desenharBanco(arq,banco);

    desenharSelecao(arq,svg);

    desenharMarcadores(arq,svg);

    fecharSVG(arq);
}

//SNAPSHOTS DA ORDENAÇÃO
void gerarSnapshotOrdenacao(SVG s, ARVORE banco, FORMA vet[], int n){
    if(s == NULL || banco == NULL)
        return;

    SvgSt *svg = s;

    if(svg->qry == NULL)
        return;

    char *nome = montarNomeSnapshot(svg);

    FILE *arq = abrirSVG(nome);

    free(nome);

    if(arq == NULL)
        return;

    desenharBanco(arq, banco);

    desenharSelecao(arq, svg);

    desenharMarcadores(arq, svg);

    desenharVetorOrdenacao(arq, svg, vet, n);

    fecharSVG(arq);

    svg->snapshotAtual++;
}
//SELEÇÃO
void svgDefinirSelecao(SVG s,
                       double x,
                       double y,
                       double w,
                       double h){

    if(s==NULL)
        return;

    SvgSt *svg=s;

    svg->selecaoAtiva=1;

    svg->selX=x;
    svg->selY=y;
    svg->selW=w;
    svg->selH=h;
}

void svgLimparSelecao(SVG s){

    if(s==NULL)
        return;

    SvgSt *svg=s;

    svg->selecaoAtiva=0;
}

//MARCADORES
void svgMarcarAncora(SVG s, FORMA forma){

    if(s==NULL || forma==NULL)
        return;

    SvgSt *svg=s;

    if(svg->qtdMarcadas==svg->capMarcadas){

        svg->capMarcadas*=2;

        FORMA *novo = realloc(svg->marcadas, sizeof(FORMA) * svg->capMarcadas);
            if(novo == NULL)
                return;

        svg->marcadas = novo;
    }

    svg->marcadas[svg->qtdMarcadas]=forma;

    svg->qtdMarcadas++;
}

void svgLimparMarcadores(SVG s){

    if(s==NULL)
        return;

    SvgSt *svg=s;

    svg->qtdMarcadas=0;
}

void svgIniciarMarcadores(SVG s){
    svgLimparMarcadores(s);
}

void svgFinalizarMarcadores(SVG s){

}

void svgDefinirLayoutOrdenacao(SVG s, double x, double y, double dw){
    if(s == NULL)
        return;

    SvgSt *svg = s;

    svg->layoutOrdenacaoAtivo = 1;

    svg->ordX = x;
    svg->ordY = y;
    svg->ordDW = dw;
}
/* ======================== IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ======================== */
static char *duplicarString(const char *s){

    if(s==NULL)
        return NULL;

    char *nova=malloc(strlen(s)+1);

    if(nova==NULL)
        return NULL;

    strcpy(nova,s);

    return nova;
}

static char *removerExtensao(char *nome){

    char copia[256];

    strcpy(copia,nome);

    char *p=strrchr(copia,'.');

    if(p)
        *p='\0';

    return duplicarString(copia);
}

static char *montarNomeInicial(SvgSt *svg){

    char *base=removerExtensao(getNomeArq(svg->geo));

    size_t tam=strlen(svg->dirSaida)+strlen(base)+10;

    char *caminho=malloc(tam);

    sprintf(caminho,"%s/%s.svg",
            svg->dirSaida,
            base);

    free(base);

    return caminho;
}

static char *montarNomeFinal(SvgSt *svg){

    char *baseGeo=removerExtensao(getNomeArq(svg->geo));

    size_t tam;

    if(svg->qry){

        char *baseQry=removerExtensao(getNomeArq(svg->qry));

        tam=strlen(svg->dirSaida)+strlen(baseGeo)+strlen(baseQry)+10;

        char *caminho=malloc(tam);

        sprintf(caminho,
                "%s/%s-%s.svg",
                svg->dirSaida,
                baseGeo,
                baseQry);

        free(baseGeo);
        free(baseQry);

        return caminho;
    }

    tam=strlen(svg->dirSaida)+strlen(baseGeo)+10;

    char *caminho=malloc(tam);

    sprintf(caminho,"%s/%s.svg",
            svg->dirSaida,
            baseGeo);

    free(baseGeo);

    return caminho;
}

static char *montarNomeSnapshot(SvgSt *svg){

    if(svg->qry == NULL)
        return NULL;

    char *baseGeo = removerExtensao(getNomeArq(svg->geo));
    char *baseQry = removerExtensao(getNomeArq(svg->qry));

    size_t tam =
        strlen(svg->dirSaida) +
        strlen(baseGeo) +
        strlen(baseQry) +
        30;

    char *caminho = malloc(tam);

    sprintf(caminho,
            "%s/%s-%s%06d.svg",
            svg->dirSaida,
            baseGeo,
            baseQry,
            svg->snapshotAtual);

    free(baseGeo);
    free(baseQry);

    return caminho;
}

static FILE *abrirSVG(char *nome){

    FILE *arq=fopen(nome,"w");

    if(arq==NULL)
        return NULL;

    fprintf(arq,
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");

    fprintf(arq,
            "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    return arq;
}

static void fecharSVG(FILE *arq){

    fprintf(arq,"</svg>\n");

    fclose(arq);
}

//DESENHO DAS FORMAS
static void desenharForma(FILE *arq,FORMA f){

    switch(getTipoForma(f)){

        case FORMA_CIRCULO:{

            CIRCULO c=getDataForma(f);

            fprintf(arq,
            "<circle cx='%.2lf' cy='%.2lf' r='%.2lf' "
            "fill='%s' stroke='%s'/>\n",

            getX_C(c),
            getY_C(c),
            getR_C(c),
            getCorP_C(c),
            getCorB_C(c));

            break;
        }

        case FORMA_RETANGULO:{

            RETANGULO r=getDataForma(f);

            fprintf(arq,

            "<rect x='%.2lf' y='%.2lf' "
            "width='%.2lf' height='%.2lf' "
            "fill='%s' stroke='%s'/>\n",

            getX_R(r),
            getY_R(r),
            getW_R(r),
            getH_R(r),
            getCorP_R(r),
            getCorB_R(r));

            break;
        }

        case FORMA_LINHA:{

            LINHA l=getDataForma(f);

            fprintf(arq,

            "<line x1='%.2lf' y1='%.2lf' "
            "x2='%.2lf' y2='%.2lf' "
            "stroke='%s'/>\n",

            getX1_L(l),
            getY1_L(l),
            getX2_L(l),
            getY2_L(l),
            getCor_L(l));

            break;
        }

        case FORMA_TEXTO:{

            TEXTO t=getDataForma(f);

            char *anchor="start";

            char a=getA_T(t);

            if(a=='m'||a=='M')
                anchor="middle";

            else if(a=='f'||a=='F')
                anchor="end";

            fprintf(arq,

            "<text "
            "x='%.2lf' "
            "y='%.2lf' "
            "fill='%s' "
            "stroke='%s' "
            "text-anchor='%s'>"
            "%s"
            "</text>\n",

            getX_T(t),
            getY_T(t),
            getCorp_T(t),
            getCorb_T(t),
            anchor,
            getTxto_T(t));

            break;
        }

        default:
            break;
    }
}

//DESENHAR TODA A ÁRVORE
static void desenharBanco(FILE *arq,ARVORE banco){

    int n=tamanhoArvore(banco);

    if(n<=0)
        return;

    FORMA *vet=malloc(sizeof(FORMA)*n);

    arvoreParaVetor(banco,vet);

    for(int i=0;i<n;i++)
        desenharForma(arq,vet[i]);

    free(vet);
}

static void desenharVetorOrdenacao(FILE *arq, SvgSt *svg, FORMA vet[], int n){
    if(!svg->layoutOrdenacaoAtivo)
        return;

    if(vet == NULL || n <= 0)
        return;

    for(int i=0;i<n;i++){

        double x = svg->ordX + i * svg->ordDW;
        double y = svg->ordY;

        fprintf(arq,
            "<circle "
            "cx='%.2lf' "
            "cy='%.2lf' "
            "r='4' "
            "fill='blue'/>\n",
            x,
            y);

        fprintf(arq,
            "<text "
            "x='%.2lf' "
            "y='%.2lf' "
            "font-size='9' "
            "text-anchor='middle'>"
            "%d"
            "</text>\n",
            x,
            y - 8,
            i);

        double ax, ay;

        getAncoraForma(vet[i], &ax, &ay);

        fprintf(arq,
            "<line "
            "x1='%.2lf' "
            "y1='%.2lf' "
            "x2='%.2lf' "
            "y2='%.2lf' "
            "stroke='blue' "
            "stroke-width='1'/>\n",
            x,
            y,
            ax,
            ay);
    }
}

