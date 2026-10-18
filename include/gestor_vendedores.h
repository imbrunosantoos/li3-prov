#ifndef GESTOR_VENDEDORES_H
#define GESTOR_VENDEDORES_H

#include <stdbool.h>
#include "vendedor.h"

typedef struct gestorVendedores GestorVendedores;

GestorVendedores *gestor_vendedores_create(void);
void gestor_vendedores_destroy(GestorVendedores *gc);
bool gestor_vendedores_inserir(GestorVendedores *gc, Vendedor *c);
const Vendedor *gestor_vendedores_procurar (const GestorVendedores *gc, const char *id);

#endif