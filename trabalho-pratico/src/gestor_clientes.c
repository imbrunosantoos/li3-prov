#include "gestor_clientes.h"
#include <stdlib.h>
#include <glib.h>

// a tabela de hash tem o id como chave e o cliente como valor
struct gestorClientes {
    GHashTable *clientes;
};

GestorClientes *gestor_clientes_create(void) {
    GestorClientes *gc = malloc(sizeof(GestorClientes));
    if (gc == NULL) return NULL;
    // g_str_hash e g_str_equal comparam as chaves pelo texto e não pelo endereço
    // a chave é NULL porque é o id do próprio cliente, que o cliente_destroy já liberta
    // o cast GDestroyNotify é preciso porque a glib espera uma função que recebe void *
    gc -> clientes = g_hash_table_new_full(g_str_hash,g_str_equal, NULL, (GDestroyNotify)cliente_destroy);
    return gc;
}    


void gestor_clientes_destroy (GestorClientes *gc) {
    if (gc == NULL) return;
    // primeiro a tabela, que liberta todos os clientes, só depois a struct
    // porque o ponteiro para a tabela está guardado dentro dela
    g_hash_table_destroy(gc->clientes);
    free(gc);
}

bool gestor_clientes_inserir(GestorClientes *gc, Cliente *c) {
   // o gestor fica sempre dono do cliente, se o recusa é ele que o destrói
    if (gc == NULL || c == NULL){
        cliente_destroy(c);
        return false;
    }
    // o cliente é opaco, o id só se obtém pelo getter
    const char *id = get_cliente_id(c);
    // id repetido: recusa e mantém o que já lá estava
    if (g_hash_table_contains(gc->clientes, id)) {
        cliente_destroy(c);
        return false;
    }    
   // gpointer = void *, o cast tira o const
    // é seguro porque a tabela nunca altera a chave
    g_hash_table_insert (gc->clientes, (gpointer)id, c);
    return true;
}   

const Cliente *gestor_clientes_procurar (const GestorClientes *gc, const char *id) {
    if (gc == NULL || id == NULL) return NULL;
    // o lookup já devolve NULL se o id não existir
    return g_hash_table_lookup(gc->clientes, id);
}