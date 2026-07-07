#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitorQry.h"

#include "../estruturas/ABB.h"
#include "../formas/forma.h"
#include "../formas/circulo.h"
#include "../formas/estiloTexto.h"
#include "../formas/linha.h"
#include "../formas/retangulo.h"
#include "../formas/texto.h"
#include "leitorDeArquivos.h"
#include "svg.h"
#include "ordenacao.h"
#include "comparadores.h"

typedef struct {

    ARVORE banco;

    SVG svg;

    DadosArquivo geo;
    DadosArquivo qry;

    FILE *txt;

    FORMA *selecionadas;
    int qtdSel;
    int capSel;
    int proxId;

} QrySt;

/* ======================== FUNÇÕES AUXILIARES ======================== */
static void exeCmd (QrySt *qry, FILE *arq, char *cmd);

static void exeCmdSel (QrySt *qry, FILE *arq);
static void exeCmdFind (QrySt *qry, FILE *arq);
static void exeCmdFindRm (QrySt *qry, FILE *arq);
static void exeCmdCm (QrySt *qry, FILE *arq);
static void exeCmdMc(QrySt *qry, FILE *arq);

static int formaDentroRegiao(FORMA f, double x, double y, double w, double h);

static void limparSelecao(QrySt *qry);
static void adicionarSelecionada(QrySt *qry, FORMA f);

static ALGORITMO lerAlgoritmo(char *alg);
static CRITERIO lerCriterio(char *crit);
static void produzirOrdenacao(QrySt *qry, int k, ALGORITMO alg, CRITERIO crit, double x, double y, double dw, int remover);

static FORMA *selecionadasParaVetor(QrySt *qry, int *n);
static FORMA clonarForma(FORMA f);
static void moverFormaParaPosicao(  FORMA f, double x, double y);

static void imprimirFormaSelecionada(FILE *txt, FORMA f, CRITERIO crit);
/* ======================== FUNÇÕES PRINCIPAIS ======================== */

LEITOR_QRY criarLeitorQry(char *dirSaida, DadosArquivo geo, DadosArquivo qry, ARVORE banco, SVG svg){
    QrySt *novo = malloc(sizeof(QrySt));

    if (novo == NULL)
        return NULL;

    novo->txt = NULL;
    novo->selecionadas = NULL;

    novo->banco = banco;
    novo->svg = svg;

    novo->geo = geo;
    novo->qry = qry;

    novo->capSel = 32;
    novo->qtdSel = 0;
    novo->proxId = obterMaiorIdArvore(banco);
    novo->selecionadas = malloc(sizeof(FORMA) * novo->capSel);

    if (novo->selecionadas == NULL){
        free(novo);
        return NULL;
    }

    char caminhoTxt[1024];

    char nomeGeo[256];
    char nomeQry[256];

    strcpy(nomeGeo, getNomeArq(geo));
    strcpy(nomeQry, getNomeArq(qry));

    char *p = strrchr(nomeGeo, '.');
    if (p != NULL)
        *p = '\0';

    p = strrchr(nomeQry, '.');
    if (p != NULL)
        *p = '\0';

    snprintf(
        caminhoTxt,
        sizeof(caminhoTxt),
        "%s/%s-%s.txt",
        dirSaida,
        nomeGeo,
        nomeQry
    );

    novo->txt = fopen(caminhoTxt, "w");

    if (novo->txt == NULL){
        free(novo->selecionadas);
        free(novo);
        return NULL;
    }

    return (LEITOR_QRY) novo;
}

void executarQry(LEITOR_QRY leitor){
    if (leitor == NULL)
        return;

    QrySt *qry = (QrySt *) leitor;

    FILE *arquivoQry = fopen(getPathArq(qry->qry), "r");

    if (arquivoQry == NULL)
        return;

    char comando[64];

    while (fscanf(arquivoQry, "%63s", comando) == 1){

        exeCmd(qry, arquivoQry, comando);
    }

    fclose(arquivoQry);
}

void destruirLeitorQry(LEITOR_QRY leitor){
    if (leitor == NULL)
        return;

    QrySt *qry = (QrySt *) leitor;

    if (qry->txt != NULL)
        fclose(qry->txt);

    free(qry->selecionadas);

    free(qry);
}

