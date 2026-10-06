#ifndef ENCOMENDA_H
#define ENCOMENDA_H

typedef struct encomenda Encomenda;

typedef enum EstadoEncomenda{
    ENCOMENDA_PAGA,
    ENCOMENDA_ENVIADA,
    ENCOMENDA_ENTREGUE,
    ENCOMENDA_CANCELADA
}EstadoEncomenda;

Encomenda *encomenda_nova(const char *id, const char *id_cliente, const char *data, EstadoEncomenda estado);

void encomenda_destroy(Encomenda *e);

//-----Funçoes Getters

const char *encomenda_get_id(const Encomenda *e);

const char *encomenda_get_id_cliente(const Encomenda *e);

const char *encomenda_get_data(const Encomenda *e);

EstadoEncomenda encomenda_get_estado_encomenda(const Encomenda *e);


#endif
