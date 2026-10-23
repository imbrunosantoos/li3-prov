#ifndef GESTOR_LINHAS_ENCOMENDA_H
#define GESTOR_LINHAS_ENCOMENDA_H

#include "linha_encomenda.h"
#include <stdbool.h>

typedef struct gestorLinhaEncomenda GestorLinhaEncomenda;

/**
 * @brief Cria um gestor de linhas de encomenda vazio
 *
 * @return Ponteiro para o novo gestor, a libertar com gestor_linha_encomenda_destroy
 */

GestorLinhaEncomenda *gestor_linha_encomenda_create(void);

/**
 * @brief Destrói o gestor e todas as linhas que ele contém
 *
 * @param gl Gestor a destruir(se for NULL nao faz nada)
 */

void gestor_linha_encomenda_destroy(GestorLinhaEncomenda *gl);

/**
 * @brief Insere uma linha na lista da sua encomenda
 *
 * A linha é guardada junto das outras linhas da mesma encomenda pela ordem de chegada
 * O gestor passa sempre a ser o dono da linha se a inserção falhar
 * gestor ou linha NULL ou par (encomenda, produto) já existente, a linha é
 * destruída pelo próprio gestor
 *
 * @param gl Gestor onde inserir
 * @param le Linha a inserir
 *
 * @return true se a linha foi inserida, false caso contrário
 */

bool gestor_linha_encomenda_inserir(GestorLinhaEncomenda *gl, LinhaEncomenda *le);

/**
 * @brief Devolve o número de linhas de uma encomenda
 *
 * @param gl           Gestor onde procurar
 * @param id_encomenda Id da encomenda
 *
 * @return Número de linhas da encomenda, ou 0 se ela não tiver linhas, gl ou id_encomenda forem NULL
 */

int gestor_linha_encomenda_num_linhas(const GestorLinhaEncomenda *gl, const char *id_encomenda);

/**
 * @brief Devolve a linha numa dada posição da lista de uma encomenda
 *
 * @param gl           Gestor onde procurar
 * @param id_encomenda Id da encomenda
 * @param i            Posição da linha na lista- começa em 0
 *
 * @return A linha na posição i, ou NULL se a posição não existir
 */

const LinhaEncomenda *gestor_linha_encomenda_get_linha(const GestorLinhaEncomenda *gl, const char *id_encomenda, int i);

/**
 * @brief Verifica se uma encomenda já tem uma linha de um dado produto
 *
 * @param gl           Gestor onde procurar
 * @param id_encomenda Id da encomenda
 * @param id_produto   Id do produto
 *
 * @return true se já existir uma linha com este par, false caso contrário
 */

bool gestor_linha_encomenda_existe_par(const GestorLinhaEncomenda *gl, const char *id_encomenda, const char *id_produto);

#endif