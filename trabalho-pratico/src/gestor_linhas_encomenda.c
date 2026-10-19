#include "gestor_linhas_encomenda.h"

#include <stdlib.h>
#include <glib.h>
#include <string.h>


struct gestorLinhaEncomenda{
    GHashTable *linhas;
};

GestorLinhaEncomenda *gestor_linha_encomenda_create(void){
    GestorLinhaEncomenda *gl = malloc(sizeof(GestorLinhaEncomenda));
    if (gl == NULL)return NULL;

    // g_free- cada etiqueta é uma cópia (g_strdup) feita no inserir, por isso a tabela é dona dela
    // g_ptr_array_unref: cada valor é uma gaveta - destruí-la destrói também as linhas lá dentro
    gl->linhas =  g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)g_ptr_array_unref);
    
    return gl;
}

void gestor_linha_encomenda_destroy(GestorLinhaEncomenda *gl){
    if (gl == NULL) return;

    // a tabela liberta cada etiqueta (g_free)
    // e cada gaveta (g_ptr_array_unref)
    //cada gaveta liberta as suas linhas (linha_encomenda_destroy)
    g_hash_table_destroy(gl->linhas);

    free(gl);
}

bool gestor_linha_encomenda_inserir(GestorLinhaEncomenda *gl, LinhaEncomenda *le){
    if (gl == NULL || le == NULL){
        linha_encomenda_destroy(le);
        return false;
    }

    // a linha é opaca - os ids só se obtem pelos getters
    const char *id_produto = linha_encomenda_get_id_produto(le);

    const char *id_encomenda = linha_encomenda_get_id_encomenda(le);

    //a linha repetida é recusada e o par é unico
    if (gestor_linha_encomenda_existe_par(gl, id_encomenda, id_produto)){
        linha_encomenda_destroy(le);
        return false;
    }

    // procura a gaveta desta encomenda
    GPtrArray *gaveta = g_hash_table_lookup(gl->linhas, id_encomenda);

    if (gaveta == NULL){
        //gaveta nova, que já sabe destruir cada linha quando ela for destruida
        gaveta = g_ptr_array_new_with_free_func((GDestroyNotify)linha_encomenda_destroy);
        // a etiqueta é uma cópia do id-o id original pertence a linha, a cópia pertence à tabela
        g_hash_table_insert(gl->linhas, g_strdup(id_encomenda), gaveta);
    }

    //a linha entra sempre quer a gaveta seja nova quer já existisse
    g_ptr_array_add(gaveta, le);

    return true;
}

bool gestor_linha_encomenda_existe_par(const GestorLinhaEncomenda *gl, const char *id_encomenda, const char *id_produto){
    if (id_produto == NULL) return false;
    // gl e id_encomenda NULL já são tratados pelo num_linhas

    int n = gestor_linha_encomenda_num_linhas(gl, id_encomenda);

     // percorre as linhas da encomenda e procura uma do mesmo produto
    for (int i = 0; i < n; i++){
        const LinhaEncomenda *le = gestor_linha_encomenda_get_linha(gl, id_encomenda, i);
        // strcmp devolve 0 quando as duas strings são iguais
        if (strcmp(linha_encomenda_get_id_produto(le), id_produto) == 0) return true;
    }

    return false;
}

int gestor_linha_encomenda_num_linhas(const GestorLinhaEncomenda *gl, const char *id_encomenda){
    if (gl == NULL || id_encomenda == NULL) return 0;

    GPtrArray *gaveta = g_hash_table_lookup(gl->linhas, id_encomenda);
     //sem gaveta = encomenda sem linhas (na Q3 o total fica 0.00)
    if (gaveta == NULL) return 0;

     //len é o número de elementos do GPtrArray(é um unsigned int)
    return gaveta->len;
}

const LinhaEncomenda *gestor_linha_encomenda_get_linha(const GestorLinhaEncomenda *gl, const char *id_encomenda, int i){
     // posições válidas: de 0 até num_linhas - 1; fora disso devolve NULL
    // se a gaveta não existir, num_linhas dá 0 e qualquer i cai aqui
    if (i < 0 || i >= gestor_linha_encomenda_num_linhas(gl, id_encomenda)) return NULL;

    // aqui a gaveta existe pois passou o if de cima
    GPtrArray *gaveta = g_hash_table_lookup(gl->linhas, id_encomenda);

    // equivalente a gaveta[i] num array normal
    return g_ptr_array_index(gaveta, i);
}
