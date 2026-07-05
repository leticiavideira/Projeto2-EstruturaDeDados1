#ifndef FORMA_H
#define FORMA_H

/*
 * @file forma.h
 * @brief Interface para o módulo de Forma.
 *
 * Este módulo atua como um wrapper genérico para diferentes tipos de formas
 * geométricas (círculo, retângulo, linha, texto, etc.), permitindo que sejam
 * manipuladas de forma uniforme em estruturas como listas e filas.
 *
 * Cada forma encapsula:
 * - Um tipo (FormaTipo)
 * - Um ponteiro genérico para os dados específicos da forma
 *
 * O uso de tipo opaco garante encapsulamento da implementação interna.
 */

/**
 * @brief Enumeração dos tipos de formas suportadas.
 */
typedef enum {
    FORMA_CIRCULO,
    FORMA_RETANGULO,
    FORMA_LINHA,
    FORMA_TEXTO,
    FORMA_ESTILO_TEXTO
} FormaTipo;

/**
 * @brief Tipo abstrato que representa uma forma.
 */
typedef void* FORMA;

/**
 * @brief Cria uma nova forma genérica.
 *
 * @param tipo Tipo da forma
 * @param data Ponteiro para a estrutura específica da forma
 *
 * @return FORMA Ponteiro para a forma criada
 *
 * @note O conteúdo de data deve ser compatível com o tipo informado.
 */
FORMA criarForma(FormaTipo tipo, void *data);

/**
 * @brief Retorna a coordenada x da forma.
 *
 * @param f Forma.
 *
 * @return double Coordenada x da forma.
 * @return double -1 em caso de erro ou tipo incompatível.
 */
double getXForma (FORMA f);

/**
 * @brief Retorna a coordenada y da forma.
 *
 * @param f Forma.
 *
 * @return double Coordenada y da forma.
 * @return double -1 em caso de erro ou tipo incompatível.
 */
double getYForma (FORMA f);

/**
 * @brief Calcula e retorna a área da forma.
 *
 * @param f Forma.
 *
 * @return double Área da forma.
 * @return double -1 em caso de erro ou tipo incompatível.
 */
double getAreaForma (FORMA f);

/**
 * @brief Retorna a largura da forma.
 *
 * @param f Forma.
 *
 * @return double Largura da forma.
 * @return double -1 em caso de erro ou tipo incompatível.
 */
double getLarguraForma (FORMA f);

/**
 * @brief Retorna a altura da forma.
 *
 * @param f Forma.
 *
 * @return double Altura da forma.
 * @return double -1 em caso de erro ou tipo incompatível.
 */
double getAlturaForma (FORMA f);

/**
 * @brief Retorna a cor de preenchimento da forma.
 *
 * @param f Forma.
 *
 * @return char* String contendo a cor de preenchimento.
 * @return NULL em caso de erro ou tipo incompatível.
 */
char* getCorPreenchimentoForma (FORMA f);

/**
 * @brief Retorna a cor da borda da forma.
 *
 * @param f Forma.
 *
 * @return char* String contendo a cor da borda.
 * @return NULL em caso de erro ou tipo incompatível.
 */
char* getCorBordaForma(FORMA f);

/**
 * @brief Retorna o raio de um círculo.
 *
 * @param f Forma.
 *
 * @return double Raio do círculo.
 * @return double -1 caso a forma não seja um círculo ou em caso de erro.
 */
double getRaioForma(FORMA f);

/**
 * @brief Retorna a coordenada x do segundo ponto de uma linha.
 *
 * @param f Forma.
 *
 * @return double Coordenada x do segundo ponto.
 * @return double -1 caso a forma não seja uma linha ou em caso de erro.
 */
double getX2Forma(FORMA f);

/**
 * @brief Retorna a coordenada y do segundo ponto de uma linha.
 *
 * @param f Forma.
 *
 * @return double Coordenada y do segundo ponto.
 * @return double -1 caso a forma não seja uma linha ou em caso de erro.
 */
double getY2Forma(FORMA f);

/**
 * @brief Retorna o tipo de âncora de um texto.
 *
 * @param f Forma.
 *
 * @return char Caractere que representa a âncora do texto.
 * @return '\0' caso a forma não seja um texto ou em caso de erro.
 */
char getAncoraTextoForma(FORMA f);

/**
 * @brief Retorna o conteúdo textual armazenado em uma forma texto.
 *
 * @param f Forma.
 *
 * @return char* String contendo o texto.
 * @return NULL caso a forma não seja um texto ou em caso de erro.
 */
char* getConteudoTextoForma(FORMA f);

/**
 * @brief Retorna o nome textual da forma.
 *
 * @param f Forma
 *
 * @return char* Nome da forma (ex: "circulo", "retangulo")
 * @return NULL em caso de erro
 */
char* getNomeForma (FORMA f);

/**
 * @brief Retorna o identificador da forma.
 *
 * @param f Forma
 *
 * @return int ID da forma
 * @return int -1 em caso de erro
 */
int getIdForma(FORMA f);

/**
 * @brief Obtém o ponto âncora da forma.
 *
 * @param f Forma
 * @param x Saída: coordenada x
 * @param y Saída: coordenada y
 *
 * @note O significado da âncora depende do tipo da forma.
 */
void getAncoraForma(FORMA f, double *x, double *y);

/**
 * @brief Retorna o tipo da forma (com base no enum).
 *
 * @param f Forma
 *
 * @return FormaTipo Tipo da forma
 */
FormaTipo getTipoForma(FORMA f);

/**
 * @brief Retorna o ponteiro para os dados internos da forma.
 *
 * @param f Forma
 *
 * @return void* Ponteiro para a estrutura específica da forma
 *
 * @warning O uso deste ponteiro deve respeitar o tipo da forma.
 */
void* getDataForma(FORMA f);

/**
 * @brief Define o identificador da forma.
 *
 * @param f Forma.
 * @param id Novo identificador.
 *
 * @note O identificador é atualizado de acordo com o tipo específico da forma.
 */
void setIdForma(FORMA f, int id);

/**
 * @brief Define a cor da borda da forma.
 *
 * @param f Forma
 * @param cor String representando a cor
 */
void setCorBordaForma(FORMA f, char *cor);

/**
 * @brief Define a cor de preenchimento da forma.
 *
 * @param f Forma
 * @param cor String representando a cor
 */
void setCorPreenchimentoForma(FORMA f, char *cor);

/**
 * @brief Move a forma no plano cartesiano.
 *
 * @param f Forma
 * @param dx Deslocamento em x
 * @param dy Deslocamento em y
 */
void moverForma(FORMA f, double dx, double dy);

/**
 * @brief Imprime os dados da forma em formato texto (em um arquivo .txt).
 *
 * @param txt Arquivo de saída
 * @param f Forma
 *
 * @note O formato de saída depende do tipo da forma.
 */
void printFormaTXT(FILE *txt, FORMA f);

/**
 * @brief Libera a memória associada à forma.
 *
 * @param f Forma
 */
void killForma(FORMA f);

#endif