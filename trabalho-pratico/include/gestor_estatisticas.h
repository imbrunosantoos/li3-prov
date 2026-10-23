#ifndef GESTOR_ESTATISTICAS_H
#define GESTOR_ESTATISTICAS_H

#include <stdint.h>
#include <stdbool.h>
#include "linha_encomenda.h"
#include "encomenda.h"

typedef struct gestorEstatisticas GestorEstatisticas;

GestorEstatisticas *gestor_estatisticas_create(void);

void gestor_estatisticas_destroy(GestorEstatisticas *ge);

bool gestor_estatisticas_registrar_linha(GestorEstatisticas *ge, const LinhaEncomenda *le, EstadoEncomenda estado);

int gestor_estatisticas_get_unidades(const GestorEstatisticas *ge, const char *id);

int64_t gestor_estatisticas_get_receita_cents(const GestorEstatisticas *ge, const char *id);


#endif