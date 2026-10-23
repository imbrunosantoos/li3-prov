#include "output.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>

struct output
{
    FILE *ficheiro;
    char separador;
    bool primeiro_campo;
};

Output *output_abrir(int n_comando, char sep)
{
    mkdir("resultados", 0755);

    char nome_ficheiro[64];
    snprintf(nome_ficheiro, sizeof(nome_ficheiro), "resultados/command%d_output.txt", n_comando);

    FILE *out = fopen(nome_ficheiro, "w");
    if (out == NULL)
        return NULL;

    Output *o = malloc(sizeof(Output));
    if (o == NULL)
    {
        fclose(out);
        return NULL;
    }

    o->ficheiro = out;
    o->primeiro_campo = true;
    o->separador = sep;

    return o;
}

void output_campo(Output *o, const char *campo)
{
    if (o->primeiro_campo == false)
    {
        fprintf(o->ficheiro, "%c", o->separador);
    }
    fprintf(o->ficheiro, "%s", campo);
    o->primeiro_campo = false;
}

void output_fim_linha(Output *o)
{
    fprintf(o->ficheiro, "\n");
    o->primeiro_campo = true;
}

void output_fechar(Output *o)
{
    if (o == NULL)
        return;

    fclose(o->ficheiro);
    free(o);
}