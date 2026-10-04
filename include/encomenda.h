#ifndef ENCOMENDA_H
#define ENCOMENDA_H

typedef struct encomenda Encomenda;

typedef enum EstadoEncomenda{
    ENCOMENDA_PAGA,
    ENCOMENDA_ENVIADA,
    ENCOMENDA_ENTREGUE,
    ENCOMENDA_CANCELADA
}EstadoEncomenda;




#endif
