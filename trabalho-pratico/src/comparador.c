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