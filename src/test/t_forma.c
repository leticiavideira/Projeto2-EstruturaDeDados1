#include "unity.h"

#include "../formas/forma.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/linha.h"
#include "../formas/texto.h"

void setUp(void){}
void tearDown(void){}

/*==================================================
 CRIAÇÃO
==================================================*/

void test_criarForma(void){

    CIRCULO c = criaCirculo(1,10,20,5,"black","red");

    FORMA f = criarForma(FORMA_CIRCULO,c);

    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL(FORMA_CIRCULO,getTipoForma(f));
    TEST_ASSERT_EQUAL_PTR(c,getDataForma(f));

    killForma(f);
}

void test_criarForma_dataNULL(void){

    TEST_ASSERT_NULL(criarForma(FORMA_CIRCULO,NULL));
}

/*==================================================
 GETTERS
==================================================*/

void test_getters_circulo(void){

    FORMA f = criarForma(
        FORMA_CIRCULO,
        criaCirculo(15,10,20,5,"black","red")
    );

    TEST_ASSERT_EQUAL(15,getIdForma(f));
    TEST_ASSERT_FLOAT_WITHIN(0.001,10,getXForma(f));
    TEST_ASSERT_FLOAT_WITHIN(0.001,20,getYForma(f));
    TEST_ASSERT_FLOAT_WITHIN(0.001,5,getRaioForma(f));
    TEST_ASSERT_FLOAT_WITHIN(0.001,10,getLarguraForma(f));
    TEST_ASSERT_FLOAT_WITHIN(0.001,10,getAlturaForma(f));

    TEST_ASSERT_EQUAL_STRING("black",getCorBordaForma(f));
    TEST_ASSERT_EQUAL_STRING("red",getCorPreenchimentoForma(f));
    TEST_ASSERT_EQUAL_STRING("circulo",getNomeForma(f));

    killForma(f);
}

void test_getters_retangulo(void){

    FORMA f = criarForma(
        FORMA_RETANGULO,
        criaRetangulo(8,5,6,20,10,"blue","green")
    );

    TEST_ASSERT_EQUAL(8,getIdForma(f));
    TEST_ASSERT_FLOAT_WITHIN(0.001,20,getLarguraForma(f));
    TEST_ASSERT_FLOAT_WITHIN(0.001,10,getAlturaForma(f));
    TEST_ASSERT_EQUAL_STRING("blue",getCorBordaForma(f));
    TEST_ASSERT_EQUAL_STRING("green",getCorPreenchimentoForma(f));

    killForma(f);
}

void test_getters_linha(void){

    FORMA f = criarForma(
        FORMA_LINHA,
        criaLinha(3,1,2,5,6,"red")
    );

    TEST_ASSERT_EQUAL(3,getIdForma(f));
    TEST_ASSERT_FLOAT_WITHIN(0.001,5,getX2Forma(f));
    TEST_ASSERT_FLOAT_WITHIN(0.001,6,getY2Forma(f));
    TEST_ASSERT_EQUAL_STRING("red",getCorBordaForma(f));

    killForma(f);
}

void test_getters_texto(void){

    FORMA f = criarForma(
        FORMA_TEXTO,
        criaTexto(4,7,8,"black","yellow",'m',"teste")
    );

    TEST_ASSERT_EQUAL(4,getIdForma(f));
    TEST_ASSERT_EQUAL_CHAR('m',getAncoraTextoForma(f));
    TEST_ASSERT_EQUAL_STRING("teste",getConteudoTextoForma(f));

    killForma(f);
}

void test_getters_NULL(void){

    TEST_ASSERT_EQUAL(-1,getIdForma(NULL));
    TEST_ASSERT_EQUAL_FLOAT(-1,getXForma(NULL));
    TEST_ASSERT_EQUAL_FLOAT(-1,getYForma(NULL));
    TEST_ASSERT_EQUAL_FLOAT(-1,getAreaForma(NULL));
    TEST_ASSERT_NULL(getCorBordaForma(NULL));
    TEST_ASSERT_NULL(getCorPreenchimentoForma(NULL));
    TEST_ASSERT_NULL(getNomeForma(NULL));
}

/*==================================================
 SETTERS
==================================================*/

void test_setters(void){

    FORMA f = criarForma(
        FORMA_RETANGULO,
        criaRetangulo(1,0,0,10,5,"black","red")
    );

    setIdForma(f,99);
    setCorBordaForma(f,"white");
    setCorPreenchimentoForma(f,"green");

    TEST_ASSERT_EQUAL(99,getIdForma(f));
    TEST_ASSERT_EQUAL_STRING("white",getCorBordaForma(f));
    TEST_ASSERT_EQUAL_STRING("green",getCorPreenchimentoForma(f));

    killForma(f);
}

/*==================================================
 MOVER
==================================================*/

void test_moverForma(void){

    FORMA f = criarForma(
        FORMA_CIRCULO,
        criaCirculo(1,10,20,5,"a","b")
    );

    moverForma(f,5,-10);

    TEST_ASSERT_FLOAT_WITHIN(0.001,15,getXForma(f));
    TEST_ASSERT_FLOAT_WITHIN(0.001,10,getYForma(f));

    killForma(f);
}

/*==================================================
 ÂNCORA
==================================================*/

void test_getAncoraForma(void){

    double x,y;

    FORMA f = criarForma(
        FORMA_CIRCULO,
        criaCirculo(1,8,9,2,"a","b")
    );

    getAncoraForma(f,&x,&y);

    TEST_ASSERT_FLOAT_WITHIN(0.001,8,x);
    TEST_ASSERT_FLOAT_WITHIN(0.001,9,y);

    killForma(f);
}

/*==================================================
 PRINT
==================================================*/

void test_printFormaTXT(void){

    FILE *fp = fopen("testeForma.txt","w");

    TEST_ASSERT_NOT_NULL(fp);

    FORMA f = criarForma(
        FORMA_CIRCULO,
        criaCirculo(1,0,0,2,"a","b")
    );

    printFormaTXT(fp,f);

    fclose(fp);

    killForma(f);

    TEST_PASS();
}

/*==================================================
 KILL
==================================================*/

void test_killForma(void){

    FORMA f = criarForma(
        FORMA_CIRCULO,
        criaCirculo(1,0,0,1,"a","b")
    );

    killForma(f);

    TEST_PASS();
}

/*==================================================
 MAIN
==================================================*/

int main(void){

    UNITY_BEGIN();

    RUN_TEST(test_criarForma);
    RUN_TEST(test_criarForma_dataNULL);

    RUN_TEST(test_getters_circulo);
    RUN_TEST(test_getters_retangulo);
    RUN_TEST(test_getters_linha);
    RUN_TEST(test_getters_texto);
    RUN_TEST(test_getters_NULL);

    RUN_TEST(test_setters);

    RUN_TEST(test_moverForma);

    RUN_TEST(test_getAncoraForma);

    RUN_TEST(test_printFormaTXT);

    RUN_TEST(test_killForma);

    return UNITY_END();
}