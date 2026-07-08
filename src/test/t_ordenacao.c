#include "unity.h"

#include "../gerais/ordenacao.h"
#include "../gerais/comparadores.h"
#include "../formas/circulo.h"
#include "../formas/forma.h"

void setUp(void){}
void tearDown(void){}

/*==================================================
 AUXILIARES
==================================================*/

FORMA criaFormaTeste(int id,double area){

    double r = sqrt(area/3.141592653589793);

    return criarForma(
        FORMA_CIRCULO,
        criaCirculo(id,0,0,r,"black","red")
    );
}

void verificaOrdenado(FORMA vet[],int n){

    for(int i=0;i<n-1;i++){

        TEST_ASSERT_LESS_OR_EQUAL(
            0,
            comparaArea(vet[i],vet[i+1])
        );
    }
}

/*==================================================
 SELECTION SORT
==================================================*/

void test_selectionSort(){

    FORMA vet[5];

    vet[0]=criaFormaTeste(5,25);
    vet[1]=criaFormaTeste(2,4);
    vet[2]=criaFormaTeste(8,49);
    vet[3]=criaFormaTeste(1,1);
    vet[4]=criaFormaTeste(3,9);

    ordenar(vet,5,SS,comparaArea,NULL,NULL);

    verificaOrdenado(vet,5);

    for(int i=0;i<5;i++)
        killForma(vet[i]);
}

/*==================================================
 BUBBLE SORT
==================================================*/

void test_bubbleSort(){

    FORMA vet[4];

    vet[0]=criaFormaTeste(5,36);
    vet[1]=criaFormaTeste(2,4);
    vet[2]=criaFormaTeste(8,16);
    vet[3]=criaFormaTeste(1,1);

    ordenar(vet,4,BS,comparaArea,NULL,NULL);

    verificaOrdenado(vet,4);

    for(int i=0;i<4;i++)
        killForma(vet[i]);
}

/*==================================================
 INSERTION
==================================================*/

void test_insertionSort(){

    FORMA vet[5];

    vet[0]=criaFormaTeste(10,64);
    vet[1]=criaFormaTeste(11,1);
    vet[2]=criaFormaTeste(12,25);
    vet[3]=criaFormaTeste(13,9);
    vet[4]=criaFormaTeste(14,16);

    ordenar(vet,5,IS,comparaArea,NULL,NULL);

    verificaOrdenado(vet,5);

    for(int i=0;i<5;i++)
        killForma(vet[i]);
}

/*==================================================
 SHELL
==================================================*/

void test_shellSort(){

    FORMA vet[5];

    vet[0]=criaFormaTeste(1,81);
    vet[1]=criaFormaTeste(2,9);
    vet[2]=criaFormaTeste(3,36);
    vet[3]=criaFormaTeste(4,4);
    vet[4]=criaFormaTeste(5,25);

    ordenar(vet,5,SHS,comparaArea,NULL,NULL);

    verificaOrdenado(vet,5);

    for(int i=0;i<5;i++)
        killForma(vet[i]);
}

/*==================================================
 QUICK
==================================================*/

void test_quickSort(){

    FORMA vet[6];

    vet[0]=criaFormaTeste(1,49);
    vet[1]=criaFormaTeste(2,1);
    vet[2]=criaFormaTeste(3,64);
    vet[3]=criaFormaTeste(4,16);
    vet[4]=criaFormaTeste(5,4);
    vet[5]=criaFormaTeste(6,25);

    ordenar(vet,6,QS,comparaArea,NULL,NULL);

    verificaOrdenado(vet,6);

    for(int i=0;i<6;i++)
        killForma(vet[i]);
}

/*==================================================
 MERGE
==================================================*/

void test_mergeSort(){

    FORMA vet[5];

    vet[0]=criaFormaTeste(1,49);
    vet[1]=criaFormaTeste(2,9);
    vet[2]=criaFormaTeste(3,1);
    vet[3]=criaFormaTeste(4,36);
    vet[4]=criaFormaTeste(5,16);

    ordenar(vet,5,MS,comparaArea,NULL,NULL);

    verificaOrdenado(vet,5);

    for(int i=0;i<5;i++)
        killForma(vet[i]);
}

/*==================================================
 CASOS ESPECIAIS
==================================================*/

void test_vetorJaOrdenado(){

    FORMA vet[3];

    vet[0]=criaFormaTeste(1,1);
    vet[1]=criaFormaTeste(2,4);
    vet[2]=criaFormaTeste(3,9);

    ordenar(vet,3,QS,comparaArea,NULL,NULL);

    verificaOrdenado(vet,3);

    for(int i=0;i<3;i++)
        killForma(vet[i]);
}

void test_umElemento(){

    FORMA vet[1];

    vet[0]=criaFormaTeste(1,25);

    ordenar(vet,1,MS,comparaArea,NULL,NULL);

    TEST_ASSERT_EQUAL(1,getIdForma(vet[0]));

    killForma(vet[0]);
}

void test_vetorVazio(){

    ordenar(NULL,0,QS,comparaArea,NULL,NULL);

    TEST_PASS();
}

void test_comparadorNULL(){

    FORMA vet[1];

    vet[0]=criaFormaTeste(1,25);

    ordenar(vet,1,QS,NULL,NULL,NULL);

    killForma(vet[0]);

    TEST_PASS();
}

void test_algoritmoInvalido(){

    FORMA vet[2];

    vet[0]=criaFormaTeste(1,9);
    vet[1]=criaFormaTeste(2,1);

    ordenar(vet,2,(ALGORITMO)50,comparaArea,NULL,NULL);

    killForma(vet[0]);
    killForma(vet[1]);

    TEST_PASS();
}

/*==================================================
 MAIN
==================================================*/

int main(){

    UNITY_BEGIN();

    RUN_TEST(test_selectionSort);
    RUN_TEST(test_bubbleSort);
    RUN_TEST(test_insertionSort);
    RUN_TEST(test_shellSort);
    RUN_TEST(test_quickSort);
    RUN_TEST(test_mergeSort);

    RUN_TEST(test_vetorJaOrdenado);
    RUN_TEST(test_umElemento);

    RUN_TEST(test_vetorVazio);
    RUN_TEST(test_comparadorNULL);
    RUN_TEST(test_algoritmoInvalido);

    return UNITY_END();
}