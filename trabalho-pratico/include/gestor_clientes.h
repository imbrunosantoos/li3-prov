#ifndef GESTOR_CLIENTES_H
#define GESTOR_CLIENTES_H

#include <stdbool.h>
#include "cliente.h"

typedef struct gestorClientes GestorClientes;

GestorClientes *gestor_clientes_create(void);
void gestor_clientes_destroy(GestorClientes *gc);
bool gestor_clientes_inserir(GestorClientes *gc, Cliente *c);
const Cliente *gestor_clientes_procurar (const GestorClientes *gc, const char *id);

#endif