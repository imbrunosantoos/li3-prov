#ifndef GESTOR_LINHAS_ENCOMENDA_H
#define GESTOR_LINHAS_ENCOMENDA_H

#include "linha_encomenda.h"
#include <stdbool.h>

typedef struct gestorLinhaEncomenda GestorLinhaEncomenda;

GestorLinhaEncomenda *gestor_linha_encomenda_create(void);

void gestor_linha_encomenda_destroy(GestorLinhaEncomenda *gl);

bool gestor_linha_encomenda_inserir(GestorLinhaEncomenda *gl, LinhaEncomenda *le);

int gestor_linha_encomenda_num_linhas(const GestorLinhaEncomenda *gl, const char *id_encomenda);

const LinhaEncomenda *gestor_linha_encomenda_get_linha(const GestorLinhaEncomenda *gl, const char *id_encomenda, int i);

bool gestor_linha_encomenda_existe_par(const GestorLinhaEncomenda *gl, const char *id_encomenda, const char *id_produto);

#endif