#include "encomenda.h"
#include "linha_encomenda.h"

struct encomenda{
    char *id;
    char *id_cliente;
    char *data;
    EstadoEncomenda estado;
};