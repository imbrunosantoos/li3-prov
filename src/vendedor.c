#include "vendedor.h"
#include "validadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_BUFFER 1024

static int  separar_campos (char *linha_copia, char **campos, int max_campos) {
    int count = 0;
    char *token = strtok (linha_copia, ";\r\n");
    while (token != NULL && count < max_campos) {
        campos[count++] = token;
        token = strtok(NULL, ";\r\n");
    }
    return count;
}

void processar_vendedores ( const char *caminho_entrada, const char *caminho_erros) {
    FILE *f_in = fopen (caminho_entrada, "r" );
    if (!f_in) {
        perror("ERRO AO ABRIR FICHEIRO DE VENDEDORES " );
        return;
    }
    FILE *f_er = fopen(caminho_erros, "w");
    if (!f_er) {
        perror("ERRO AO ABRIR FICHEIRO DE ERRO DE VENDEDORES");
        fclose(f_in);
        return; 
    }    
    
    char buffer [TAM_BUFFER];
    char linha_copia [TAM_BUFFER];
        if (fgets(buffer, sizeof(buffer), f_in) != NULL) {
            fputs(buffer, f_er);
        }
        char *campos[10];

        while (fgets(buffer, sizeof(buffer), f_in) != NULL) {
        strcpy(linha_copia, buffer);

        int n_campos = separar_campos(linha_copia, campos, 10);

        if (!validar_linha_vendedor((const char **)campos, n_campos)) {
            fputs(buffer, f_er);
        }
    }

    fclose(f_in);
    fclose(f_er);
}