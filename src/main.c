#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerais/leitorDeArquivos.h"
#include "gerais/leitorGeo.h"
#include "gerais/leitorQry.h"
#include "gerais/svg.h"

#define TAM_PATH 1024

int main(int argc, char *argv[]) {

    char *dirEntrada = NULL;
    char *dirSaida   = NULL;
    char *geoNome    = NULL;
    char *qryNome    = NULL;

    //Leitura dos parâmetros
    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            dirEntrada = argv[++i];
        }

        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            geoNome = argv[++i];
        }

        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            qryNome = argv[++i];
        }

        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            dirSaida = argv[++i];
        }
    }

    //Validação
    if (geoNome == NULL || dirSaida == NULL) {

        fprintf(stderr,
                "Uso:\n"
                "./ted [-e dirEntrada] -f arquivo.geo "
                "[-q arquivo.qry] -o dirSaida\n");

        return EXIT_FAILURE;
    }

    if (dirEntrada == NULL)
        dirEntrada = ".";

    //Monta caminho do GEO
    char caminhoGeo[TAM_PATH];

    if (geoNome[0] == '/' || geoNome[0] == '.') {

        snprintf(caminhoGeo,
                 sizeof(caminhoGeo),
                 "%s",
                 geoNome);

    } else {

        snprintf(caminhoGeo,
                 sizeof(caminhoGeo),
                 "%s/%s",
                 dirEntrada,
                 geoNome);
    }

    //Leitura do GEO
    DadosArquivo geo = criarDadosArq(caminhoGeo);

    if (geo == NULL) {

        fprintf(stderr,
                "Erro ao abrir arquivo GEO: %s\n",
                caminhoGeo);

        return EXIT_FAILURE;
    }

    //Processa GEO
    SISTEMA sistema = processarGeo(geo);

    if (sistema == NULL) {

        fprintf(stderr,
                "Erro ao processar arquivo GEO.\n");

        destruirDadosArq(geo);

        return EXIT_FAILURE;
    }

    ARVORE banco = getArvoreFormas(sistema);

    //Caso exista QRY, abre o arquivo
    DadosArquivo qry = NULL;

    if (qryNome != NULL) {

        char caminhoQry[TAM_PATH];

        if (qryNome[0] == '/' || qryNome[0] == '.') {

            snprintf(caminhoQry,
                     sizeof(caminhoQry),
                     "%s",
                     qryNome);

        } else {

            snprintf(caminhoQry,
                     sizeof(caminhoQry),
                     "%s/%s",
                     dirEntrada,
                     qryNome);
        }

        qry = criarDadosArq(caminhoQry);

        if (qry == NULL) {

            fprintf(stderr,
                    "Erro ao abrir arquivo QRY: %s\n",
                    caminhoQry);

            killSistemaGeo(sistema);
            destruirDadosArq(geo);

            return EXIT_FAILURE;
        }
    }

    //Cria módulo SVG
    SVG svg = criarSVG(dirSaida, geo, qry);

    if (svg == NULL) {

        fprintf(stderr,
                "Erro ao criar módulo SVG.\n");

        if (qry != NULL)
            destruirDadosArq(qry);

        destruirDadosArq(geo);
        killSistemaGeo(sistema);

        return EXIT_FAILURE;
    }

    gerarSVGInicial(svg, banco);

    //Executa arquivo QRY (caso exista)
    LEITOR_QRY leitor = NULL;

    if (qry != NULL) {

        leitor = criarLeitorQry(
                    dirSaida,
                    geo,
                    qry,
                    banco,
                    svg);

        if (leitor == NULL) {

            fprintf(stderr,
                    "Erro ao criar leitor do QRY.\n");

            destruirSVG(svg);
            destruirDadosArq(qry);
            destruirDadosArq(geo);
            killSistemaGeo(sistema);

            return EXIT_FAILURE;
        }

        executarQry(leitor);

        gerarSVGFinal(svg, banco);

        destruirLeitorQry(leitor);
    }

    
    //Finalização
    destruirSVG(svg);

    if (qry != NULL)
        destruirDadosArq(qry);

    destruirDadosArq(geo);

    killSistemaGeo(sistema);

    printf("Execução finalizada com sucesso.\n");

    return EXIT_SUCCESS;
}