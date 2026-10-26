#ifndef GESTOR_ESTATISTICAS_H
#define GESTOR_ESTATISTICAS_H

#include <stdint.h>
#include <stdbool.h>
#include "linha_encomenda.h"
#include "encomenda.h"

typedef struct gestorEstatisticas GestorEstatisticas;

/**
 * @brief Cria um gestor de estatísticas vazio
 * 
 * @return Ponteiro para o novo gestor, a libertar com gestor_estatisticas_destroy,
 *         ou NULL se não houver memória
 */

GestorEstatisticas *gestor_estatisticas_create(void);

/**
 * @brief Destrói o gestor e todas as estatísticas que ele contém
 *
 * @param ge Gestor a destruir (se for NULL não faz nada)
 */

void gestor_estatisticas_destroy(GestorEstatisticas *ge);


/**
 * @brief Acumula uma linha de encomenda nas estatísticas do seu produto
 *
 * Soma a quantidade e o subtotal da linha as estatísticas do produto, criando elas
 * na primeira venda(as linhas de encomendas canceladas não contam para as
 * estatísticas mas são aceites)
 *
 * @param ge Gestor onde acumular
 * @param le Linha de encomenda válida
 * @param estado Estado da encomenda a que a linha pertence
 *
 * @return true se a linha foi tratada false se o gestor ou a linha forem NULL
 */

bool gestor_estatisticas_registrar_linha(GestorEstatisticas *ge, const LinhaEncomenda *le, EstadoEncomenda estado);

/**
 * @brief Devolve as unidades vendidas de um produto
 *
 * @param ge Gestor a consultar
 * @param id Identificador do produto
 *
 * @return Soma das quantidades das linhas não canceladas do produto ou 0 se o
 *         produto não tiver vendas, não existir ou algum argumento for NULL
 */

int gestor_estatisticas_get_unidades(const GestorEstatisticas *ge, const char *id);

/**
 * @brief Devolve a receita gerada por um produto, em cêntimos
 *
 * @param ge Gestor a consultar
 * @param id Identificador do produto
 *
 * @return Soma de quantidade * preco_unitario das linhas não canceladas do produto,
 *         em cêntimos, ou 0 se o produto não tiver vendas não existir ou algum
 *         argumento for NULL
 */

int64_t gestor_estatisticas_get_receita_cents(const GestorEstatisticas *ge, const char *id);


#endif