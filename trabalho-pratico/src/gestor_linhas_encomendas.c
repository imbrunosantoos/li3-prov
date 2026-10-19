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

    gl->linhas =  g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)g_ptr_array_unref);
    
    return gl;
}

void gestor_linha_encomenda_destroy(GestorLinhaEncomenda *gl){
    if (gl == NULL) return;

    g_hash_table_destroy(gl->linhas);

    free(gl);
}

bool gestor_linha_encomenda_inserir(GestorLinhaEncomenda *gl, LinhaEncomenda *le){
    if (gl == NULL || le == NULL){
        linha_encomenda_destroy(le);
        return false;
    }

    const char *id_produto = linha_encomenda_get_id_produto(le);
    
    const char *id_encomenda = linha_encomenda_get_id_encomenda(le);

    if (gestor_linha_encomenda_existe_par(gl, id_encomenda, id_produto)){
        linha_encomenda_destroy(le);
        return false;
    }

    GPtrArray *gaveta = g_hash_table_lookup(gl->linhas, id_encomenda);

    if (gaveta == NULL){
        gaveta = g_ptr_array_new_with_free_func((GDestroyNotify)linha_encomenda_destroy);
        g_hash_table_insert(gl->linhas, g_strdup(id_encomenda), gaveta);
    }

    g_ptr_array_add(gaveta, le);

    return true;
}

bool gestor_linha_encomenda_existe_par(const GestorLinhaEncomenda *gl, const char *id_encomenda, const char *id_produto){
    if (id_produto == NULL) return false;

    int n = gestor_linha_encomenda_num_linhas(gl, id_encomenda);

    for (int i = 0; i < n; i++){
        const LinhaEncomenda *le = gestor_linha_encomenda_get_linha(gl, id_encomenda, i);
        if (strcmp(linha_encomenda_get_id_produto(le), id_produto) == 0) return true;
    }

    return false;
}

int gestor_linha_encomenda_num_linhas(const GestorLinhaEncomenda *gl, const char *id_encomenda){
    if (gl == NULL || id_encomenda == NULL) return 0;

    GPtrArray *gaveta = g_hash_table_lookup(gl->linhas, id_encomenda);
    if (gaveta == NULL) return 0;

    return gaveta->len;
}

const LinhaEncomenda *gestor_linha_encomenda_get_linha(const GestorLinhaEncomenda *gl, const char *id_encomenda, int i){
    if (i < 0 || i >= gestor_linha_encomenda_num_linhas(gl, id_encomenda)) return NULL;

    GPtrArray *gaveta = g_hash_table_lookup(gl->linhas, id_encomenda);

    return g_ptr_array_index(gaveta, i);
}
