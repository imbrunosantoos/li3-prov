#include "gestor_vendedores.h"
#include <stdlib.h>
#include <glib.h>

// a tabela de hash tem o id como chave e o vendedor como valor
struct gestorVendedores {
    GHashTable *vendedores;
};

GestorVendedores *gestor_vendedores_create(void) {
    GestorVendedores *gv = malloc(sizeof(GestorVendedores));
    if (gv == NULL) return NULL;
    // g_str_hash e g_str_equal comparam as chaves pelo texto e não pelo endereço
    // a chave é NULL porque é o id do próprio vendedor, que o vendedor_destroy já liberta
    // o cast GDestroyNotify é preciso porque a glib espera uma função que recebe void *
    gv -> vendedores = g_hash_table_new_full(g_str_hash,g_str_equal, NULL, (GDestroyNotify)vendedor_destroy);
    return gv;
}    


void gestor_vendedores_destroy (GestorVendedores *gv) {
    if (gv == NULL) return;
    // primeiro a tabela, que liberta todos os vendedores, só depois a struct
    // porque o ponteiro para a tabela está guardado dentro dela
    g_hash_table_destroy(gv->vendedores);
    free(gv);
}

bool gestor_vendedores_inserir(GestorVendedores *gv, Vendedor *v) {
   // o gestor fica sempre dono do vendedor, se o recusa é ele que o destrói
    if (gv == NULL || v == NULL){
        vendedor_destroy(v);
        return false;
    }
   // o vendedor é opaco, o id só se obtém pelo getter
    const char *id = get_vendedor_id(v);
     // id repetido: recusa e mantém o que já lá estava
    if (g_hash_table_contains(gv->vendedores, id)) {
        vendedor_destroy(v);
        return false;
    }    
    // gpointer = void *, o cast tira o const
    // é seguro porque a tabela nunca altera a chave
    g_hash_table_insert (gv->vendedores, (gpointer)id, v);
    return true;
}   

const Vendedor *gestor_vendedores_procurar (const GestorVendedores *gv, const char *id) {
    if (gv == NULL || id == NULL) return NULL;
     // o lookup já devolve NULL se o id não existir
    return g_hash_table_lookup(gv->vendedores, id);
}