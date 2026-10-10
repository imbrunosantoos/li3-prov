#ifndef  VALIDADORES_H
#define  VALIDADORES_H
#include <stdbool.h>

typedef enum {
    ESTADO_PROD_INVALIDO = -1,
    ESTADO_PROD_ATIVO,
    ESTADO_PROD_DESCONTINUADO
} EstadoProduto;

typedef enum {
    ESTADO_ENC_INVALIDO = -1,
    ESTADO_ENC_PAGA,
    ESTADO_ENC_ENVIADA,
    ESTADO_ENC_ENTREGUE,
    ESTADO_ENC_CANCELADA
} EstadoEncomenda;

bool validar_id(const char *id, char prefixo);
bool validar_data(const char *data );
bool validar_texto(const char *str);
bool validar_sem_espacos(const char *str);


bool  validar_preco (const char *texto, int64_t *cents);
bool validar_quantidade (const char *texto, int *quantidade);
bool validar_estado_produto (const char *texto, EstadoProduto *estado);
bool validar_estado_encomenda (const char *texto, EstadoEncomenda *estado);


bool validar_linha_cliente(const char  **campos, int n_campos);
bool validar_linha_vendedor(const char  **campos, int n_campos);

#endif