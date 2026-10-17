#include "gestor_encomendas.h"

#include <stdlib.h>
#include <glib.h>

struct gestorEncomendas{
    GHashTable *encomendas;
};

GestorEncomendas *gestor_encomendas_create(void){
    GestorEncomendas *ge = malloc(sizeof(GestorEncomendas));
    if (ge == NULL) return NULL;

    ge->encomendas = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)encomenda_destroy);

    return ge;
}

void gestor_encomendas_destroy(GestorEncomendas *ge){
    if (ge == NULL)return;

    g_hash_table_destroy(ge->encomendas);

    free(ge);
}

bool gestor_encomendas_inserir(GestorEncomendas *ge, Encomenda *e){
    if(ge == NULL || e == NULL) {
        encomenda_destroy(e);
        return false;
    }

    const char *id1 = encomenda_get_id(e);

    if(g_hash_table_contains(ge->encomendas, id1)){
        encomenda_destroy(e);
        return false;
    } 

    g_hash_table_insert(ge->encomendas, (gpointer)id1, e);

    return true;
}

const Encomenda *gestor_encomendas_procurar(const GestorEncomendas *ge, const char *id){
    if (ge == NULL || id == NULL){
        return NULL;
    }

    return g_hash_table_lookup(ge->encomendas, id);
}