/* ======================== IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ======================== */
static void exeCmd(QrySt *qry, FILE *arq, char *cmd){

    if(strcmp(cmd, "sel") == 0){
        exeCmdSel(qry, arq);
    }
    else if(strcmp(cmd, "find") == 0){
        exeCmdFind(qry, arq);
    }
    else if(strcmp(cmd, "findrm") == 0){
        exeCmdFindRm(qry, arq);
    }
    else if(strcmp(cmd, "cm") == 0){
        exeCmdCm(qry, arq);
    }
    else if(strcmp(cmd, "mc") == 0){
        exeCmdMc(qry, arq);
    }
}

static void exeCmdSel(QrySt *qry, FILE *arq){

    double x, y, w, h;

    if(fscanf(arq,"%lf %lf %lf %lf",
              &x,&y,&w,&h) != 4)
        return;
    
    fprintf(qry->txt,
        "[*] sel %.2lf %.2lf %.2lf %.2lf\n",
        x,y,w,h);

    limparSelecao(qry);

    int n = tamanhoArvore(qry->banco);

    if(n <= 0)
        return;

    FORMA *vet = malloc(sizeof(FORMA)*n);
        if(vet == NULL)
            return;


    arvoreParaVetor(qry->banco, vet);

    for(int i=0;i<n;i++){

        if(formaDentroRegiao(vet[i],x,y,w,h)){

            adicionarSelecionada(qry,vet[i]);

            fprintf(qry->txt,
                    "%d %s\n",
                    getIdForma(vet[i]),
                    getNomeForma(vet[i]));
        }
    }

    free(vet);

    svgDesenharSelecao(qry->svg, x, y, w, h);
}

static void exeCmdFind(QrySt *qry, FILE *arq){

    int k;
    char alg[32];
    char crit[32];

    double x;
    double y;
    double dw;

    if(fscanf(arq,
              "%d %31s %31s %lf %lf %lf",
              &k, alg, crit, &x, &y, &dw) != 6)
        return;

    fprintf(qry->txt,
        "[*] find %d %s %s %.2lf %.2lf %.2lf\n",
        k,alg,crit,x,y,dw);

    produzirOrdenacao(qry, k, lerAlgoritmo(alg), lerCriterio(crit), x, y, dw, 0);
}

static void exeCmdFindRm(QrySt *qry, FILE *arq){

    int k;
    char alg[32];
    char crit[32];

    double x;
    double y;
    double dw;

    if(fscanf(arq,
              "%d %31s %31s %lf %lf %lf",
              &k, alg, crit, &x, &y, &dw) != 6)
        return;

    fprintf(qry->txt,
        "[*] findrm %d %s %s %.2lf %.2lf %.2lf\n",
        k,alg,crit,x,y,dw);

    produzirOrdenacao(
        qry,
        k,
        lerAlgoritmo(alg),
        lerCriterio(crit),
        x,
        y,
        dw,
        1
    );
}

static void exeCmdCm(QrySt *qry, FILE *arq){

    double x;
    double y;
    double w;
    double h;
    double dx;
    double dy;

    if(fscanf(arq,
              "%lf %lf %lf %lf %lf %lf",
              &x,&y,&w,&h,&dx,&dy) != 6)
        return;

    fprintf(qry->txt,
        "[*] cm %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
        x,y,w,h,dx,dy);

    limparSelecao(qry);

    int n = tamanhoArvore(qry->banco);

    if(n <= 0)
        return;

    FORMA *vet = malloc(sizeof(FORMA) * n);

    if(vet == NULL)
        return;

    arvoreParaVetor(qry->banco, vet);

    for(int i = 0; i < n; i++){

        if(!formaDentroRegiao(vet[i], x, y, w, h))
            continue;

        FORMA copia = clonarForma(vet[i]);

        if(copia == NULL)
            continue;

        setIdForma(copia, qry->proxId++);

        moverForma(copia, dx, dy);

        pushArvore(qry->banco, copia);

        adicionarSelecionada(qry, copia);

        printFormaTXT(qry->txt, copia);
    }

    free(vet);
}

