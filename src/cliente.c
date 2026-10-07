#include "cliente.h"
#include "validadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_BUFFER 1024

static int separar_campos(char *linha_copia, char **campos, int max_campos) {
    int count = 0;
    char *token = strtok(linha_copia, ",\r\n");
    while (token != NULL && count< max_campos){
        campos [count++] = token;
        token  = strtok (NULL, ",\r\n");
    }
    return count;
}


void processar_clientes (const char *caminho_entrada, const char *caminho_erros) {
    