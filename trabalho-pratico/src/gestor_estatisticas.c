#include "gestor_estatisticas.h"

#include <glib.h>
#include <stdlib.h>

// estatísticas de um produto - privada, ninguém fora deste .c sabe que existe
typedef struct estatisticaProduto{
    int unidades;
    int64_t receita_cents;
}EstatisticaProduto;

struct gestorEstatisticas{
    GHashTable *por_produto;
};

GestorEstatisticas *gestor_estatisticas_create(void){
    // calloc - os campos começam a NULL, para o destroy ser seguro mesmo antes de tudo estar criado
    GestorEstatisticas *ge = calloc(1,sizeof(GestorEstatisticas));
    if (ge == NULL)return NULL;

    // g_free - a chave é uma cópia do id (stdup), por isso a tabela é dona dela
    // free - cada estatística é criada com calloc no registrar_linha
    ge->por_produto = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);

    return ge;
}

void gestor_estatisticas_destroy(GestorEstatisticas *ge){
    if(ge== NULL)return;
     // a tabela liberta cada chave e cada estatística com as funções dadas no create
    g_hash_table_destroy(ge->por_produto);

    free(ge);   
}

bool gestor_estatisticas_registrar_linha(GestorEstatisticas *ge, const LinhaEncomenda *le, EstadoEncomenda estado){
    if(ge==NULL||le==NULL)return false;

    // encomenda cancelada não conta para as estatísticas, mas não é um erro
    if (estado == ENCOMENDA_CANCELADA)return true;

    // o id pertence a linha - aqui só é lido
    const char *id = linha_encomenda_get_id_produto(le);


    // procura as estatísticas deste produto (NULL se ainda não vendeu nada)
    EstatisticaProduto *ep = g_hash_table_lookup(ge->por_produto, id);

    if (ep == NULL){
        // primeira venda do produto - estatística nova
        ep = calloc(1, sizeof(EstatisticaProduto));
        if (ep == NULL)return false;

        g_hash_table_insert(ge->por_produto, g_strdup(id), ep);
    }
    // o ep aponta para a estatística que está na tabela, por isso não é preciso voltar a inserir
    ep->receita_cents += linha_encomenda_subtotal_cents(le);

    ep->unidades += linha_encomenda_get_quantidade(le);

    return true;
}

int gestor_estatisticas_get_unidades(const GestorEstatisticas *ge, const char *id){
    if(ge == NULL || id == NULL)return 0;
    EstatisticaProduto *ep = g_hash_table_lookup(ge->por_produto, id);
    // produto sem vendas não tem entrada na tabela
    if (ep==NULL)return 0;
    return ep->unidades;
}

int64_t gestor_estatisticas_get_receita_cents(const GestorEstatisticas *ge, const char *id){
    if (ge == NULL || id == NULL)return 0;
    EstatisticaProduto *ep = g_hash_table_lookup(ge->por_produto, id);
    // produto sem vendas não tem entrada na tabela
    if(ep == NULL)return 0;
    return ep->receita_cents;
}