static void exeCmdMc(QrySt *qry, FILE *arq){

    char corBorda[64];
    char corPreenchimento[64];

    if(fscanf(arq,
              "%63s %63s",
              corBorda,
              corPreenchimento) != 2)
        return;

    fprintf(qry->txt,
        "[*] mc %s %s\n",
        corBorda,
        corPreenchimento);

    for(int i = 0; i < qry->qtdSel; i++){

        FORMA f = qry->selecionadas[i];

        setCorBordaForma(f, corBorda);

        if(getTipoForma(f) != FORMA_LINHA)
            setCorPreenchimentoForma(f, corPreenchimento);
    }
}

static int formaDentroRegiao(FORMA f, double x, double y, double w, double h){
    if(f == NULL)
        return 0;

    switch(getTipoForma(f)){

        case FORMA_RETANGULO:{

            double fx = getXForma(f);
            double fy = getYForma(f);

            return (fx >= x &&
                    fy >= y &&
                    fx + getLarguraForma(f) <= x + w &&
                    fy + getAlturaForma(f) <= y + h);
        }

        case FORMA_CIRCULO:{

            double cx = getXForma(f);
            double cy = getYForma(f);
            double r = getRaioForma(f);

            return (cx-r >= x &&
                    cy-r >= y &&
                    cx+r <= x+w &&
                    cy+r <= y+h);
        }

        case FORMA_LINHA:{

            double x1 = getXForma(f);
            double y1 = getYForma(f);

            double x2 = getX2Forma(f);
            double y2 = getY2Forma(f);

            return (x1 >= x && x1 <= x+w &&
                    y1 >= y && y1 <= y+h &&
                    x2 >= x && x2 <= x+w &&
                    y2 >= y && y2 <= y+h);
        }

        case FORMA_TEXTO:{

            double tx = getXForma(f);
            double ty = getYForma(f);

            return (tx >= x &&
                    tx <= x+w &&
                    ty >= y &&
                    ty <= y+h);
        }

        default:
            return 0;
    }
}

static void limparSelecao(QrySt *qry){
    if (qry == NULL)
        return;

    qry->qtdSel = 0;
}

static void adicionarSelecionada(QrySt *qry, FORMA f){
    if (qry == NULL || f == NULL)
        return;

    if (qry->qtdSel >= qry->capSel){

        qry->capSel *= 2;

        FORMA *novo = realloc(
            qry->selecionadas,
            sizeof(FORMA) * qry->capSel
        );

        if (novo == NULL)
            return;

        qry->selecionadas = novo;
    }

    qry->selecionadas[qry->qtdSel++] = f;
}

static ALGORITMO lerAlgoritmo(char *alg){

    if(strcmp(alg, "ss") == 0)
        return SS;

    if(strcmp(alg, "bs") == 0)
        return BS;

    if(strcmp(alg, "is") == 0)
        return IS;

    if(strcmp(alg, "shs") == 0)
        return SHS;

    if(strcmp(alg, "qs") == 0)
        return QS;

    if(strcmp(alg, "ms") == 0)
        return MS;

    return SS;
}

static CRITERIO lerCriterio(char *crit){

    if(strcmp(crit, "d") == 0)
        return DEFAULT;

    if(strcmp(crit, "a") == 0)
        return AREA;

    if(strcmp(crit, "w") == 0)
        return LARGURA;

    if(strcmp(crit, "h") == 0)
        return ALTURA;

    if(strcmp(crit, "c") == 0)
        return COR;

    return DEFAULT;
}

