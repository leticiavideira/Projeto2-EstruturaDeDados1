#include "unity.h"
#include "../formas/retangulo.h"

void setUp(void){}
void tearDown(void){}

/*==================================================
  CRIAÇÃO
==================================================*/

void test_criaRetangulo_deveCriarRetanguloValido(void){
    RETANGULO r = criaRetangulo(1,10,20,30,40,"black","red");

    TEST_ASSERT_NOT_NULL(r);

    kill_R(r);
}

void test_criaRetangulo_deveInicializarTodosOsCampos(void){
    RETANGULO r = criaRetangulo(5,1,2,3,4,"blue","yellow");

    TEST_ASSERT_EQUAL_INT(5,getId_R(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001,1,getX_R(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001,2,getY_R(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001,3,getW_R(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001,4,getH_R(r));
    TEST_ASSERT_EQUAL_STRING("blue",getCorB_R(r));
    TEST_ASSERT_EQUAL_STRING("yellow",getCorP_R(r));

    kill_R(r);
}

/*==================================================
  GETTERS
==================================================*/

void test_getId(void){
    RETANGULO r = criaRetangulo(10,0,0,1,1,"a","b");

    TEST_ASSERT_EQUAL_INT(10,getId_R(r));

    kill_R(r);
}

void test_getX(void){
    RETANGULO r = criaRetangulo(1,12.5,0,1,1,"a","b");

    TEST_ASSERT_FLOAT_WITHIN(0.001,12.5,getX_R(r));

    kill_R(r);
}

void test_getY(void){
    RETANGULO r = criaRetangulo(1,0,18.2,1,1,"a","b");

    TEST_ASSERT_FLOAT_WITHIN(0.001,18.2,getY_R(r));

    kill_R(r);
}

void test_getLargura(void){
    RETANGULO r = criaRetangulo(1,0,0,25,1,"a","b");

    TEST_ASSERT_FLOAT_WITHIN(0.001,25,getW_R(r));

    kill_R(r);
}

void test_getAltura(void){
    RETANGULO r = criaRetangulo(1,0,0,1,15,"a","b");

    TEST_ASSERT_FLOAT_WITHIN(0.001,15,getH_R(r));

    kill_R(r);
}

void test_getCorB(void){
    RETANGULO r = criaRetangulo(1,0,0,1,1,"preto","vermelho");

    TEST_ASSERT_EQUAL_STRING("preto",getCorB_R(r));

    kill_R(r);
}

void test_getCorP(void){
    RETANGULO r = criaRetangulo(1,0,0,1,1,"preto","verde");

    TEST_ASSERT_EQUAL_STRING("verde",getCorP_R(r));

    kill_R(r);
}

/*==================================================
  ÁREA
==================================================*/

void test_calcularArea(void){
    RETANGULO r = criaRetangulo(1,0,0,10,5,"a","b");

    TEST_ASSERT_FLOAT_WITHIN(0.001,50,calcularArea_R(r));

    kill_R(r);
}

void test_calcularArea_dimensoesZero(void){
    RETANGULO r = criaRetangulo(1,0,0,0,0,"a","b");

    TEST_ASSERT_FLOAT_WITHIN(0.001,0,calcularArea_R(r));

    kill_R(r);
}

/*==================================================
  SETTERS
==================================================*/

void test_setId(void){
    RETANGULO r = criaRetangulo(1,0,0,1,1,"a","b");

    setId_R(r,99);

    TEST_ASSERT_EQUAL_INT(99,getId_R(r));

    kill_R(r);
}

void test_setX(void){
    RETANGULO r = criaRetangulo(1,0,0,1,1,"a","b");

    setX_R(r,30);

    TEST_ASSERT_FLOAT_WITHIN(0.001,30,getX_R(r));

    kill_R(r);
}

void test_setY(void){
    RETANGULO r = criaRetangulo(1,0,0,1,1,"a","b");

    setY_R(r,18);

    TEST_ASSERT_FLOAT_WITHIN(0.001,18,getY_R(r));

    kill_R(r);
}

void test_setLargura(void){
    RETANGULO r = criaRetangulo(1,0,0,1,1,"a","b");

    setW_R(r,12);

    TEST_ASSERT_FLOAT_WITHIN(0.001,12,getW_R(r));

    kill_R(r);
}

void test_setAltura(void){
    RETANGULO r = criaRetangulo(1,0,0,1,1,"a","b");

    setH_R(r,9);

    TEST_ASSERT_FLOAT_WITHIN(0.001,9,getH_R(r));

    kill_R(r);
}

void test_setCorB(void){
    RETANGULO r = criaRetangulo(1,0,0,1,1,"a","b");

    setCorB_R(r,"white");

    TEST_ASSERT_EQUAL_STRING("white",getCorB_R(r));

    kill_R(r);
}

void test_setCorP(void){
    RETANGULO r = criaRetangulo(1,0,0,1,1,"a","b");

    setCorP_R(r,"green");

    TEST_ASSERT_EQUAL_STRING("green",getCorP_R(r));

    kill_R(r);
}

void test_setDimensoes_deveAlterarArea(void){
    RETANGULO r = criaRetangulo(1,0,0,2,3,"a","b");

    setW_R(r,10);
    setH_R(r,20);

    TEST_ASSERT_FLOAT_WITHIN(0.001,200,calcularArea_R(r));

    kill_R(r);
}

/*==================================================
  DESTRUTOR
==================================================*/

void test_killRetangulo(void){
    RETANGULO r = criaRetangulo(1,0,0,1,1,"a","b");

    kill_R(r);

    TEST_PASS();
}

/*==================================================
  MAIN
==================================================*/

int main(void){

    UNITY_BEGIN();

    RUN_TEST(test_criaRetangulo_deveCriarRetanguloValido);
    RUN_TEST(test_criaRetangulo_deveInicializarTodosOsCampos);

    RUN_TEST(test_getId);
    RUN_TEST(test_getX);
    RUN_TEST(test_getY);
    RUN_TEST(test_getLargura);
    RUN_TEST(test_getAltura);
    RUN_TEST(test_getCorB);
    RUN_TEST(test_getCorP);

    RUN_TEST(test_calcularArea);
    RUN_TEST(test_calcularArea_dimensoesZero);

    RUN_TEST(test_setId);
    RUN_TEST(test_setX);
    RUN_TEST(test_setY);
    RUN_TEST(test_setLargura);
    RUN_TEST(test_setAltura);
    RUN_TEST(test_setCorB);
    RUN_TEST(test_setCorP);
    RUN_TEST(test_setDimensoes_deveAlterarArea);

    RUN_TEST(test_killRetangulo);

    return UNITY_END();
}