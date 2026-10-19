#include "gestor_vendedores.h"
#include <stdlib.h>
#include <glib.h>

struct gestorVendedores {
    GHashTable *vendedores;
};

GestorVendedores *gestor_vendedores_create(void) {
    GestorVendedores *gv = malloc(sizeof(GestorVendedores));
    if (gv == NULL) return NULL;
    gv -> vendedores = g_hash_table_new_full(g_str_hash,g_str_equal, NULL, (GDestroyNotify)vendedor_destroy);
    return gv;
}    


void gestor_vendedores_destroy (GestorVendedores *gv) {
    if (gv == NULL) return;
    g_hash_table_destroy(gv->vendedores);
    free(gv);
}

bool gestor_vendedores_inserir(GestorVendedores *gv, Vendedor *v) {
    if (gv == NULL || v == NULL){
        vendedor_destroy(v);
        return false;
    }
    const char *id = get_vendedor_id(v);
    if (g_hash_table_contains(gv->vendedores, id)) {
        vendedor_destroy(v);
        return false;
    }    
    g_hash_table_insert (gv->vendedores, (gpointer)id, v);
    return true;
}   

const Vendedor *gestor_vendedores_procurar (const GestorVendedores *gv, const char *id) {
    if (gv == NULL || id == NULL) return NULL;
    return g_hash_table_lookup(gv->vendedores, id);
}