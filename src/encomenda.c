#include "encomenda.h"

#include <string.h>
#include <stdlib.h>

struct encomenda{
    char *id;
    char *id_cliente;
    char *data;
    EstadoEncomenda estado;
};

Encomenda *encomenda_nova(const char *id, const char *id_cliente, const char *data, EstadoEncomenda estado){
    Encomenda *e = malloc(sizeof(Encomenda));
    if(e == NULL) return NULL;

    char *id1 = strdup (id);
    e->id = id1;

    char *id_cliente1 = strdup (id_cliente);
    e->id_cliente = id_cliente1;

    char *data1 = strdup (data);
    e->data = data1;

    e->estado = estado;

    if(e->id == NULL || e->id_cliente == NULL || e->data == NULL){
        encomenda_destroy(e);
        return NULL;
    }
    return e;
}

void encomenda_destroy(Encomenda *e){
    if(e == NULL) return;
    
    free(e->id);
    free(e->id_cliente);
    free(e->data);

    free(e);
}

const char *encomenda_get_id(const Encomenda *e){
    return e->id;
}

const char *encomenda_get_id_cliente(const Encomenda *e){
    return e->id_cliente;
}

const char *encomenda_get_data(const Encomenda *e){
    return e->data;
}

EstadoEncomenda encomenda_get_estado_encomenda(const Encomenda *e){
    return e->estado;
}
