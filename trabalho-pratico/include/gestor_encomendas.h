#ifndef GESTOR_ENCOMENDAS_H
#define GESTOR_ENCOMENDAS_H

#include "encomenda.h"
#include <stdbool.h>

typedef struct gestorEncomendas GestorEncomendas;

/**
 * @brief Cria um gestor de encomendas vazio
 *
 * @return Ponteiro para o novo gestor, a libertar com gestor_encomendas_destroy
 *         ou NULL se não houver memória
 */

GestorEncomendas *gestor_encomendas_create(void);

/**
 * @brief Insere uma encomenda no gestor
 *
 * O gestor passa sempre a ser o dono da encomenda -se a inserção falhar 
 * a encomenda é destruída pelo próprio gestor
 *
 * @param ge Gestor onde inserir
 * @param e  Encomenda a inserir
 *
 * @return true se a encomenda foi inserida, false caso contrário
 */
bool gestor_encomendas_inserir(GestorEncomendas *ge, Encomenda *e);

/**
 * @brief Procura uma encomenda pelo seu id
 *
 * Usamos o const para garantir que só pode ser lida,
 * nunca alterada nem libertada por quem a recebe
 *
 * @param ge Gestor onde procurar
 * @param id Id da encomenda
 *
 * @return A encomenda com esse id, ou NULL se não existir
 */

const Encomenda *gestor_encomendas_procurar(const GestorEncomendas *ge, const char *id);

/**
 * @brief Destrói o gestor e todas as encomendas que ele contém
 *
 * @param ge Gestor a destruir (se for NULL, não faz nada)
 */

void gestor_encomendas_destroy(GestorEncomendas *ge);


#endif