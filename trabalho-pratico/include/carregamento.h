#ifndef CARREGAMENTO_H
#define CARREGAMENTO_H

#include "gestor_clientes.h"
#include "gestor_vendedores.h"
#include "gestor_produtos.h"
#include "gestor_encomendas.h"
#include "gestor_linhas_encomenda.h"




int carregar_clientes(const char *entrada, const char *erros, GestorClientes *gc) ;

int carregar_vendedores(const char *entrada, const char *erros, GestorVendedores *gv) ;

int carregar_produtos(const char *entrada, const char *erros, GestorProdutos *gp, GestorVendedores *gv) ;

int carregar_encomendas(const char *entrada, const char *erros, GestorEncomendas *ge, GestorClientes *gc); ;

int carregar_linhas_encomendas(const char *entrada, const char *erros, GestorLinhaEncomenda *gl, GestorEncomendas *gc); 

#endif
