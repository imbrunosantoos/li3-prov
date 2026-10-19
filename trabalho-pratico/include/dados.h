#ifndef DADOS_H
#define DADOS_H
#include "gestor_produtos.h"

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

#endif