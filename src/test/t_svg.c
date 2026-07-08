#include "unity.h"

#include "../gerais/svg.h"
#include "../gerais/leitorDeArquivos.h"
#include "../estruturas/ABB.h"
#include "../formas/circulo.h"
#include "../formas/forma.h"

#include <stdio.h>

void setUp(void){}
void tearDown(void){}

/*==================================================
 AUXILIAR
==================================================*/

void criarArquivo(const char *nome,const char *conteudo){

    FILE *f=fopen(nome,"w");

    TEST_ASSERT_NOT_NULL(f);

    fprintf(f,"%s",conteudo);

    fclose(f);
}

ARVORE criaBancoTeste(){

    ARVORE a=criarArvore();

    pushArvore(a,
        criarForma(
            FORMA_CIRCULO,
            criaCirculo(1,10,20,5,"black","red")
        )
    );

    return a;
}

/*==================================================
 CRIAÇÃO
==================================================*/

void test_criarSVG_Valido(){

    criarArquivo("geo.geo","");
    criarArquivo("qry.qry","");

    DadosArquivo geo=criarDadosArq("geo.geo");
    DadosArquivo qry=criarDadosArq("qry.qry");

    SVG svg=criarSVG(".",geo,qry);

    TEST_ASSERT_NOT_NULL(svg);

    destruirSVG(svg);
}

void test_criarSVG_QryNULL(){

    criarArquivo("geo.geo","");

    DadosArquivo geo=criarDadosArq("geo.geo");

    SVG svg=criarSVG(".",geo,NULL);

    TEST_ASSERT_NOT_NULL(svg);

    destruirSVG(svg);
}

void test_criarSVG_DiretorioNULL(){

    SVG svg=criarSVG(NULL,NULL,NULL);

    TEST_ASSERT_NULL(svg);
}

/*==================================================
 SVG INICIAL
==================================================*/

void test_gerarSVGInicial(){

    criarArquivo("geo.geo","");

    DadosArquivo geo=criarDadosArq("geo.geo");

    SVG svg=criarSVG(".",geo,NULL);

    ARVORE banco=criaBancoTeste();

    gerarSVGInicial(svg,banco);

    TEST_PASS();

    destruirSVG(svg);
    killArvore(banco);
}

void test_gerarSVGInicial_BancoVazio(){

    criarArquivo("geo.geo","");

    DadosArquivo geo=criarDadosArq("geo.geo");

    SVG svg=criarSVG(".",geo,NULL);

    ARVORE banco=criarArvore();

    gerarSVGInicial(svg,banco);

    TEST_PASS();

    destruirSVG(svg);
    killArvore(banco);
}

void test_gerarSVGInicial_NULL(){

    gerarSVGInicial(NULL,NULL);

    TEST_PASS();
}

/*==================================================
 SVG FINAL
==================================================*/

void test_gerarSVGFinal(){

    criarArquivo("geo.geo","");

    DadosArquivo geo=criarDadosArq("geo.geo");

    SVG svg=criarSVG(".",geo,NULL);

    ARVORE banco=criaBancoTeste();

    gerarSVGFinal(svg,banco);

    TEST_PASS();

    destruirSVG(svg);
    killArvore(banco);
}

void test_gerarSVGFinal_NULL(){

    gerarSVGFinal(NULL,NULL);

    TEST_PASS();
}

/*==================================================
 SNAPSHOT
==================================================*/

void test_snapshotOrdenacao(){

    criarArquivo("geo.geo","");

    DadosArquivo geo=criarDadosArq("geo.geo");

    SVG svg=criarSVG(".",geo,NULL);

    ARVORE banco=criaBancoTeste();

    FORMA vet[1];

    vet[0]=buscaIdArvore(banco,1);

    gerarSnapshotOrdenacao(svg,banco,vet,1);

    TEST_PASS();

    destruirSVG(svg);
    killArvore(banco);
}

void test_snapshotOrdenacao_VetorNULL(){

    gerarSnapshotOrdenacao(NULL,NULL,NULL,0);

    TEST_PASS();
}

/*==================================================
 SELEÇÃO
==================================================*/

void test_svgDefinirSelecao(){

    SVG svg=criarSVG(".",NULL,NULL);

    svgDefinirSelecao(svg,10,20,30,40);

    TEST_PASS();

    destruirSVG(svg);
}

void test_svgDefinirSelecao_NULL(){

    svgDefinirSelecao(NULL,0,0,0,0);

    TEST_PASS();
}

void test_svgLimparSelecao(){

    SVG svg=criarSVG(".",NULL,NULL);

    svgLimparSelecao(svg);

    TEST_PASS();

    destruirSVG(svg);
}

