#include "carregamento.h"
#include "parser.h"
#include "validadores.h"
#include "cliente.h"
#include "vendedor.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAM_BUFFER 1024

typedef bool (*FnValidar) (const char **campos, int n_campos);
typedef bool (*FnInserir) (void *gestor, const char **campos);

static int carregar_csv (const char *entrada, const char *erros, FnValidar validar , FnInserir inserir, void *gestor) {
    FILE *f_in = fopen (entrada, "r");
    if (!f_in) {
        perror("EROO AO ABRIR FICHEIRO DE ENTRADA");
        return -1;
    }
    FILE *f_er = fopen (erros, "w");
    if (!f_er) {
        perror("EROO AO ABRIR FICHEIRO DE ERROS");
        fclose(f_in);
        return -1;
    }
    char buffer [TAM_BUFFER];
    char linha_copia [TAM_BUFFER];
    char *campos [10];
    if (fgets(buffer, sizeof(buffer), f_in)!=NULL)
        fputs (buffer, f_er);
    while  (fgets(buffer, sizeof(buffer), f_in)!=NULL) {
        strcpy(linha_copia, buffer);
        linha_copia[strcspn (linha_copia, "\r\n")] = '\0';
        int n = separar_campos(linha_copia, campos, 10, ";");
        if (!validar ((const char **)campos, n) || !inserir(gestor, (const char **)campos)) fputs (buffer, f_er);
    }
     fclose (f_in);
     fclose (f_er);
     return 0;
}

static bool inserir_cliente(void *g, const char **c) {
    Cliente *cl =cliente_novo (c[0],c[1],c[2],c[3]);
    if (!cl) return false;
    return gestor_clientes_inserir (g ,cl);
}

static bool inserir_vendedor(void *g, const char **c) {
    Vendedor *v =vendedor_novo (c[0],c[1],c[2],c[3]);
    if (!v) return false;
    return gestor_vendedores_inserir (g,v);
}

int carregar_clientes (const char *entrada, const char *erros, GestorClientes *gc) {
    return carregar_csv(entrada, erros, validar_linha_cliente, inserir_cliente, gc);
}



int carregar_vendedores (const char *entrada, const char *erros, GestorVendedores *gv) {
    return carregar_csv(entrada, erros, validar_linha_vendedor, inserir_vendedor, gv);
}