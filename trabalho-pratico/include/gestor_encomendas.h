#ifndef GESTOR_ENCOMENDAS_H
#define GESTOR_ENCOMENDAS_H

#include "encomenda.h"
#include <stdbool.h>

typedef struct gestorEncomendas GestorEncomendas;

GestorEncomendas *gestor_encomendas_create(void);

bool gestor_encomendas_inserir(GestorEncomendas *ge, Encomenda *e);

const Encomenda *gestor_encomendas_procurar(const GestorEncomendas *ge, const char *id);

void gestor_encomendas_destroy(GestorEncomendas *ge);


#endif