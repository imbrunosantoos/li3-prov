#include "gestor_linhas_encomenda.h"

#include <stdlib.h>
#include <glib.h>

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