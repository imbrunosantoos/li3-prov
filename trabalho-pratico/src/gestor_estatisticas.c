#include "gestor_estatisticas.h"

#include <glib.h>
#include <stdlib.h>
#include <string.h>

// estatísticas de um produto - privada, ninguém fora deste .c sabe que existe
typedef struct estatisticaProduto{
    int unidades;
    int64_t receita_cents;
}EstatisticaProduto;

//uma posição do ranking-o produto e as unidades já calculadas
//assim a ordenação compara números em vez de ir procurar à tabela
typedef struct itemRanking{
    const Produto *p;
    int unidades;
}ItemRanking;

struct gestorEstatisticas{
    GHashTable *por_produto;
    ItemRanking *ranking;   // array ordenado- posição 0 = mais vendido
    int n_ranking;          // quantas posições tem
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

    // só o array, os produtos pertencem ao gestor de produtos
    free(ge->ranking);
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

// o qsort chama esta função para saber qual de dois itens vem primeiro:
// negativo = a vem antes, positivo = b vem antes
//precisa do const void por causa do qsort
static int comparar_ranking(const void *a, const void *b){
    const ItemRanking *x = a;
    const ItemRanking *y = b;
    // mais unidades primeiro
    if (x->unidades > y->unidades)
        return -1;
    if (x->unidades < y->unidades)
        return 1;
    // empate: id menor primeiro
    return strcmp(produto_get_id(x->p), produto_get_id(y->p));
}

bool gestor_estatisticas_construir_ranking(GestorEstatisticas *ge, const GestorProdutos *gp){
    if (ge == NULL || gp == NULL) return false;

    int n;
    const Produto **lista = gestor_produtos_lista(gp, &n);
    if (lista == NULL) return false;

    ItemRanking *ranking = malloc(n * sizeof(ItemRanking));
    if (ranking == NULL){
        free(lista);
        return false;
    }

    // junta a cada produto as suas unidades (0 se nunca vendeu)
    for (int i = 0; i < n; i++){
        ranking[i].p = lista[i];
        ranking[i].unidades = gestor_estatisticas_get_unidades(ge, produto_get_id(lista[i]));
    }
    // a lista já não é precisa pq  os apontadores passaram para o ranking
    free(lista);

    // ordena uma única vez- a partir daqui a Q2 só lê
    qsort(ranking, n, sizeof(ItemRanking), comparar_ranking);

    ge->ranking = ranking;
    ge->n_ranking = n;
    return true;
}

int gestor_estatisticas_ranking_num(const GestorEstatisticas *ge){
    if (ge == NULL) return 0;
    return ge->n_ranking;
}

const Produto *gestor_estatisticas_ranking_get(const GestorEstatisticas *ge, int i){
    if (ge == NULL || i < 0 || i >= ge->n_ranking) return NULL;
    return ge->ranking[i].p;
}
