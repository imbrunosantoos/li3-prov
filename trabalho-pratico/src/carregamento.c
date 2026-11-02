#include "carregamento.h"
#include "parser.h"
#include "validadores.h"
#include "cliente.h"
#include "vendedor.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "produto.h"
#include "gestor_produtos.h"
#include "encomenda.h"
#include "gestor_encomendas.h"
#include "gestor_linhas_encomenda.h"
#define TAM_BUFFER 1024

typedef enum { TIPO_CLIENTE, TIPO_VENDEDOR } TipoEntidade;


static int carregar_csv (const char *entrada, const char *erros,TipoEntidade tipo, GestorClientes *gc, GestorVendedores *gv) {
    FILE *f_in = fopen (entrada, "r");
    if (!f_in) {
        perror("ERRO AO ABRIR FICHEIRO DE ENTRADA");
        return -1;
    }
    FILE *f_er = fopen (erros, "w");
    if (!f_er) {
        perror("ERRO AO ABRIR FICHEIRO DE ERROS");
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
        
        bool ok = false;

        if (tipo == TIPO_CLIENTE) {
            if (validar_linha_cliente((const char **)campos, n)) {
                Cliente *c = cliente_novo(campos[0], campos[1], campos[2], campos[3]);
                if (c) ok = gestor_clientes_inserir(gc, c);
            }
        } else {
            if (validar_linha_vendedor((const char **)campos, n)) {
                Vendedor *v = vendedor_novo(campos[0], campos[1], campos[2], campos[3]);
                if (v) ok = gestor_vendedores_inserir(gv, v);
            }
        }

        if (!ok)
            fputs(buffer, f_er);
       
       
    }
     fclose (f_in);
     fclose (f_er);
     return 0;
}



int carregar_clientes (const char *entrada, const char *erros, GestorClientes *gc) {
    return carregar_csv(entrada, erros, TIPO_CLIENTE, gc, NULL);
}



int carregar_vendedores (const char *entrada, const char *erros, GestorVendedores *gv) {
    return carregar_csv(entrada, erros, TIPO_VENDEDOR , NULL, gv);
}

int carregar_produtos (const char *entrada, const char *erros, GestorProdutos *gp, GestorVendedores *gv) {
     FILE *f_in = fopen (entrada, "r");
    if (!f_in) {
        perror("ERRO AO ABRIR FICHEIRO DE PRODUTOS");
        return -1;
    }
    FILE *f_er = fopen (erros, "w");
    if (!f_er) {
        perror("ERRO AO ABRIR FICHEIRO DE ERROS DE PRODUTOS");
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
        if (!validar_linha_produto((const char **)campos, n)) {
            fputs(buffer, f_er);
            continue;
        }
        if (gestor_vendedores_procurar(gv,campos[4]) == NULL) {
            fputs(buffer, f_er);
            continue;
        }
        int64_t cents;
        EstadoProduto estado;
        validar_preco(campos [3], &cents);
        validar_estado_produto(campos [5], &estado);
        Produto *p = produto_novo (campos [0], campos [1], campos [2] , cents, campos [4], estado);
        if (!p) {
            fputs(buffer, f_er);
            continue;
        }
        if (!gestor_produtos_inserir(gp, p))
            fputs(buffer, f_er);
    }
    fclose(f_in);
    fclose(f_er);
    return 0;

}


int carregar_encomendas (const char *entrada, const char *erros, GestorEncomendas *ge, GestorClientes *gc) {
     FILE *f_in = fopen (entrada, "r");
    if (!f_in) {
        perror("ERRO AO ABRIR FICHEIRO DE ENCOMENDAS");
        return -1;
    }
    FILE *f_er = fopen (erros, "w");
    if (!f_er) {
        perror("ERRO AO ABRIR FICHEIRO DE ERROS DE ENCOMENDAS");
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
        if (!validar_linha_encomenda((const char **)campos, n)) {
            fputs(buffer, f_er);
            continue;
        }
        if (gestor_clientes_procurar(gc,campos[1]) == NULL) {
            fputs(buffer, f_er);
            continue;
        }
        EstadoEncomenda estado;
        validar_estado_encomenda (campos[3], &estado);
        Encomenda *e = encomenda_nova (campos [0], campos [1], campos [2] , estado);
        if (!e) {
            fputs(buffer, f_er);
            continue;
        }
        if (!gestor_encomendas_inserir(ge, e))
            fputs(buffer, f_er);
    }
    fclose(f_in);
    fclose(f_er);
    return 0;

}



int carregar_linhas (const char *entrada, const char *erros, GestorLinhaEncomenda *gl, GestorEncomendas *ge, GestorProdutos *gp) {
     FILE *f_in = fopen (entrada, "r");
    if (!f_in) {
        perror("ERRO AO ABRIR FICHEIRO DE LINHAS");
        return -1;
    }
    FILE *f_er = fopen (erros, "w");
    if (!f_er) {
        perror("ERRO AO ABRIR FICHEIRO DE ERROS DE LINHAS");
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
        if (!validar_linha_linhas_encomenda((const char **)campos, n)) {
            fputs(buffer, f_er);
            continue;
        }
        if (gestor_encomendas_procurar(ge,campos[0]) == NULL) {
            fputs(buffer, f_er);
            continue;
        }
        if (gestor_produtos_procurar(gp,campos[1]) == NULL) {
            fputs(buffer, f_er);
            continue;
        }
        if (gestor_linha_encomenda_existe_par(gl,campos[0],campos[1])) {
            fputs(buffer, f_er);
            continue;
        }
       int quantidade;
       int64_t cents;
       validar_quantidade (campos [2], &quantidade);
       validar_preco(campos[3], &cents);
        LinhaEncomenda *l = linha_encomenda_nova (campos [0], campos [1], quantidade, cents);
        if (!l) {
            fputs(buffer, f_er);
            continue;
        }
        if (!gestor_linha_encomenda_inserir(gl, l))
            fputs(buffer, f_er);
    }
    fclose(f_in);
    fclose(f_er);
    return 0;

}
