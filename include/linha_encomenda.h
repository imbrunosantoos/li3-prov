#ifndef LINHA_ENCOMENDA_H
#define LINHA_ENCOMENDA_H

// Necessário para o tipo int64_t inteiro com  64 bits que o guiao recomenda
#include <stdint.h>


typedef struct linhaEncomenda LinhaEncomenda;

LinhaEncomenda *linha_encomenda_nova(const char *id_encomenda, const char *id_produto, int quantidade, int64_t preco_unitario_cents);

void linha_encomenda_destroy(LinhaEncomenda *le);

int64_t linha_encomenda_subtota_cents(const LinhaEncomenda *le);

// ------Funcoes GETTERS

const char *linha_encomenda_get_id_encomenda(const LinhaEncomenda *le);

const char *linha_encomenda_get_id_produto(const LinhaEncomenda *le);

int linha_encomenda_get_quantidade(const LinhaEncomenda *le);

int64_t linha_encomenda_get_preco_unitario_cents(const LinhaEncomenda *le);




#endif