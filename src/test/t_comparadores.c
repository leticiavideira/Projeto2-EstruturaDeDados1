#include "unity.h"

#include "../gerais/comparadores.h"
#include "../formas/circulo.h"
#include "../formas/forma.h"

void setUp(void){}
void tearDown(void){}

/*==================================================
 AUXILIAR
==================================================*/

FORMA criaFormaTeste(int id,double x,double y,double r,char *cor){

    return criarForma(
        FORMA_CIRCULO,
        criaCirculo(id,x,y,r,"black",cor)
    );
}

/*==================================================
 DEFAULT
==================================================*/

void test_comparaDefault_yMenor(){

    FORMA a=criaFormaTeste(1,10,5,2,"red");
    FORMA b=criaFormaTeste(2,10,20,2,"red");

    TEST_ASSERT_LESS_THAN(0,comparaDefault(a,b));

    killForma(a);
    killForma(b);
}

void test_comparaDefault_xMenor(){

    FORMA a=criaFormaTeste(1,5,10,2,"red");
    FORMA b=criaFormaTeste(2,20,10,2,"red");

    TEST_ASSERT_LESS_THAN(0,comparaDefault(a,b));

    killForma(a);
    killForma(b);
}

void test_comparaDefault_areaMenor(){

    FORMA a=criaFormaTeste(1,10,10,1,"red");
    FORMA b=criaFormaTeste(2,10,10,5,"red");

    TEST_ASSERT_LESS_THAN(0,comparaDefault(a,b));

    killForma(a);
    killForma(b);
}

void test_comparaDefault_iguais(){

    FORMA a=criaFormaTeste(1,10,10,2,"red");
    FORMA b=criaFormaTeste(2,10,10,2,"red");

    TEST_ASSERT_EQUAL(0,comparaDefault(a,b));

    killForma(a);
    killForma(b);
}

void test_comparaDefault_NULL(){

    TEST_ASSERT_EQUAL(0,comparaDefault(NULL,NULL));
}

/*==================================================
 AREA
==================================================*/

void test_comparaArea(){

    FORMA a=criaFormaTeste(1,0,0,2,"red");
    FORMA b=criaFormaTeste(2,0,0,5,"red");

    TEST_ASSERT_LESS_THAN(0,comparaArea(a,b));
    TEST_ASSERT_GREATER_THAN(0,comparaArea(b,a));

    killForma(a);
    killForma(b);
}

void test_comparaArea_iguais(){

    FORMA a=criaFormaTeste(1,0,0,2,"red");
    FORMA b=criaFormaTeste(2,5,8,2,"blue");

    TEST_ASSERT_EQUAL(0,comparaArea(a,b));

    killForma(a);
    killForma(b);
}

void test_comparaArea_NULL(){

    TEST_ASSERT_EQUAL(0,comparaArea(NULL,NULL));
}

/*==================================================
 LARGURA
==================================================*/

void test_comparaLargura(){

    FORMA a=criaFormaTeste(1,0,0,2,"red");
    FORMA b=criaFormaTeste(2,0,0,5,"red");

    TEST_ASSERT_LESS_THAN(0,comparaLargura(a,b));

    killForma(a);
    killForma(b);
}

void test_comparaLargura_iguais(){

    FORMA a=criaFormaTeste(1,0,0,3,"red");
    FORMA b=criaFormaTeste(2,5,5,3,"blue");

    TEST_ASSERT_EQUAL(0,comparaLargura(a,b));

    killForma(a);
    killForma(b);
}

void test_comparaLargura_NULL(){

    TEST_ASSERT_EQUAL(0,comparaLargura(NULL,NULL));
}

/*==================================================
 ALTURA
==================================================*/

void test_comparaAltura(){

    FORMA a=criaFormaTeste(1,0,0,2,"red");
    FORMA b=criaFormaTeste(2,0,0,5,"red");

    TEST_ASSERT_LESS_THAN(0,comparaAltura(a,b));

    killForma(a);
    killForma(b);
}

void test_comparaAltura_iguais(){

    FORMA a=criaFormaTeste(1,0,0,3,"red");
    FORMA b=criaFormaTeste(2,5,5,3,"blue");

    TEST_ASSERT_EQUAL(0,comparaAltura(a,b));

    killForma(a);
    killForma(b);
}

void test_comparaAltura_NULL(){

    TEST_ASSERT_EQUAL(0,comparaAltura(NULL,NULL));
}

/*==================================================
 COR
==================================================*/

void test_comparaCor(){

    FORMA a=criaFormaTeste(1,0,0,2,"blue");
    FORMA b=criaFormaTeste(2,0,0,2,"red");

    TEST_ASSERT_LESS_THAN(0,comparaCor(a,b));

    killForma(a);
    killForma(b);
}

void test_comparaCor_iguais(){

    FORMA a=criaFormaTeste(1,0,0,2,"green");
    FORMA b=criaFormaTeste(2,8,5,5,"green");

    TEST_ASSERT_EQUAL(0,comparaCor(a,b));

    killForma(a);
    killForma(b);
}

void test_comparaCor_NULL(){

    TEST_ASSERT_EQUAL(0,comparaCor(NULL,NULL));
}

/*==================================================
 OBTER COMPARADOR
==================================================*/

void test_obterComparador_default(){

    TEST_ASSERT_EQUAL_PTR(comparaDefault,
        obterComparador(DEFAULT));
}

void test_obterComparador_area(){

    TEST_ASSERT_EQUAL_PTR(comparaArea,
        obterComparador(AREA));
}

void test_obterComparador_largura(){

    TEST_ASSERT_EQUAL_PTR(comparaLargura,
        obterComparador(LARGURA));
}

void test_obterComparador_altura(){

    TEST_ASSERT_EQUAL_PTR(comparaAltura,
        obterComparador(ALTURA));
}

void test_obterComparador_cor(){

    TEST_ASSERT_EQUAL_PTR(comparaCor,
        obterComparador(COR));
}

void test_obterComparador_invalido(){

    TEST_ASSERT_EQUAL_PTR(
        comparaDefault,
        obterComparador((CRITERIO)100)
    );
}

/*==================================================
 MAIN
==================================================*/

int main(){

    UNITY_BEGIN();

    RUN_TEST(test_comparaDefault_yMenor);
    RUN_TEST(test_comparaDefault_xMenor);
    RUN_TEST(test_comparaDefault_areaMenor);
    RUN_TEST(test_comparaDefault_iguais);
    RUN_TEST(test_comparaDefault_NULL);

    RUN_TEST(test_comparaArea);
    RUN_TEST(test_comparaArea_iguais);
    RUN_TEST(test_comparaArea_NULL);

    RUN_TEST(test_comparaLargura);
    RUN_TEST(test_comparaLargura_iguais);
    RUN_TEST(test_comparaLargura_NULL);

    RUN_TEST(test_comparaAltura);
    RUN_TEST(test_comparaAltura_iguais);
    RUN_TEST(test_comparaAltura_NULL);

    RUN_TEST(test_comparaCor);
    RUN_TEST(test_comparaCor_iguais);
    RUN_TEST(test_comparaCor_NULL);

    RUN_TEST(test_obterComparador_default);
    RUN_TEST(test_obterComparador_area);
    RUN_TEST(test_obterComparador_largura);
    RUN_TEST(test_obterComparador_altura);
    RUN_TEST(test_obterComparador_cor);
    RUN_TEST(test_obterComparador_invalido);

    return UNITY_END();
}