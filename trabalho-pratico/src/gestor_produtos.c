#include "gestor_produtos.h"

#include <stdlib.h>
#include <glib.h>

/*
criar a tabela	-----g_hash_table_new_full(hash, igual, liberta_chave, liberta_valor)
hash de strings	---- g_str_hash
comparar string ---- g_str_equal
guardar------------	g_hash_table_insert(tabela, chave, valor)
ver se existe------	g_hash_table_contains(tabela, chave)
procurar--------	g_hash_table_lookup(tabela, chave) (devolve NULL se não existir)
destruir tudo------ g_hash_table_destroy(tabela)
cast do destrutor---(GDestroyNotify)
*/
struct gestorProdutos{
    GHashTable *produtos;
};

GestorProdutos *gestor_produtos_create(void){
    GestorProdutos *gp = malloc(sizeof(GestorProdutos));
    if (gp== NULL)return NULL;
    //o cast(GDestroNotify) é preciso pq a glib espera uma funcao que receba void
    gp->produtos = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)produto_destroy);
    return gp;
}

void gestor_produtos_destroy(GestorProdutos *ge){
    if (ge == NULL)return;
     // destrói a tabela, que chama produto_destroy em cada produto
    g_hash_table_destroy(ge->produtos);
    // só depois liberta a caixa, porque a tabela estava guardada lá dentro
    free(ge);
}


bool gestor_produtos_inserir(GestorProdutos *ge, Produto *p){
    if(ge == NULL || p == NULL) {
        produto_destroy(p);
        return false;
    }
    // o produto é opaco, por isso o id só se obtém pelo getter
    const char *id1 = produto_get_id(p);
    // id repetido - recusa, sem substituir o produto que já lá está
    if(g_hash_table_contains(ge->produtos, id1)){
        produto_destroy(p);
        return false;
    } 
    // cast para gpointer: a glib recebe a chave sem const
    g_hash_table_insert(ge->produtos, (gpointer)id1, p);
    return true;

}

const Produto *gestor_produtos_procurar(const GestorProdutos *ge, const char *id){
    if (ge == NULL || id == NULL)return NULL;
    // o lookup já devolve NULL quando o id não existe
    return g_hash_table_lookup(ge->produtos, id);
}
