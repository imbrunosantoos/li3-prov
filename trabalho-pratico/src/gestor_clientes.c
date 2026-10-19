#include "gestor_clientes.h"
#include <stdlib.h>
#include <glib.h>

struct gestorClientes {
    GHashTable *clientes;
};

GestorClientes *gestor_clientes_create(void) {
    GestorClientes *gc = malloc(sizeof(GestorClientes));
    if (gc == NULL) return NULL;
    gc -> clientes = g_hash_table_new_full(g_str_hash,g_str_equal, NULL, (GDestroyNotify)cliente_destroy);
    return gc;
}    


void gestor_clientes_destroy (GestorClientes *gc) {
    if (gc == NULL) return;
    g_hash_table_destroy(gc->clientes);
    free(gc);
}

bool gestor_clientes_inserir(GestorClientes *gc, Cliente *c) {
    if (gc == NULL || c == NULL){
        cliente_destroy(c);
        return false;
    }
    const char *id = get_cliente_id(c);
    if (g_hash_table_contains(gc->clientes, id)) {
        cliente_destroy(c);
        return false;
    }    
    g_hash_table_insert (gc->clientes, (gpointer)id, c);
    return true;
}   

const Cliente *gestor_clientes_procurar (const GestorClientes *gc, const char *id) {
    if (gc == NULL || id == NULL) return NULL;
    return g_hash_table_lookup(gc->clientes, id);
}