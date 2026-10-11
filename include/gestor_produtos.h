#ifndef GESTOR_PRODUTOS_H
#define GESTOR_PRODUTOS_H

#include "produto.h"
#include <stdbool.h>

typedef struct gestorProdutos GestorProdutos;

/**
 * @brief Cria um gestor de produtos vazio
 *
 * @return Ponteiro para o novo gestor, ou NULL se não houver memória
 *         
 */

GestorProdutos *gestor_produtos_create(void);

/**
 * @brief Insere um produto no gestor, o gestor passa a ser o dono do produto
 * se a inserção falhar, o próprio gestor destrói o produto
 * 
 * @param ge Gestor onde inserir
 * @param p  Produto a inserir
 * 
 * @return true se o produto foi inserido, false caso contrário
 */

bool gestor_produtos_inserir(GestorProdutos *ge, Produto *p);

/**
 * @brief Procura um produto pelo seu id
 * @param ge Gestor onde procurar
 * @param id Id do produto
 * 
 * @return O produto com esse id, ou NULL se não existir
 */

const Produto *gestor_produtos_procurar(const GestorProdutos *ge, const char *id);

/**
 * @brief Destrói o gestor e todos os produtos que ele contém
 * 
 * @param ge Gestor a destruir
 */

void gestor_produtos_destroy(GestorProdutos *ge);


#endif