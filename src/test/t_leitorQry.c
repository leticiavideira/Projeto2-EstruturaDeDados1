#include "unity.h"

#include "../gerais/leitorQry.h"
#include "../gerais/leitorGeo.h"
#include "../gerais/leitorDeArquivos.h"
#include "../gerais/svg.h"

#include "../estruturas/ABB.h"

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

/*==================================================
 CRIAÇÃO
==================================================*/

void test_criarLeitorQry_Valido(){

    criarArquivo("teste.geo",
        "c 1 10 10 5 black red\n");

    criarArquivo("teste.qry","");

    DadosArquivo geo=criarDadosArq("teste.geo");
    DadosArquivo qry=criarDadosArq("teste.qry");

    SISTEMA sistema=processarGeo(geo);

    ARVORE banco=getArvoreFormas(sistema);

    SVG svg=criarSVG(".", geo, qry);

    LEITOR_QRY leitor=
        criarLeitorQry(".",geo,qry,banco,svg);

    TEST_ASSERT_NOT_NULL(leitor);

    destruirLeitorQry(leitor);
    killSistemaGeo(sistema);
}

void test_criarLeitorQry_DiretorioNULL(){

    DadosArquivo geo=NULL;
    DadosArquivo qry=NULL;

    LEITOR_QRY leitor=
        criarLeitorQry(NULL,geo,qry,NULL,NULL);

    TEST_ASSERT_NULL(leitor);
}

void test_criarLeitorQry_GeoNULL(){

    LEITOR_QRY leitor=
        criarLeitorQry(".",NULL,NULL,NULL,NULL);

    TEST_ASSERT_NULL(leitor);
}

void test_criarLeitorQry_QryNULL(){

    DadosArquivo geo=NULL;

    LEITOR_QRY leitor=
        criarLeitorQry(".",geo,NULL,NULL,NULL);

    TEST_ASSERT_NULL(leitor);
}

void test_criarLeitorQry_BancoNULL(){

    DadosArquivo geo=NULL;
    DadosArquivo qry=NULL;

    LEITOR_QRY leitor=
        criarLeitorQry(".",geo,qry,NULL,NULL);

    TEST_ASSERT_NULL(leitor);
}

/*==================================================
 EXECUÇÃO
==================================================*/

void test_executarQry_Vazio(){

    criarArquivo("teste.geo",
        "c 1 0 0 5 black red\n");

    criarArquivo("teste.qry","");

    DadosArquivo geo=criarDadosArq("teste.geo");
    DadosArquivo qry=criarDadosArq("teste.qry");

    SISTEMA sistema=processarGeo(geo);

    LEITOR_QRY leitor=
        criarLeitorQry(
            ".",
            geo,
            qry,
            getArvoreFormas(sistema),
            NULL
        );

    executarQry(leitor);

    TEST_ASSERT_EQUAL(
        1,
        tamanhoArvore(getArvoreFormas(sistema))
    );

    destruirLeitorQry(leitor);
    killSistemaGeo(sistema);
}

void test_executarQry_ComandosInvalidos(){

    criarArquivo("teste.geo",
        "c 1 0 0 5 black red\n");

    criarArquivo("teste.qry",
        "abcdef\n"
        "xyz 10 20\n");

    DadosArquivo geo=criarDadosArq("teste.geo");
    DadosArquivo qry=criarDadosArq("teste.qry");

    SISTEMA sistema=processarGeo(geo);

    LEITOR_QRY leitor=
        criarLeitorQry(
            ".",
            geo,
            qry,
            getArvoreFormas(sistema),
            NULL
        );

    executarQry(leitor);

    TEST_PASS();

    destruirLeitorQry(leitor);
    killSistemaGeo(sistema);
}

void test_executarQry_LeitorNULL(){

    executarQry(NULL);

    TEST_PASS();
}

/*==================================================
 DESTRUIÇÃO
==================================================*/

void test_destruirLeitorQry(){

    criarArquivo("teste.geo",
        "c 1 0 0 5 black red\n");

    criarArquivo("teste.qry","");

    DadosArquivo geo=criarDadosArq("teste.geo");
    DadosArquivo qry=criarDadosArq("teste.qry");

    SISTEMA sistema=processarGeo(geo);

    LEITOR_QRY leitor=
        criarLeitorQry(
            ".",
            geo,
            qry,
            getArvoreFormas(sistema),
            NULL
        );

    destruirLeitorQry(leitor);

    TEST_PASS();

    killSistemaGeo(sistema);
}

void test_destruirLeitorQry_NULL(){

    destruirLeitorQry(NULL);

    TEST_PASS();
}

/*==================================================
 MAIN
==================================================*/

int main(){

    UNITY_BEGIN();

    RUN_TEST(test_criarLeitorQry_Valido);

    RUN_TEST(test_criarLeitorQry_DiretorioNULL);
    RUN_TEST(test_criarLeitorQry_GeoNULL);
    RUN_TEST(test_criarLeitorQry_QryNULL);
    RUN_TEST(test_criarLeitorQry_BancoNULL);

    RUN_TEST(test_executarQry_Vazio);
    RUN_TEST(test_executarQry_ComandosInvalidos);
    RUN_TEST(test_executarQry_LeitorNULL);

    RUN_TEST(test_destruirLeitorQry);
    RUN_TEST(test_destruirLeitorQry_NULL);

    return UNITY_END();
}