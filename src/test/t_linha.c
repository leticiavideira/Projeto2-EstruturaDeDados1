#include "unity.h"
#include "../formas/linha.h"
#include <math.h>

void setUp(void){}
void tearDown(void){}

/*==================================================
  CRIAÇÃO
==================================================*/

void test_criaLinha_deveCriarLinhaValida(void){
    LINHA l = criaLinha(1,10,20,30,40,"black");

    TEST_ASSERT_NOT_NULL(l);

    kill_L(l);
}

void test_criaLinha_deveInicializarTodosOsCampos(void){
    LINHA l = criaLinha(5,1,2,3,4,"blue");

    TEST_ASSERT_EQUAL_INT(5,getId_L(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001,1,getX1_L(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001,2,getY1_L(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001,3,getX2_L(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001,4,getY2_L(l));
    TEST_ASSERT_EQUAL_STRING("blue",getCor_L(l));

    kill_L(l);
}

/*==================================================
  GETTERS
==================================================*/

void test_getId(void){
    LINHA l = criaLinha(10,0,0,1,1,"a");

    TEST_ASSERT_EQUAL_INT(10,getId_L(l));

    kill_L(l);
}

void test_getX1(void){
    LINHA l = criaLinha(1,12.5,0,1,1,"a");

    TEST_ASSERT_FLOAT_WITHIN(0.001,12.5,getX1_L(l));

    kill_L(l);
}

void test_getY1(void){
    LINHA l = criaLinha(1,0,18.2,1,1,"a");

    TEST_ASSERT_FLOAT_WITHIN(0.001,18.2,getY1_L(l));

    kill_L(l);
}

void test_getX2(void){
    LINHA l = criaLinha(1,0,0,25.5,1,"a");

    TEST_ASSERT_FLOAT_WITHIN(0.001,25.5,getX2_L(l));

    kill_L(l);
}

void test_getY2(void){
    LINHA l = criaLinha(1,0,0,1,30.7,"a");

    TEST_ASSERT_FLOAT_WITHIN(0.001,30.7,getY2_L(l));

    kill_L(l);
}

void test_getCor(void){
    LINHA l = criaLinha(1,0,0,1,1,"red");

    TEST_ASSERT_EQUAL_STRING("red",getCor_L(l));

    kill_L(l);
}

void test_getLargura(void){
    LINHA l = criaLinha(1,2,0,8,0,"a");

    TEST_ASSERT_FLOAT_WITHIN(0.001,6,getLargura_L(l));

    kill_L(l);
}

void test_getAltura(void){
    LINHA l = criaLinha(1,0,3,0,10,"a");

    TEST_ASSERT_FLOAT_WITHIN(0.001,1.5,getAltura_L(l));

    kill_L(l);
}

/*==================================================
  ÁREA
==================================================*/

void test_calcularArea(void){
    LINHA l = criaLinha(1,0,0,3,4,"a");

    /* comprimento = 5
       area = 5 * 1.5 = 7.5 */

    TEST_ASSERT_FLOAT_WITHIN(0.001,7.5,calcularArea_L(l));

    kill_L(l);
}

void test_calcularArea_linhaHorizontal(void){
    LINHA l = criaLinha(1,0,0,10,0,"a");

    TEST_ASSERT_FLOAT_WITHIN(0.001,15,calcularArea_L(l));

    kill_L(l);
}

/*==================================================
  SETTERS
==================================================*/

void test_setId(void){
    LINHA l = criaLinha(1,0,0,1,1,"a");

    setId_L(l,99);

    TEST_ASSERT_EQUAL_INT(99,getId_L(l));

    kill_L(l);
}

void test_setX1(void){
    LINHA l = criaLinha(1,0,0,1,1,"a");

    setX1_L(l,20);

    TEST_ASSERT_FLOAT_WITHIN(0.001,20,getX1_L(l));

    kill_L(l);
}

void test_setY1(void){
    LINHA l = criaLinha(1,0,0,1,1,"a");

    setY1_L(l,30);

    TEST_ASSERT_FLOAT_WITHIN(0.001,30,getY1_L(l));

    kill_L(l);
}

void test_setX2(void){
    LINHA l = criaLinha(1,0,0,1,1,"a");

    setX2_L(l,40);

    TEST_ASSERT_FLOAT_WITHIN(0.001,40,getX2_L(l));

    kill_L(l);
}

void test_setY2(void){
    LINHA l = criaLinha(1,0,0,1,1,"a");

    setY2_L(l,50);

    TEST_ASSERT_FLOAT_WITHIN(0.001,50,getY2_L(l));

    kill_L(l);
}

void test_setCor(void){
    LINHA l = criaLinha(1,0,0,1,1,"black");

    setCor_L(l,"green");

    TEST_ASSERT_EQUAL_STRING("green",getCor_L(l));

    kill_L(l);
}

void test_setPontos_deveAlterarArea(void){
    LINHA l = criaLinha(1,0,0,1,1,"a");

    setX1_L(l,0);
    setY1_L(l,0);
    setX2_L(l,6);
    setY2_L(l,8);

    /* comprimento = 10
       area = 15 */

    TEST_ASSERT_FLOAT_WITHIN(0.001,15,calcularArea_L(l));

    kill_L(l);
}

/*==================================================
  DESTRUTOR
==================================================*/

void test_killLinha(void){
    LINHA l = criaLinha(1,0,0,1,1,"a");

    kill_L(l);

    TEST_PASS();
}

/*==================================================
  MAIN
==================================================*/

int main(void){

    UNITY_BEGIN();

    RUN_TEST(test_criaLinha_deveCriarLinhaValida);
    RUN_TEST(test_criaLinha_deveInicializarTodosOsCampos);

    RUN_TEST(test_getId);
    RUN_TEST(test_getX1);
    RUN_TEST(test_getY1);
    RUN_TEST(test_getX2);
    RUN_TEST(test_getY2);
    RUN_TEST(test_getCor);
    RUN_TEST(test_getLargura);
    RUN_TEST(test_getAltura);

    RUN_TEST(test_calcularArea);
    RUN_TEST(test_calcularArea_linhaHorizontal);

    RUN_TEST(test_setId);
    RUN_TEST(test_setX1);
    RUN_TEST(test_setY1);
    RUN_TEST(test_setX2);
    RUN_TEST(test_setY2);
    RUN_TEST(test_setCor);
    RUN_TEST(test_setPontos_deveAlterarArea);

    RUN_TEST(test_killLinha);

    return UNITY_END();
}