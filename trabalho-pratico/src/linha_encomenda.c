#include "linha_encomenda.h"
#include <stdlib.h>

//os ids não são copiados: apontam para os ids da Encomenda e do Produto, que vivem até ao fim do programa
struct linhaEncomenda{
    const char *id_encomenda;
    const char *id_produto;
    int quantidade;
    int64_t preco_unitario_cents;
};

LinhaEncomenda *linha_encomenda_nova(const char *id_encomenda, const char *id_produto, int quantidade, int64_t preco_unitario_cents){
     // Reserva o bloco da linha; se não houver memória, avisa quem chamou com NULL
    LinhaEncomenda *le = malloc(sizeof(LinhaEncomenda));
    if(le == NULL) return NULL;

    le->id_encomenda = id_encomenda;

    le->id_produto = id_produto;

    le->quantidade = quantidade;

    le->preco_unitario_cents = preco_unitario_cents;

    return le;
}

void linha_encomenda_destroy(LinhaEncomenda *le){
    if(le == NULL) return;

    free(le);
}

int64_t linha_encomenda_subtotal_cents(const LinhaEncomenda *le){
    // A quantidade (int) é convertida para int64_t antes de multiplicar por isso o resultado n estoura.
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