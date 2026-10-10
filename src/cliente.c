#include "cliente.h"
#include "validadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_BUFFER 1024


struct cliente {
    char *id;
    char *nome;
    char *regiao;
    char *data;
};

Cliente *criar_cliente (const char *id, const char *nome, const char *data, const char *regiao){
    Cliente *c = malloc (sizeof(struct cliente));
    if (c == NULL) return NULL;
    c -> id = strdup(id);
    c -> nome = strdup (nome);
    c -> regiao = strdup (regiao);
    c -> data = strdup (data);
    return c;
}

void destruir_cliente(void *cliente_ptr) {
    Cliente *c = (Cliente *) cliente_ptr;
    if (c == NULL) return;
    free (c -> id);
    free (c -> nome);
    free ( c -> regiao);
    free (c -> data);
    free (c);
}


const char *get_cliente_id (const Cliente *c){
    if (c == NULL) return NULL;
    return c-> id;
}

const char *get_cliente_nome (const Cliente *c){
    if (c == NULL) return NULL;
    return c-> nome;
}

const char *get_cliente_data (const Cliente *c){
    if (c == NULL) return NULL;
    return c-> data;
}
char *get_cliente_regiao (const Cliente *c){
    if (c == NULL) return NULL;
    return c-> regiao;
}

static int separar_campos(char *linha_copia, char **campos, int max_campos) {
    int count = 0;
    char *token = strtok(linha_copia, ";\r\n");
    while (token != NULL && count< max_campos){
        campos [count++] = token;
        token  = strtok (NULL, ";\r\n");
    }
    return count;
}


void processar_clientes (const char *caminho_entrada, const char *caminho_erros) {
    FILE *f_in = fopen(caminho_entrada, "r");
        if (!f_in) {
            perror ("ERRO AO ABRIR FICHEIRO CLIENTES");
            return;
        }
    FILE *f_er = fopen (caminho_erros, "w");
        if (!f_er) {
            perror ("ERRO AO ABRIR FICHEIRO DE ERROS DE CLIENTES");
            fclose (f_in);
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

        if (!validar_linha_cliente((const char **)campos, n_campos)) {
            fputs(buffer, f_er);
        } else {
            Cliente *c = cliente_novo (campos[0], campos [1], campos [2], campos [3]);
        }
    }
    fclose(f_in);
    fclose(f_er);
}