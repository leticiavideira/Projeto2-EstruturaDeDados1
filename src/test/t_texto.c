#include "unity.h"
#include "../formas/texto.h"

void setUp(void){}
void tearDown(void){}

/*==================================================
  CRIAÇÃO
==================================================*/

void test_criaTexto_deveCriarTextoValido(void){
    TEXTO t = criaTexto(1,10,20,"black","red",'i',"teste");

    TEST_ASSERT_NOT_NULL(t);

    kill_T(t);
}

void test_criaTexto_deveInicializarTodosOsCampos(void){
    TEXTO t = criaTexto(5,15,25,"blue","yellow",'m',"Unity");

    TEST_ASSERT_EQUAL_INT(5,getId_T(t));
    TEST_ASSERT_FLOAT_WITHIN(0.001,15,getX_T(t));
    TEST_ASSERT_FLOAT_WITHIN(0.001,25,getY_T(t));
    TEST_ASSERT_EQUAL_STRING("blue",getCorb_T(t));
    TEST_ASSERT_EQUAL_STRING("yellow",getCorp_T(t));
    TEST_ASSERT_EQUAL_CHAR('m',getA_T(t));
    TEST_ASSERT_EQUAL_STRING("Unity",getTxto_T(t));

    kill_T(t);
}

/*==================================================
  GETTERS
==================================================*/

void test_getId(void){
    TEXTO t = criaTexto(10,0,0,"a","b",'i',"txt");

    TEST_ASSERT_EQUAL_INT(10,getId_T(t));

    kill_T(t);
}

void test_getX(void){
    TEXTO t = criaTexto(1,12.5,0,"a","b",'i',"txt");

    TEST_ASSERT_FLOAT_WITHIN(0.001,12.5,getX_T(t));

    kill_T(t);
}

void test_getY(void){
    TEXTO t = criaTexto(1,0,18.2,"a","b",'i',"txt");

    TEST_ASSERT_FLOAT_WITHIN(0.001,18.2,getY_T(t));

    kill_T(t);
}

void test_getCorB(void){
    TEXTO t = criaTexto(1,0,0,"black","red",'i',"txt");

    TEST_ASSERT_EQUAL_STRING("black",getCorb_T(t));

    kill_T(t);
}

void test_getCorP(void){
    TEXTO t = criaTexto(1,0,0,"black","green",'i',"txt");

    TEST_ASSERT_EQUAL_STRING("green",getCorp_T(t));

    kill_T(t);
}

void test_getAncora(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'f',"txt");

    TEST_ASSERT_EQUAL_CHAR('f',getA_T(t));

    kill_T(t);
}

void test_getTexto(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"Estrutura");

    TEST_ASSERT_EQUAL_STRING("Estrutura",getTxto_T(t));

    kill_T(t);
}

void test_getAltura(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"abc");

    TEST_ASSERT_FLOAT_WITHIN(0.001,10,getAltura_T(t));

    kill_T(t);
}

void test_getComprimento(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"abcd");

    TEST_ASSERT_FLOAT_WITHIN(0.001,40,getComprimento_T(t));

    kill_T(t);
}

void test_getLargura(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"abcd");

    TEST_ASSERT_FLOAT_WITHIN(0.001,4,getLargura_T(t));

    kill_T(t);
}

void test_calcX1(void){
    TEXTO t = criaTexto(1,20,0,"a","b",'i',"abc");

    TEST_ASSERT_FLOAT_WITHIN(0.001,20,calcX1_T(t));

    kill_T(t);
}

void test_calcX2(void){
    TEXTO t = criaTexto(1,20,0,"a","b",'i',"abc");

    TEST_ASSERT_TRUE(calcX2_T(t) >= calcX1_T(t));

    kill_T(t);
}

/*==================================================
  ÁREA
==================================================*/

void test_calcularArea(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"abcd");

    TEST_ASSERT_FLOAT_WITHIN(0.001,40,calcularArea_T(t));

    kill_T(t);
}

void test_calcularArea_textoVazio(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"");

    TEST_ASSERT_FLOAT_WITHIN(0.001,0,calcularArea_T(t));

    kill_T(t);
}

/*==================================================
  SETTERS
==================================================*/

void test_setId(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"txt");

    setId_T(t,99);

    TEST_ASSERT_EQUAL_INT(99,getId_T(t));

    kill_T(t);
}

void test_setX(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"txt");

    setX_T(t,50);

    TEST_ASSERT_FLOAT_WITHIN(0.001,50,getX_T(t));

    kill_T(t);
}

void test_setY(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"txt");

    setY_T(t,60);

    TEST_ASSERT_FLOAT_WITHIN(0.001,60,getY_T(t));

    kill_T(t);
}

void test_setCorB(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"txt");

    setCorb_T(t,"white");

    TEST_ASSERT_EQUAL_STRING("white",getCorb_T(t));

    kill_T(t);
}

void test_setCorP(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"txt");

    setCorp_T(t,"green");

    TEST_ASSERT_EQUAL_STRING("green",getCorp_T(t));

    kill_T(t);
}

void test_setAncora(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"txt");

    setA_T(t,'m');

    TEST_ASSERT_EQUAL_CHAR('m',getA_T(t));

    kill_T(t);
}

void test_setTexto(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"abc");

    setTxto_T(t,"Novo Texto");

    TEST_ASSERT_EQUAL_STRING("Novo Texto",getTxto_T(t));

    kill_T(t);
}

void test_setTexto_deveAlterarComprimento(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"abc");

    setTxto_T(t,"abcdefgh");

    TEST_ASSERT_FLOAT_WITHIN(0.001,80,getComprimento_T(t));

    kill_T(t);
}

/*==================================================
  DESTRUTOR
==================================================*/

void test_killTexto(void){
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"abc");

    kill_T(t);

    TEST_PASS();
}

/*==================================================
  MAIN
==================================================*/

int main(void){

    UNITY_BEGIN();

    RUN_TEST(test_criaTexto_deveCriarTextoValido);
    RUN_TEST(test_criaTexto_deveInicializarTodosOsCampos);

    RUN_TEST(test_getId);
    RUN_TEST(test_getX);
    RUN_TEST(test_getY);
    RUN_TEST(test_getCorB);
    RUN_TEST(test_getCorP);
    RUN_TEST(test_getAncora);
    RUN_TEST(test_getTexto);
    RUN_TEST(test_getAltura);
    RUN_TEST(test_getComprimento);
    RUN_TEST(test_getLargura);
    RUN_TEST(test_calcX1);
    RUN_TEST(test_calcX2);

    RUN_TEST(test_calcularArea);
    RUN_TEST(test_calcularArea_textoVazio);

    RUN_TEST(test_setId);
    RUN_TEST(test_setX);
    RUN_TEST(test_setY);
    RUN_TEST(test_setCorB);
    RUN_TEST(test_setCorP);
    RUN_TEST(test_setAncora);
    RUN_TEST(test_setTexto);
    RUN_TEST(test_setTexto_deveAlterarComprimento);

    RUN_TEST(test_killTexto);

    return UNITY_END();
}