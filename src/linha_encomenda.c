#include "linha_encomenda.h"

#include <string.h>
#include <stdlib.h>


struct linhaEncomenda{
    char *id_encomenda;
    char *id_produto;
    int quantidade;
    int64_t preco_unitario_cents;
};

LinhaEncomenda *linha_encomenda_nova(const char *id_encomenda, const char *id_produto, int quantidade, int64_t preco_unitario_cents){
    LinhaEncomenda *le = malloc(sizeof(LinhaEncomenda));
    if(le == NULL) return NULL;


    char *id_encomenda1 = strdup(id_encomenda);
    le->id_encomenda = id_encomenda1;

    char *id_produto1 = strdup(id_produto);
    le->id_produto = id_produto1;

    le->quantidade = quantidade;

    le->preco_unitario_cents = preco_unitario_cents;

    if(le->id_encomenda == NULL || le->id_produto == NULL){
        linha_encomenda_destroy(le);
        return NULL;
    }
    return le;
}

void linha_encomenda_destroy(LinhaEncomenda *le){
    if(le == NULL) return;

    free(le->id_encomenda);
    free(le->id_produto);

    free(le);
}

int64_t linha_encomenda_subtotal_cents(const LinhaEncomenda *le){
    return (le->quantidade * le->preco_unitario_cents);
}

const char *linha_encomenda_get_id_encomenda(const LinhaEncomenda *le){
    return le->id_encomenda;
}

const char *linha_encomenda_get_id_produto(const LinhaEncomenda *le){
    return le->id_produto;
}

int linha_encomenda_get_quantidade(const LinhaEncomenda *le){
    return le->quantidade;
}

int64_t linha_encomenda_get_preco_unitario_cents(const LinhaEncomenda *le){
    return le->preco_unitario_cents;
}