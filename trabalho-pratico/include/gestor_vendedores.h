#ifndef GESTOR_VENDEDORES_H
#define GESTOR_VENDEDORES_H

#include <stdbool.h>
#include "vendedor.h"

typedef struct gestorVendedores GestorVendedores;
/**
 * @brief Cria um gestor de vendedores vazio
 *
 * @return Ponteiro para o novo gestor, ou NULL se não houver memória
 */
GestorVendedores *gestor_vendedores_create(void);

/**
 * @brief Destrói o gestor e todos os vendedores que ele contém
 *
 * @param gv Gestor a destruir (se for NULL, não faz nada)
 */

void gestor_vendedores_destroy(GestorVendedores *gc);

/**
 * @brief Insere um vendedor no gestor, o gestor passa a ser o dono do vendedor
 * se a inserção falhar (argumentos nulos ou id repetido), o próprio gestor destrói o vendedor
 *
 * @param gv Gestor onde inserir
 * @param v  Vendedor a inserir
 *
 * @return true se o vendedor foi inserido, false caso contrário
 */

bool gestor_vendedores_inserir(GestorVendedores *gc, Vendedor *c);


/**
 * @brief Procura um vendedor pelo seu id
 * @param gv Gestor onde procurar
 * @param id Id do vendedor
 *
 * @return O vendedor com esse id, ou NULL se não existir
 */

const Vendedor *gestor_vendedores_procurar (const GestorVendedores *gc, const char *id);

#endif