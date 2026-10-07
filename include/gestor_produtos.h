#ifndef GESTOR_PRODUTOS_H
#define GESTOR_PRODUTOS_H

#include "produto.h"
#include <stdbool.h>

typedef struct gestorProdutos GestorProdutos;

GestorProdutos *gestor_produtos_create(void);

bool gestor_produtos_inserir(GestorProdutos *ge, Produto *p);

const Produto *gestor_produtos_procurar(const GestorProdutos *ge, const char *id);

void gestor_produtos_destroy(GestorProdutos *ge);


#endif