static void produzirOrdenacao(QrySt *qry, int k, ALGORITMO alg, CRITERIO crit, double x, double y, double dw, int remover){
    svgLimparPontos(qry->svg);
    svgLimparMarcadores(qry->svg);

    int n;

    FORMA *vet = selecionadasParaVetor(qry, &n);

    if(vet == NULL || n == 0)
        return;

    svgDefinirLayoutOrdenacao(
        qry->svg,
        x,
        y,
        dw
    );

    ordenar(
        vet,
        n,
        alg,
        obterComparador(crit),
        qry->svg,
        qry->banco
    );

    if(k > n)
        k = n;

    double xAtual = x;

    if(remover){
        for(int i = k; i < n; i++){

            FORMA removida = popIdArvore(
                qry->banco,
                getIdForma(vet[i])
            );

            if(removida == NULL){
                fprintf(stderr, "Erro ao remover id %d\n", getIdForma(vet[i]));
            
            } else{
                killForma(removida);
                vet[i] = NULL;
            }
        }

        qry->qtdSel = k;

        for(int i = 0; i < k; i++)
            qry->selecionadas[i] = vet[i];
    }

    for(int i = 0; i < k; i++){

        moverFormaParaPosicao(
            vet[i],
            xAtual,
            y
        );

        svgMarcarAncora(qry->svg, vet[i]);

        imprimirFormaSelecionada(
            qry->txt,
            vet[i],
            crit
        );

        
        double largura = getLarguraForma(vet[i]);

        xAtual += largura + dw;
    }

    svgFinalizarLayoutOrdenacao(qry->svg);
    free(vet);
}

static FORMA *selecionadasParaVetor(QrySt *qry, int *n){

    *n = qry->qtdSel;

    if(*n == 0)
        return NULL;

    FORMA *vet = malloc((*n) * sizeof(FORMA));

    if(vet == NULL)
        return NULL;

    for(int i = 0; i < *n; i++)
        vet[i] = qry->selecionadas[i];

    return vet;
}

static FORMA clonarForma(FORMA f){

    if(f == NULL)
        return NULL;

    FormaTipo tipo = getTipoForma(f);

    switch(tipo){

        case FORMA_CIRCULO:{

            CIRCULO c = criaCirculo(
                getIdForma(f),
                getXForma(f),
                getYForma(f),
                getRaioForma(f),
                getCorBordaForma(f),
                getCorPreenchimentoForma(f)
            );

            return criarForma(FORMA_CIRCULO, c);
        }

        case FORMA_RETANGULO:{

            RETANGULO r = criaRetangulo(
                getIdForma(f),
                getXForma(f),
                getYForma(f),
                getLarguraForma(f),
                getAlturaForma(f),
                getCorBordaForma(f),
                getCorPreenchimentoForma(f)
            );

            return criarForma(FORMA_RETANGULO, r);
        }

        case FORMA_LINHA:{

            LINHA l = criaLinha(
                getIdForma(f),
                getXForma(f),
                getYForma(f),
                getX2Forma(f),
                getY2Forma(f),
                getCorBordaForma(f)
            );

            return criarForma(FORMA_LINHA, l);
        }

        case FORMA_TEXTO:{

            TEXTO t = criaTexto(
                getIdForma(f),
                getXForma(f),
                getYForma(f),
                getCorBordaForma(f),
                getCorPreenchimentoForma(f),
                getAncoraTextoForma(f),
                getConteudoTextoForma(f)
            );

            return criarForma(FORMA_TEXTO, t);
        }

        default:
            return NULL;
    }
}

static void moverFormaParaPosicao(FORMA f, double x, double y){

    double xAtual = getXForma(f);
    double yAtual = getYForma(f);

    moverForma(
        f,
        x - xAtual,
        y - yAtual
    );
}

static void imprimirFormaSelecionada(FILE *txt, FORMA f, CRITERIO crit){

    fprintf(txt,
            "%d %s ",
            getIdForma(f),
            getNomeForma(f));

    switch(crit){

        case DEFAULT:
            fprintf(txt,
                    "(x=%.2lf y=%.2lf)",
                    getXForma(f),
                    getYForma(f));
            break;

        case AREA:
            fprintf(txt,
                    "(area=%.2lf)",
                    getAreaForma(f));
            break;

        case LARGURA:
            fprintf(txt,
                    "(largura=%.2lf)",
                    getLarguraForma(f));
            break;

        case ALTURA:
            fprintf(txt,
                    "(altura=%.2lf)",
                    getAlturaForma(f));
            break;

        case COR:
            fprintf(txt,
                    "(cor=%s)",
                    getCorPreenchimentoForma(f));
            break;
    }

    fprintf(txt, "\n");
}