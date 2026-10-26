#include "gestor_estatisticas.h"

#include <glib.h>
#include <stdlib.h>

typedef struct estatisticaProduto{
    int unidades;
    int64_t receita_cents;
}EstatisticaProduto;

struct gestorEstatisticas{
    GHashTable *por_produto;
};

GestorEstatisticas *gestor_estatisticas_create(void){
    GestorEstatisticas *ge = calloc(1,sizeof(GestorEstatisticas));
    if (ge == NULL)return NULL;

    ge->por_produto = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);

    return ge;
}

void gestor_estatisticas_destroy(GestorEstatisticas *ge){
    if(ge== NULL)return;

    g_hash_table_destroy(ge->por_produto);

    free(ge);   
}

bool gestor_estatisticas_registrar_linha(GestorEstatisticas *ge, const LinhaEncomenda *le, EstadoEncomenda estado){
    if(ge==NULL||le==NULL)return false;

    if (estado == ENCOMENDA_CANCELADA)return true;

    const char *id = linha_encomenda_get_id_produto(le);


    EstatisticaProduto *ep = g_hash_table_lookup(ge->por_produto, id);

    if (ep == NULL){
        ep = calloc(1, sizeof(EstatisticaProduto));
        if (ep == NULL)return false;

        g_hash_table_insert(ge->por_produto, g_strdup(id), ep);
    }
    ep->receita_cents += linha_encomenda_subtotal_cents(le);

    ep->unidades += linha_encomenda_get_quantidade(le);

    return true;
}

int gestor_estatisticas_get_unidades(const GestorEstatisticas *ge, const char *id){
    if(ge == NULL || id == NULL)return 0;
    EstatisticaProduto *ep = g_hash_table_lookup(ge->por_produto, id);
    if (ep==NULL)return 0;
    return ep->unidades;
}

int64_t gestor_estatisticas_get_receita_cents(const GestorEstatisticas *ge, const char *id){
    if (ge == NULL || id == NULL)return 0;
    EstatisticaProduto *ep = g_hash_table_lookup(ge->por_produto, id);
    if(ep == NULL)return 0;
    return ep->receita_cents;
}