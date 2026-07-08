#include "unity.h"
#include "../formas/circulo.h"

#define PI 3.14159265358979323846

void setUp(void){}
void tearDown(void){}

/*==================================================
  CRIAÇÃO
==================================================*/

void test_criaCirculo_deveCriarCirculoValido(void){
    CIRCULO c = criaCirculo(10,20,30,5,"black","red");

    TEST_ASSERT_NOT_NULL(c);

    kill_C(c);
}

void test_criaCirculo_deveInicializarTodosOsCampos(void){
    CIRCULO c = criaCirculo(1,2,3,4,"blue","yellow");

    TEST_ASSERT_EQUAL_INT(1,getId_C(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001,2,getX_C(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001,3,getY_C(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001,4,getR_C(c));
    TEST_ASSERT_EQUAL_STRING("blue",getCorB_C(c));
    TEST_ASSERT_EQUAL_STRING("yellow",getCorP_C(c));

    kill_C(c);
}

/*==================================================
  GETTERS
==================================================*/

void test_getLargura_deveRetornarDiametro(void){
    CIRCULO c = criaCirculo(1,0,0,8,"a","b");

    TEST_ASSERT_FLOAT_WITHIN(0.001,16,getLargura_C(c));

    kill_C(c);
}

void test_getAltura_deveRetornarDiametro(void){
    CIRCULO c = criaCirculo(1,0,0,8,"a","b");

    TEST_ASSERT_FLOAT_WITHIN(0.001,16,getAltura_C(c));

    kill_C(c);
}

/*==================================================
  ÁREA
==================================================*/

void test_calcularArea_deveCalcularCorretamente(void){
    CIRCULO c = criaCirculo(1,0,0,2,"a","b");

    TEST_ASSERT_FLOAT_WITHIN(
        0.001,
        PI*4,
        calcularArea_C(c)
    );

    kill_C(c);
}

void test_calcularArea_raioZero(void){
    CIRCULO c = criaCirculo(1,0,0,0,"a","b");

    TEST_ASSERT_FLOAT_WITHIN(0.001,0,calcularArea_C(c));

    kill_C(c);
}

/*==================================================
  SETTERS
==================================================*/

void test_setId(void){
    CIRCULO c = criaCirculo(1,0,0,1,"a","b");

    setId_C(c,99);

    TEST_ASSERT_EQUAL_INT(99,getId_C(c));

    kill_C(c);
}

void test_setX(void){
    CIRCULO c = criaCirculo(1,0,0,1,"a","b");

    setX_C(c,15.5);

    TEST_ASSERT_FLOAT_WITHIN(0.001,15.5,getX_C(c));

    kill_C(c);
}

void test_setY(void){
    CIRCULO c = criaCirculo(1,0,0,1,"a","b");

    setY_C(c,22.4);

    TEST_ASSERT_FLOAT_WITHIN(0.001,22.4,getY_C(c));

    kill_C(c);
}

void test_setRaio(void){
    CIRCULO c = criaCirculo(1,0,0,1,"a","b");

    setR_C(c,10);

    TEST_ASSERT_FLOAT_WITHIN(0.001,10,getR_C(c));

    kill_C(c);
}

void test_setRaio_deveAlterarArea(void){
    CIRCULO c = criaCirculo(1,0,0,1,"a","b");

    setR_C(c,5);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001,
        PI*25,
        calcularArea_C(c)
    );

    kill_C(c);
}

void test_setCorB(void){
    CIRCULO c = criaCirculo(1,0,0,1,"a","b");

    setCorB_C(c,"white");

    TEST_ASSERT_EQUAL_STRING("white",getCorB_C(c));

    kill_C(c);
}

void test_setCorP(void){
    CIRCULO c = criaCirculo(1,0,0,1,"a","b");

    setCorP_C(c,"green");

    TEST_ASSERT_EQUAL_STRING("green",getCorP_C(c));

    kill_C(c);
}

/*==================================================
  DESTRUTOR
==================================================*/

void test_killCirculo(void){
    CIRCULO c = criaCirculo(1,0,0,1,"a","b");

    kill_C(c);

    TEST_PASS();
}

/*==================================================
  MAIN
==================================================*/

int main(void){

    UNITY_BEGIN();

    RUN_TEST(test_criaCirculo_deveCriarCirculoValido);
    RUN_TEST(test_criaCirculo_deveInicializarTodosOsCampos);

    RUN_TEST(test_getLargura_deveRetornarDiametro);
    RUN_TEST(test_getAltura_deveRetornarDiametro);

    RUN_TEST(test_calcularArea_deveCalcularCorretamente);
    RUN_TEST(test_calcularArea_raioZero);

    RUN_TEST(test_setId);
    RUN_TEST(test_setX);
    RUN_TEST(test_setY);
    RUN_TEST(test_setRaio);
    RUN_TEST(test_setRaio_deveAlterarArea);
    RUN_TEST(test_setCorB);
    RUN_TEST(test_setCorP);

    RUN_TEST(test_killCirculo);

    return UNITY_END();
}