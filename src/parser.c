#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_CAMPOS 6

int separar_campos(char *linha, char **campos, int max, const char *delim){
        int i = 0;
    char *cursor = linha;
    char *campo;
    while ((i < max) && (campo = strsep(&cursor, delim)) != NULL) {
        campos[i] = campo;
        i++;
    }
    return i;
}


int ler_csv(const char *caminho) {
    FILE *fp = fopen(caminho, "r");
    if (fp == NULL) return -1;

    char *line = NULL;
    size_t cap = 0;

    ssize_t lidos = getline(&line, &cap, fp);

    if (lidos == -1){
        free(line);
        fclose(fp);
        return -1;
    }

    while((lidos = getline (&line, &cap, fp)) != -1)
    {
        line[strcspn(line, "\r\n")] = '\0';

        char *campos[MAX_CAMPOS];
        int n = separar_campos(line, campos,MAX_CAMPOS,";");

        for (int i = 0; i < n; i++) printf("%s\n", campos[i]);  
    }

    free(line);
    fclose(fp);
    return 0;
}