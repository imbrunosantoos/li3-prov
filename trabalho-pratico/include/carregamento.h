#ifndef CARREGAMENTO_H
#define CARREGAMENTO_H

#include "gestor_clientes.h"
#include "gestor_vendedores.h"


int carregar_clientes(const char *entrada, const char *erros, GestorClientes *gc) ;

int carregar_vendedores(const char *entrada, const char *erros, GestorVendedores *gv) ;

#endif