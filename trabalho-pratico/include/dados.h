#ifndef DADOS_H
#define DADOS_H
#include "gestor_produtos.h"
#include "gestor_encomendas.h"
#include "gestor_clientes.h"
#include "gestor_vendedores.h"
#include "gestor_linhas_encomenda.h"

typedef struct dados Dados;

/**
 * @brief   Cria a estrutura de dados
 * @return  Nova estrutura de dados (a libertar com dados_destruir), ou NULL se não houver memória
 */
Dados *dados_criar(void);

/**
 * @brief   Destrói a estrutura de dados e todos os gestores que ela contém
 * @param d A estrutura de dados a destruir
 */
void dados_destruir(Dados *d);

/**
 * @brief   Dá acesso ao gestor de produtos, só para leitura. É o getter que as queries devem usar.
 * @param d Estrutura de dados.
 * @return  O gestor de produtos. Pertence à estrutura de dados: não fazer free nem destroy (é libertado pelo dados_destruir).
 */
const GestorProdutos *dados_get_produtos(const Dados *d);

/**
 * @brief   Dá acesso ao gestor de produtos, para inserir dados. É o getter que o carregamento deve usar (as queries usam dados_get_produtos).
 * @param d Estrutura de dados.
 * @return  O gestor de produtos, onde se pode inserir. Pertence à estrutura de dados: não fazer free nem destroy (é libertado pelo dados_destruir).
 */
GestorProdutos *dados_get_produtos_mut(Dados *d);

/**
 * @brief   Dá acesso ao gestor de clientes, só para leitura. É o getter que as queries devem usar.
 * @param d Estrutura de dados.
 * @return  O gestor de clientes. Pertence à estrutura de dados: não fazer free nem destroy (é libertado pelo dados_destruir).
 */
const GestorClientes *dados_get_clientes(const Dados *d);

/**
 * @brief   Dá acesso ao gestor de clientes, para inserir dados. É o getter que o carregamento deve usar (as queries usam dados_get_clientes).
 * @param d Estrutura de dados.
 * @return  O gestor de clientes, onde se pode inserir. Pertence à estrutura de dados: não fazer free nem destroy (é libertado pelo dados_destruir).
 */
GestorClientes *dados_get_clientes_mut(Dados *d);

/**
 * @brief   Dá acesso ao gestor de encomendas, só para leitura. É o getter que as queries devem usar.
 * @param d Estrutura de dados.
 * @return  O gestor de encomendas. Pertence à estrutura de dados: não fazer free nem destroy (é libertado pelo dados_destruir).
 */
const GestorEncomendas *dados_get_encomendas(const Dados *d);

/**
 * @brief   Dá acesso ao gestor de encomendas, para inserir dados. É o getter que o carregamento deve usar (as queries usam dados_get_encomendas).
 * @param d Estrutura de dados.
 * @return  O gestor de encomendas, onde se pode inserir. Pertence à estrutura de dados: não fazer free nem destroy (é libertado pelo dados_destruir).
 */
GestorEncomendas *dados_get_encomendas_mut(Dados *d);

/**
 * @brief   Dá acesso ao gestor de vendedores, só para leitura. É o getter que as queries devem usar.
 * @param d Estrutura de dados.
 * @return  O gestor de vendedores. Pertence à estrutura de dados: não fazer free nem destroy (é libertado pelo dados_destruir).
 */
const GestorVendedores *dados_get_vendedores(const Dados *d);

/**
 * @brief   Dá acesso ao gestor de vendedores, para inserir dados. É o getter que o carregamento deve usar (as queries usam dados_get_vendedores).
 * @param d Estrutura de dados.
 * @return  O gestor de vendedores, onde se pode inserir. Pertence à estrutura de dados: não fazer free nem destroy (é libertado pelo dados_destruir).
 */
GestorVendedores *dados_get_vendedores_mut(Dados *d);

/**
 * @brief   Dá acesso ao gestor de linhas de encomenda, só para leitura. É o getter que as queries devem usar.
 * @param d Estrutura de dados.
 * @return  O gestor de linhas de encomenda. Pertence à estrutura de dados: não fazer free nem destroy (é libertado pelo dados_destruir).
 */
const GestorLinhaEncomenda *dados_get_linhasencomendas(const Dados *d);

/**
 * @brief   Dá acesso ao gestor de linhas de encomenda, para inserir dados. É o getter que o carregamento deve usar (as queries usam dados_get_linhasencomendas).
 * @param d Estrutura de dados.
 * @return  O gestor de linhas de encomendas, onde se pode inserir. Pertence à estrutura de dados: não fazer free nem destroy (é libertado pelo dados_destruir).
 */
GestorLinhaEncomenda *dados_get_linhasencomendas_mut(Dados *d);

#endif