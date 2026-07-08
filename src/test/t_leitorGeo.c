#include "unity.h"

#include "../gerais/leitorGeo.h"
#include "../gerais/leitorDeArquivos.h"
#include "../estruturas/ABB.h"
#include "../formas/forma.h"

#include <stdio.h>
#include <string.h>

void setUp(void){}
void tearDown(void){}

/*==================================================
 AUXILIAR
==================================================*/

void criarArquivoGeo(const char *nome,const char *conteudo){

    FILE *f=fopen(nome,"w");

    TEST_ASSERT_NOT_NULL(f);

    fprintf(f,"%s",conteudo);

    fclose(f);
}

/*==================================================
 PROCESSAR GEO
==================================================*/

void test_processarGeo_arquivoValido(){

    criarArquivoGeo(
        "teste.geo",
        "c 1 10 10 5 black red\n"
        "r 2 20 20 30 40 blue yellow\n"
    );

    DadosArquivo d=criarDadosArq("teste.geo");

    SISTEMA s=processarGeo(d);

    TEST_ASSERT_NOT_NULL(s);

    ARVORE a=getArvoreFormas(s);

    TEST_ASSERT_NOT_NULL(a);
    TEST_ASSERT_EQUAL(2,tamanhoArvore(a));

    killSistemaGeo(s);
}

void test_processarGeo_arquivoVazio(){

    criarArquivoGeo("vazio.geo","");

    DadosArquivo d=criarDadosArq("vazio.geo");

    SISTEMA s=processarGeo(d);

    TEST_ASSERT_NOT_NULL(s);

    TEST_ASSERT_EQUAL(
        0,
        tamanhoArvore(getArvoreFormas(s))
    );

    killSistemaGeo(s);
}

void test_processarGeo_arquivoInexistente(){

    DadosArquivo d=criarDadosArq("naoExiste.geo");

    SISTEMA s=processarGeo(d);

    TEST_ASSERT_NULL(s);
}

void test_processarGeo_parametroNULL(){

    TEST_ASSERT_NULL(processarGeo(NULL));
}

/*==================================================
 GET ARVORE
==================================================*/

void test_getArvoreFormas(){

    criarArquivoGeo(
        "geo.geo",
        "c 1 0 0 5 black red\n"
    );

    DadosArquivo d=criarDadosArq("geo.geo");

    SISTEMA s=processarGeo(d);

    ARVORE a=getArvoreFormas(s);

    TEST_ASSERT_NOT_NULL(a);

    TEST_ASSERT_EQUAL(1,tamanhoArvore(a));

    killSistemaGeo(s);
}

void test_getArvoreFormas_NULL(){

    TEST_ASSERT_NULL(getArvoreFormas(NULL));
}

/*==================================================
 KILL
==================================================*/

void test_killSistemaGeo(){

    criarArquivoGeo(
        "geo.geo",
        "c 1 0 0 5 black red\n"
    );

    DadosArquivo d=criarDadosArq("geo.geo");

    SISTEMA s=processarGeo(d);

    killSistemaGeo(s);

    TEST_PASS();
}

void test_killSistemaGeo_NULL(){

    killSistemaGeo(NULL);

    TEST_PASS();
}

/*==================================================
 MAIN
==================================================*/

int main(){

    UNITY_BEGIN();

    RUN_TEST(test_processarGeo_arquivoValido);
    RUN_TEST(test_processarGeo_arquivoVazio);
    RUN_TEST(test_processarGeo_arquivoInexistente);
    RUN_TEST(test_processarGeo_parametroNULL);

    RUN_TEST(test_getArvoreFormas);
    RUN_TEST(test_getArvoreFormas_NULL);

    RUN_TEST(test_killSistemaGeo);
    RUN_TEST(test_killSistemaGeo_NULL);

    return UNITY_END();
}