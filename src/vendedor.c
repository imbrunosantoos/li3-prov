#include "vendedor.h"
#include "validadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_BUFFER 1024

struct vendedor {
    char *id;
    char *nome;
    char *categoria;
    char *data;
};

Vendedor *criar_vendedor(const char *id, const char *nome, const char *categoria, const char *data) {
    Vendedor *v = malloc (sizeof(struct vendedor));
    if (v == NULL) return NULL;
    v -> id = strdup(id);
    v -> nome = strdup (nome);
    v -> categoria = strdup (categoria);
    v -> data = strdup (data);
    return v;
}    

void destruir_vendedor(void *vendedor_ptr) {
    Vendedor *v = (Vendedor *)vendedor_ptr;
    if (v == NULL) return;
    free (v -> id);
    free (v -> nome);
    free ( v -> categoria);
    free (v -> data);
    free (v);
}

const char *get_vendedor_id (const Vendedor *v){
    if (v == NULL) return NULL;
    return v-> id;
}

const char *get_vendedor_nome (const Vendedor *v){
    if (v == NULL) return NULL;
    return v-> nome;
}

const char *get_vendedor_data (const Vendedor *v){
    if (v == NULL) return NULL;
    return v-> data;
}
char *get_vendedor_categoria (const Vendedor *v){
    if (v == NULL) return NULL;
    return v-> categoria;
}









static int  separar_campos (char *linha_copia, char **campos, int max_campos) {
    linha_copia [strcspn(linha_copia, "\r\n")] = '\0';
    int i = 0;
    char *cursor = linha_copia;
    char *campo;
    while ((i < max_campos ) && (campo = strsep(&cursor,";\r\n")) != NULL ) {
        campos [i++] = campo;
    }
    return i;
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
        } else {
             Vendedor *v = vendedor_novo (campos[0], campos [1], campos [2], campos [3]);
        }
    }
    fclose(f_in);
    fclose(f_er);
}