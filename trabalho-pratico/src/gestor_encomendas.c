#include "gestor_encomendas.h"

#include <stdlib.h>
#include <glib.h>

struct gestorEncomendas{
    GHashTable *encomendas;
};

GestorEncomendas *gestor_encomendas_create(void){
    GestorEncomendas *ge = malloc(sizeof(GestorEncomendas));
    if (ge == NULL) return NULL;

    // a tabela chama encomenda_destroy em cada encomenda ao ser destruída
    // o cast GDestroyNotify é preciso porque a glib espera uma função que recebe void *
    ge->encomendas = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)encomenda_destroy);

    return ge;
}

void gestor_encomendas_destroy(GestorEncomendas *ge){
    if (ge == NULL)return;

    // primeiro a tabela que liberta todas as encomendas, só depois a struct
    // porque o ponteiro para a tabela está guardado dentro dela
    g_hash_table_destroy(ge->encomendas);

    free(ge);
}

bool gestor_encomendas_inserir(GestorEncomendas *ge, Encomenda *e){
    // o gestor fica sempre dono da encomenda-se a recusa, é ele que a destrói
    if(ge == NULL || e == NULL) {
        encomenda_destroy(e);
        return false;
    }

    // a encomenda é opaca-o id só se obtém pelo getter
    const char *id1 = encomenda_get_id(e);

    // id repetido-recusa e mantém a que já lá estava
    if(g_hash_table_contains(ge->encomendas, id1)){
        encomenda_destroy(e);
        return false;
    } 

    //gpointer = void * o cast tira o const
    //é seguro porque a tabela nunca altera a chave
    g_hash_table_insert(ge->encomendas, (gpointer)id1, e);

    return true;
}

const Encomenda *gestor_encomendas_procurar(const GestorEncomendas *ge, const char *id){
    if (ge == NULL || id == NULL){
        return NULL;
    }

    //o lookup já devolve NULL se o id não existir
    return g_hash_table_lookup(ge->encomendas, id);
}