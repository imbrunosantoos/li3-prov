#ifndef GESTOR_CLIENTES_H
#define GESTOR_CLIENTES_H

#include <stdbool.h>
#include "cliente.h"

typedef struct gestorClientes GestorClientes;
/**
 * @brief Cria um gestor de clientes vazio
 *
 * @return Ponteiro para o novo gestor, ou NULL se não houver memória
 */
GestorClientes *gestor_clientes_create(void);

/**
 * @brief Destrói o gestor e todos os clientes que ele contém
 *
 * @param gc Gestor a destruir (se for NULL, não faz nada)
 */
void gestor_clientes_destroy(GestorClientes *gc);

/**
 * @brief Insere um cliente no gestor, o gestor passa a ser o dono do cliente
 * se a inserção falhar (argumentos nulos ou id repetido), o próprio gestor destrói o cliente
 *
 * @param gc Gestor onde inserir
 * @param c  Cliente a inserir
 *
 * @return true se o cliente foi inserido, false caso contrário
 */

bool gestor_clientes_inserir(GestorClientes *gc, Cliente *c);


/**
 * @brief Procura um cliente pelo seu id
 * @param gc Gestor onde procurar
 * @param id Id do cliente
 *
 * @return O cliente com esse id, ou NULL se não existir
 */

const Cliente *gestor_clientes_procurar (const GestorClientes *gc, const char *id);

#endif