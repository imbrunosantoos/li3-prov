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

// tamanho máximo de uma linha do CSV
#define TAM_BUFFER 1024

typedef enum { TIPO_CLIENTE, TIPO_VENDEDOR } TipoEntidade;

// clientes e vendedores têm o mesmo ciclo, só mudam a validação e o gestor
// por isso partilham esta função e o tipo diz qual dos dois usar
static int carregar_csv (const char *entrada, const char *erros,TipoEntidade tipo, GestorClientes *gc, GestorVendedores *gv) {
    FILE *f_in = fopen (entrada, "r");
    if (!f_in) {
        perror("ERRO AO ABRIR FICHEIRO DE ENTRADA");
        return -1;
    }
    FILE *f_er = fopen (erros, "w");
    if (!f_er) {
        perror("ERRO AO ABRIR FICHEIRO DE ERROS");
        fclose(f_in); // o de entrada já estava aberto, senão ficava aberto
        return -1;
    }
    // buffer guarda a linha original (vai para os erros tal e qual)
    // linha_copia é a que o separar_campos estraga, ao trocar os ';' por '\0'
    char buffer [TAM_BUFFER];
    char linha_copia [TAM_BUFFER];
    char *campos [10];
     // o cabeçalho vai logo para o ficheiro de erros
    if (fgets(buffer, sizeof(buffer), f_in)!=NULL)
        fputs (buffer, f_er);
    while  (fgets(buffer, sizeof(buffer), f_in)!=NULL) {
        strcpy(linha_copia, buffer);
         // tira o \r\n do fim, senão a data chegava ao validador com 11 caracteres
        linha_copia[strcspn (linha_copia, "\r\n")] = '\0';
        int n = separar_campos(linha_copia, campos, 10, ";");
        // ok só passa a true se a linha for válida e o gestor a aceitar
        bool ok = false;

        if (tipo == TIPO_CLIENTE) {
            if (validar_linha_cliente((const char **)campos, n)) {
                Cliente *c = cliente_novo(campos[0], campos[1], campos[2], campos[3]);
                // o gestor fica dono do cliente (destrói-o se o recusar)
                if (c) ok = gestor_clientes_inserir(gc, c);
            }
        } else {
            if (validar_linha_vendedor((const char **)campos, n)) {
                Vendedor *v = vendedor_novo(campos[0], campos[1], campos[2], campos[3]);
                if (v) ok = gestor_vendedores_inserir(gv, v);
            }
        }
         // linha inválida ou recusada: vai para os erros com o \n original
        if (!ok)
            fputs(buffer, f_er);
       
       
    }
    // o fclose do ficheiro de erros garante que tudo foi escrito em disco
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
// produtos precisa do gestor de vendedores para confirmar que o vendedor existe
int carregar_produtos (const char *entrada, const char *erros, GestorProdutos *gp, GestorVendedores *gv) {
    // abrir os ficheiros e copiar o cabeçalho: igual ao carregar_csv
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
        // 1.º o formato dos campos, o continue passa logo à linha seguinte
        if (!validar_linha_produto((const char **)campos, n)) {
            fputs(buffer, f_er);
            continue;
        }
         // 2.º a cascata: o vendedor tem de existir no gestor
        // um vendedor inválido nunca entrou lá, por isso o produto também falha
        if (gestor_vendedores_procurar(gv,campos[4]) == NULL) {
            fputs(buffer, f_er);
            continue;
        }
        // a linha já foi validada, aqui só se tiram os valores convertidos
        int64_t cents;
        EstadoProduto estado;
        validar_preco(campos [3], &cents);
        validar_estado_produto(campos [5], &estado);
        Produto *p = produto_novo (campos [0], campos [1], campos [2] , cents, campos [4], estado);
        if (!p) {
            fputs(buffer, f_er);
            continue;
        }
         // o gestor destrói o produto se o recusar, por isso não se destrói aqui
        if (!gestor_produtos_inserir(gp, p))
            fputs(buffer, f_er);
    }
    fclose(f_in);
    fclose(f_er);
    return 0;

}

// encomendas precisa do gestor de clientes para confirmar que o cliente existe
int carregar_encomendas (const char *entrada, const char *erros, GestorEncomendas *ge, GestorClientes *gc) {
     // abrir os ficheiros e copiar o cabeçalho: igual ao carregar_csv
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
         // cascata: o id_cliente é o campo 1 (a encomenda só tem 4 campos)
        if (gestor_clientes_procurar(gc,campos[1]) == NULL) {
            fputs(buffer, f_er);
            continue;
        }
        // uma encomenda cancelada é válida, o estado só a exclui das estatísticas
        EstadoEncomenda estado;
        validar_estado_encomenda (campos[3], &estado);
        Encomenda *e = encomenda_nova (campos [0], campos [1], campos [2] , estado);
        if (!e) {
            fputs(buffer, f_er);
            continue;
        }
         // o gestor destrói a encomenda se a recusar
        if (!gestor_encomendas_inserir(ge, e))
            fputs(buffer, f_er);
    }
    fclose(f_in);
    fclose(f_er);
    return 0;

}


// as linhas dependem de três gestores: encomendas e produtos (consulta) e estatísticas (atualiza)
int carregar_linhas (const char *entrada, const char *erros, GestorLinhaEncomenda *gl, GestorEncomendas *ge, GestorProdutos *gp, GestorEstatisticas *gs) {
     // abrir os ficheiros e copiar o cabeçalho: igual ao carregar_csv
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
       // cascata: a encomenda e o produto têm de existir
        // guardam-se os ponteiros porque se precisam de ids e do estado mais abaixo
        const Encomenda *enc = gestor_encomendas_procurar(ge,campos[0]);
        if (enc == NULL) {
            fputs(buffer, f_er);
            continue;
        }
        const Produto *prod = gestor_produtos_procurar(gp,campos[1]);
        if (prod == NULL) {
            fputs(buffer, f_er);
            continue;
        }
       // o par (encomenda, produto) é único, repetido é inválido
        if (gestor_linha_encomenda_existe_par(gl,campos[0],campos[1])) {
            fputs(buffer, f_er);
            continue;
        }
       int quantidade;
       int64_t cents;
       validar_quantidade (campos [2], &quantidade);
       validar_preco(campos[3], &cents);
         // a linha aponta para os ids da encomenda e do produto que já existem
        // em vez de os copiar com strdup, para poupar memória em milhões de linhas
        LinhaEncomenda *l = linha_encomenda_nova (encomenda_get_id(enc), produto_get_id(prod), quantidade, cents);       
         if (!l) {
            fputs(buffer, f_er);
            continue;
        }
        if (!gestor_linha_encomenda_inserir(gl, l))
            fputs(buffer, f_er);
        else
            // só as linhas aceites contam, e o estado da encomenda diz se entram nas estatísticas
            gestor_estatisticas_registrar_linha(gs, l, encomenda_get_estado_encomenda(enc));
    }
    fclose(f_in);
    fclose(f_er);
    return 0;

}
