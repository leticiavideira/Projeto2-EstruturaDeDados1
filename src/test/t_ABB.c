#include "unity.h"

#include "../estruturas/ABB.h"
#include "../formas/forma.h"
#include "../formas/circulo.h"

void setUp(void){}
void tearDown(void){}

/*==================================================
 CRIAÇÃO
==================================================*/

void test_criarArvore(void){
    ARVORE a = criarArvore();

    TEST_ASSERT_NOT_NULL(a);
    TEST_ASSERT_EQUAL(1, arvoreVazia(a));
    TEST_ASSERT_EQUAL(0, tamanhoArvore(a));

    killArvore(a);
}

/*==================================================
 PUSH
==================================================*/

void test_pushArvore_umElemento(void){

    ARVORE a = criarArvore();

    FORMA f = criarForma(
        FORMA_CIRCULO,
        criaCirculo(10,0,0,2,"b","p")
    );

    pushArvore(a,f);

    TEST_ASSERT_EQUAL(1,tamanhoArvore(a));
    TEST_ASSERT_EQUAL(0,arvoreVazia(a));

    killArvore(a);
}

void test_pushArvore_variosElementos(void){

    ARVORE a = criarArvore();

    pushArvore(a,criarForma(FORMA_CIRCULO,
        criaCirculo(5,0,0,1,"b","p")));

    pushArvore(a,criarForma(FORMA_CIRCULO,
        criaCirculo(2,0,0,1,"b","p")));

    pushArvore(a,criarForma(FORMA_CIRCULO,
        criaCirculo(9,0,0,1,"b","p")));

    TEST_ASSERT_EQUAL(3,tamanhoArvore(a));

    killArvore(a);
}

void test_pushArvore_arvoreNULL(void){

    FORMA f = criarForma(
        FORMA_CIRCULO,
        criaCirculo(1,0,0,1,"b","p")
    );

    pushArvore(NULL,f);

    killForma(f);
}

void test_pushArvore_formaNULL(void){

    ARVORE a = criarArvore();

    pushArvore(a,NULL);

    TEST_ASSERT_EQUAL(0,tamanhoArvore(a));

    killArvore(a);
}

/*==================================================
 BUSCA
==================================================*/

void test_buscaId_existente(void){

    ARVORE a = criarArvore();

    FORMA f = criarForma(
        FORMA_CIRCULO,
        criaCirculo(15,0,0,1,"b","p")
    );

    pushArvore(a,f);

    TEST_ASSERT_EQUAL_PTR(f,buscaIdArvore(a,15));

    killArvore(a);
}

void test_buscaId_inexistente(void){

    ARVORE a = criarArvore();

    TEST_ASSERT_NULL(buscaIdArvore(a,50));

    killArvore(a);
}

void test_buscaId_arvoreNULL(void){

    TEST_ASSERT_NULL(buscaIdArvore(NULL,5));
}

/*==================================================
 POP
==================================================*/

void test_popId_folha(void){

    ARVORE a = criarArvore();

    FORMA f1=criarForma(FORMA_CIRCULO,
        criaCirculo(10,0,0,1,"b","p"));

    FORMA f2=criarForma(FORMA_CIRCULO,
        criaCirculo(5,0,10,1,"b","p"));

    pushArvore(a,f1);
    pushArvore(a,f2);

    FORMA removida=popIdArvore(a,5);

    TEST_ASSERT_EQUAL_PTR(f2,removida);
    TEST_ASSERT_EQUAL(1,tamanhoArvore(a));

    killForma(removida);
    killArvore(a);
}

void test_popId_raiz(void){

    ARVORE a=criarArvore();

    FORMA f=criarForma(FORMA_CIRCULO,
        criaCirculo(10,0,0,1,"b","p"));

    pushArvore(a,f);

    TEST_ASSERT_EQUAL_PTR(f,popIdArvore(a,10));
    TEST_ASSERT_EQUAL(0,tamanhoArvore(a));
    TEST_ASSERT_EQUAL(1,arvoreVazia(a));

    killForma(f);
    killArvore(a);
}

void test_popId_inexistente(void){

    ARVORE a=criarArvore();

    TEST_ASSERT_NULL(popIdArvore(a,80));

    killArvore(a);
}

void test_popId_arvoreNULL(void){

    TEST_ASSERT_NULL(popIdArvore(NULL,5));
}

/*==================================================
 VETOR
==================================================*/

void test_arvoreParaVetor(void){

    ARVORE a=criarArvore();

    pushArvore(a,criarForma(FORMA_CIRCULO,
        criaCirculo(3,0,30,1,"b","p")));

    pushArvore(a,criarForma(FORMA_CIRCULO,
        criaCirculo(1,0,10,1,"b","p")));

    pushArvore(a,criarForma(FORMA_CIRCULO,
        criaCirculo(5,0,50,1,"b","p")));

    FORMA vet[3];

    TEST_ASSERT_EQUAL(3,arvoreParaVetor(a,vet));

    TEST_ASSERT_EQUAL(1,getIdForma(vet[0]));
    TEST_ASSERT_EQUAL(3,getIdForma(vet[1]));
    TEST_ASSERT_EQUAL(5,getIdForma(vet[2]));

    killArvore(a);
}