void test_svgLimparSelecao_NULL(){

    svgLimparSelecao(NULL);

    TEST_PASS();
}

/*==================================================
 MARCADORES
==================================================*/

void test_svgIniciarMarcadores(){

    SVG svg=criarSVG(".",NULL,NULL);

    svgIniciarMarcadores(svg);

    TEST_PASS();

    destruirSVG(svg);
}

void test_svgMarcarAncora(){

    SVG svg=criarSVG(".",NULL,NULL);

    FORMA f=criarForma(
        FORMA_CIRCULO,
        criaCirculo(1,0,0,1,"black","red")
    );

    svgMarcarAncora(svg,f);

    killForma(f);

    destruirSVG(svg);
}

void test_svgMarcarAncora_NULL(){

    svgMarcarAncora(NULL,NULL);

    TEST_PASS();
}

void test_svgLimparMarcadores(){

    SVG svg=criarSVG(".",NULL,NULL);

    svgLimparMarcadores(svg);

    destruirSVG(svg);
}

void test_svgLimparMarcadores_NULL(){

    svgLimparMarcadores(NULL);

    TEST_PASS();
}

/*==================================================
 LAYOUT
==================================================*/

void test_svgDefinirLayout(){

    SVG svg=criarSVG(".",NULL,NULL);

    svgDefinirLayoutOrdenacao(svg,0,0,25);

    destruirSVG(svg);
}

void test_svgDefinirLayout_NULL(){

    svgDefinirLayoutOrdenacao(NULL,0,0,0);

    TEST_PASS();
}

void test_svgFinalizarLayout(){

    SVG svg=criarSVG(".",NULL,NULL);

    svgFinalizarLayoutOrdenacao(svg);

    destruirSVG(svg);
}

void test_svgFinalizarLayout_NULL(){

    svgFinalizarLayoutOrdenacao(NULL);

    TEST_PASS();
}

/*==================================================
 PONTOS
==================================================*/

void test_svgMarcarPonto(){

    SVG svg=criarSVG(".",NULL,NULL);

    svgMarcarPonto(svg,10,20);

    destruirSVG(svg);
}

void test_svgMarcarPonto_NULL(){

    svgMarcarPonto(NULL,0,0);

    TEST_PASS();
}

void test_svgLimparPontos(){

    SVG svg=criarSVG(".",NULL,NULL);

    svgLimparPontos(svg);

    destruirSVG(svg);
}

void test_svgLimparPontos_NULL(){

    svgLimparPontos(NULL);

    TEST_PASS();
}

/*==================================================
 DESTRUIÇÃO
==================================================*/

void test_destruirSVG(){

    SVG svg=criarSVG(".",NULL,NULL);

    destruirSVG(svg);

    TEST_PASS();
}

void test_destruirSVG_NULL(){

    destruirSVG(NULL);

    TEST_PASS();
}

/*==================================================
 MAIN
==================================================*/

int main(){

    UNITY_BEGIN();

    RUN_TEST(test_criarSVG_Valido);
    RUN_TEST(test_criarSVG_QryNULL);
    RUN_TEST(test_criarSVG_DiretorioNULL);

    RUN_TEST(test_gerarSVGInicial);
    RUN_TEST(test_gerarSVGInicial_BancoVazio);
    RUN_TEST(test_gerarSVGInicial_NULL);

    RUN_TEST(test_gerarSVGFinal);
    RUN_TEST(test_gerarSVGFinal_NULL);

    RUN_TEST(test_snapshotOrdenacao);
    RUN_TEST(test_snapshotOrdenacao_VetorNULL);

    RUN_TEST(test_svgDefinirSelecao);
    RUN_TEST(test_svgDefinirSelecao_NULL);
    RUN_TEST(test_svgLimparSelecao);
    RUN_TEST(test_svgLimparSelecao_NULL);

    RUN_TEST(test_svgIniciarMarcadores);
    RUN_TEST(test_svgMarcarAncora);
    RUN_TEST(test_svgMarcarAncora_NULL);
    RUN_TEST(test_svgLimparMarcadores);
    RUN_TEST(test_svgLimparMarcadores_NULL);

    RUN_TEST(test_svgDefinirLayout);
    RUN_TEST(test_svgDefinirLayout_NULL);
    RUN_TEST(test_svgFinalizarLayout);
    RUN_TEST(test_svgFinalizarLayout_NULL);

    RUN_TEST(test_svgMarcarPonto);
    RUN_TEST(test_svgMarcarPonto_NULL);
    RUN_TEST(test_svgLimparPontos);
    RUN_TEST(test_svgLimparPontos_NULL);

    RUN_TEST(test_destruirSVG);
    RUN_TEST(test_destruirSVG_NULL);

    return UNITY_END();
}