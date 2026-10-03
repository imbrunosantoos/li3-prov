#include "produto.h"

struct produto{
    char *id;
    char *nome;
    char *categoria;
    int64_t preco_atual_cents;
    char *id_vendedor;
    EstadoProduto estado;
};



const char *produto_get_id(const Produto *p){
    return p->id;
}
