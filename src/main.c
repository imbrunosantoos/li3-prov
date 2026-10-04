#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"
#include "parser.h"
#include <sys/stat.h>

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
        separar_campos(line, campos, MAX_ARGS, " ");

        size_t pos = strcspn(campos[0], "S");
        int tem_S = (campos[0][pos] == 'S');
        campos[0][pos] = '\0';
        int numero = atoi(campos[0]);
        (void)tem_S;
        (void)numero;

        char nome_ficheiro[64];
        snprintf(nome_ficheiro, sizeof(nome_ficheiro), "resultados/command%d_output.txt", N);

        FILE *out = fopen(nome_ficheiro, "w");
        if (out == NULL) { free(line); fclose(fp); return -1; }
        fprintf(out, "\n");
        fclose(out);
    }

    free(line);
    fclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "uso: %s <pasta_dataset> <ficheiro_comandos>\n", argv[0]);
        return 1;
    }

    Deque *d = create();
    destroy(d);

    if (interpretar_comandos(argv[2]) == -1) {
        fprintf(stderr, "erro ao processar comandos\n");
        return 1;
    }   
    
    return 0;
}