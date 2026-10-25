#include "comparador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparar_ficheiros(const char *obtido, const char *esperado)
{
    FILE *fo = fopen(obtido, "r");
    if (fo == NULL)
        return -1;

    FILE *fe = fopen(esperado, "r");
    if (fe == NULL)
    {
        fclose(fo);
        return -1;
    }

    char *lineo = NULL;
    size_t capo = 0;
    ssize_t lidoso;

    char *linee = NULL;
    size_t cape = 0;
    ssize_t lidose;

    int resultado;
    int linha = 1;

    while (1)
    {
        lidoso = getline(&lineo, &capo, fo);
        lidose = getline(&linee, &cape, fe);

        if (lidoso == -1 && lidose == -1)
        {
            resultado = 0;
            break;
        }
        if (lidoso == -1 || lidose == -1)
        {
            resultado = linha;
            break;
        }
        if (strcmp(lineo, linee) != 0)
        {
            resultado = linha;
            break;
        }
        linha++;
    }
    free(linee);
    free(lineo);
    fclose(fe);
    fclose(fo);
    return resultado;
}

void avaliar_resultados(const char *caminho_input, const char *pasta_esperados)
{
    FILE *fi = fopen(caminho_input, "r");
    if (fi == NULL)
    {
        fprintf(stderr, "Erro: nao consegui abrir %s\n", caminho_input);
        return;
    }

    int N = 0;
    int numero;
    char *linei = NULL;
    size_t capi = 0;
    ssize_t lidosi;

    while ((lidosi = getline(&linei, &capi, fi)) != -1)
    {

        N++;
        numero = atoi(linei);

        char nome_ficheiro_ob[64];
        snprintf(nome_ficheiro_ob, sizeof(nome_ficheiro_ob), "resultados/command%d_output.txt", N);

        char nome_ficheiro_es[512];
        snprintf(nome_ficheiro_es, sizeof(nome_ficheiro_es), "%s/command%d_output.txt", pasta_esperados, N);

        int resultados = comparar_ficheiros(nome_ficheiro_ob, nome_ficheiro_es);

        printf("comando %d -> Q%d :%d\n", N, numero, resultados);
    }
    free(linei);
    fclose(fi);
}