#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "interpretador.h"
#include "queries.h"

#define MAX_ARGS 6

int interpretar_comandos(const Dados *d, const char *caminho_input)
{
    FILE *fp = fopen(caminho_input, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "erro: nao consegui abrir %s\n", caminho_input);
        return -1;
    }

    char *line = NULL;
    size_t cap = 0;
    ssize_t lidos;

    int N = 0;

    while ((lidos = getline(&line, &cap, fp)) != -1)
    {
        N++;
        line[strcspn(line, "\r\n")] = '\0';

        char *campos[MAX_ARGS];
        int n = separar_campos(line, campos, MAX_ARGS, " ");

        size_t pos = strcspn(campos[0], "S");
        int tem_S = (campos[0][pos] == 'S');
        campos[0][pos] = '\0';
        int numero = atoi(campos[0]);
        char sep = tem_S ? '=' : ';';

        Output *o = output_abrir(N, sep);

        if (o == NULL)
        {
            free(line);
            fclose(fp);
            return -1;
        }

        switch (numero)
        {
        case 1:
            query1(d, o, campos + 1, n - 1);
            break;

        case 2:
            query2(d, o, campos + 1, n - 1);
            break;

        case 3:
            query3(d, o, campos + 1, n - 1);
            break;

        default:
            output_fim_linha(o);
            break;
        }
        output_fechar(o);
    }

    free(line);
    fclose(fp);
    return 0;
}