void test_arvoreParaVetor_arvoreNULL(void){

    FORMA vet[5];

    TEST_ASSERT_EQUAL(-1,arvoreParaVetor(NULL,vet));
}

/*==================================================
 TAMANHO
==================================================*/

void test_tamanhoArvore(void){

    ARVORE a=criarArvore();

    TEST_ASSERT_EQUAL(0,tamanhoArvore(a));

    pushArvore(a,
        criarForma(FORMA_CIRCULO,
        criaCirculo(1,0,0,1,"b","p")));

    TEST_ASSERT_EQUAL(1,tamanhoArvore(a));

    killArvore(a);
}

void test_tamanhoArvore_NULL(void){

    TEST_ASSERT_EQUAL(-1,tamanhoArvore(NULL));
}

/*==================================================
 VAZIA
==================================================*/

void test_arvoreVazia(void){

    ARVORE a=criarArvore();

    TEST_ASSERT_EQUAL(1,arvoreVazia(a));

    pushArvore(a,
        criarForma(FORMA_CIRCULO,
        criaCirculo(1,0,0,1,"b","p")));

    TEST_ASSERT_EQUAL(0,arvoreVazia(a));

    killArvore(a);
}

void test_arvoreVazia_NULL(void){

    TEST_ASSERT_EQUAL(-1,arvoreVazia(NULL));
}

/*==================================================
 LIMPAR
==================================================*/

void test_limparArvore(void){

    ARVORE a=criarArvore();

    for(int i=1;i<=10;i++){

        pushArvore(a,
            criarForma(FORMA_CIRCULO,
            criaCirculo(i,0,0,1,"b","p")));
    }

    limparArvore(a);

    TEST_ASSERT_EQUAL(0,tamanhoArvore(a));
    TEST_ASSERT_EQUAL(1,arvoreVazia(a));

    killArvore(a);
}

void test_limparArvore_NULL(void){

    limparArvore(NULL);

    TEST_PASS();
}

/*==================================================
 MAIOR ID
==================================================*/

void test_obterMaiorId(void){

    ARVORE a=criarArvore();

    pushArvore(a,
        criarForma(FORMA_CIRCULO,
        criaCirculo(2,0,20,1,"b","p")));

    pushArvore(a,
        criarForma(FORMA_CIRCULO,
        criaCirculo(80,0,80,1,"b","p")));

    pushArvore(a,
        criarForma(FORMA_CIRCULO,
        criaCirculo(30,0,30,1,"b","p")));

    TEST_ASSERT_EQUAL(80,obterMaiorIdArvore(a));

    killArvore(a);
}

void test_obterMaiorId_vazia(void){

    ARVORE a=criarArvore();

    TEST_ASSERT_EQUAL(0,obterMaiorIdArvore(a));

    killArvore(a);
}

/*==================================================
 KILL
==================================================*/

void test_killArvore(void){

    ARVORE a=criarArvore();

    pushArvore(a,
        criarForma(FORMA_CIRCULO,
        criaCirculo(1,0,0,1,"b","p")));

    killArvore(a);

    TEST_PASS();
}

/*==================================================
 MAIN
==================================================*/

int main(){

    UNITY_BEGIN();

    RUN_TEST(test_criarArvore);

    RUN_TEST(test_pushArvore_umElemento);
    RUN_TEST(test_pushArvore_variosElementos);
    RUN_TEST(test_pushArvore_arvoreNULL);
    RUN_TEST(test_pushArvore_formaNULL);

    RUN_TEST(test_buscaId_existente);
    RUN_TEST(test_buscaId_inexistente);
    RUN_TEST(test_buscaId_arvoreNULL);

    RUN_TEST(test_popId_folha);
    RUN_TEST(test_popId_raiz);
    RUN_TEST(test_popId_inexistente);
    RUN_TEST(test_popId_arvoreNULL);

    RUN_TEST(test_arvoreParaVetor);
    RUN_TEST(test_arvoreParaVetor_arvoreNULL);

    RUN_TEST(test_tamanhoArvore);
    RUN_TEST(test_tamanhoArvore_NULL);

    RUN_TEST(test_arvoreVazia);
    RUN_TEST(test_arvoreVazia_NULL);

    RUN_TEST(test_limparArvore);
    RUN_TEST(test_limparArvore_NULL);

    RUN_TEST(test_obterMaiorId);
    RUN_TEST(test_obterMaiorId_vazia);

    RUN_TEST(test_killArvore);

    return UNITY_END();
}