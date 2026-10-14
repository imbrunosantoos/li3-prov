#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "parser.h"
#include "interpretador.h"
#include "queries.h"

#define MAX_ARGS 6

int interpretar_comandos(const char *caminho_input) {
    mkdir("resultados", 0755);
    FILE *fp = fopen(caminho_input, "r");
    if (fp == NULL) {
        fprintf(stderr, "erro: nao consegui abrir %s\n", caminho_input);
        return -1;
    }

    char *line = NULL;
    size_t cap = 0;
    ssize_t lidos;
    
    int N = 0;

    while ((lidos = getline(&line, &cap, fp)) != -1) {
        N++;
        line[strcspn(line, "\r\n")] = '\0';

        char *campos[MAX_ARGS];
        int n = separar_campos(line, campos, MAX_ARGS, " ");

        size_t pos = strcspn(campos[0], "S");
        int tem_S = (campos[0][pos] == 'S');
        campos[0][pos] = '\0';
        int numero = atoi(campos[0]);
        char sep = tem_S ? '=' : ';';

        char nome_ficheiro[64];
        snprintf(nome_ficheiro, sizeof(nome_ficheiro), "resultados/command%d_output.txt", N);

        FILE *out = fopen(nome_ficheiro, "w");
        if (out == NULL) { free(line); fclose(fp); return -1; }
        
        switch (numero)
        {
        case 1:
            query1(out, campos + 1, n - 1, sep);
            break;

        case 2:
            query2(out, campos + 1, n - 1, sep);
            break;

        case 3:
            query3(out, campos + 1, n - 1, sep);
            break;

        default:
            fprintf(out, "\n");
            break;
        }
        fclose(out);
    }

    free(line);
    fclose(fp);
    return 0;
}