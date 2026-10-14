#include "produto.h"
#include <string.h>
#include <stdlib.h>

struct produto{
    char *id;
    char *nome;
    char *categoria;
    int64_t preco_atual_cents;
    char *id_vendedor;
    EstadoProduto estado;
};


Produto *produto_novo(const char *id, const char *nome, const char *categoria, int64_t preco_atual_cents, const char *id_vendedor, EstadoProduto estado){
    Produto *produto = malloc(sizeof(Produto));
    if(produto == NULL) return NULL;

     // strdup: o parser reutiliza o buffer da linha, por isso guardamos cópias nossas
    char *id1 = strdup(id);
    produto->id = id1;

    char *nome1 = strdup(nome);
    produto->nome = nome1;

    char *categoria1 = strdup(categoria);
    produto->categoria = categoria1;

    char *id_vendedor1 = strdup(id_vendedor);
    produto->id_vendedor = id_vendedor1;

    //possivel memory leak da funcao strdup caso ela falhar
    if(produto->id_vendedor == NULL || produto->categoria == NULL || produto->id == NULL || produto->nome == NULL){
        produto_destroy(produto);
        return NULL;
    }
    produto->preco_atual_cents = preco_atual_cents;
    produto->estado = estado;

    return produto;
}

void produto_destroy(Produto *p){
    if(p == NULL) return;
    // primeiro as strings pq depois de free(p) já não se pode aceder a p->
    free(p->id); 
    free(p->nome);
    free(p->categoria);
    free(p->id_vendedor);
    free(p);
}

const char *produto_get_id(const Produto *p){
    return p->id;
}

const char *produto_get_nome(const Produto *p){
    return p->nome;
}

const char *produto_get_categoria(const Produto *p){
    return p->categoria;
}

int64_t produto_get_preco_atual_cents(const Produto *p){
    return p->preco_atual_cents;
}

const char *produto_get_id_vendedor(const Produto *p){
    return p->id_vendedor;
}

EstadoProduto produto_get_estado_produto(const Produto *p){
    return p->estado;
}