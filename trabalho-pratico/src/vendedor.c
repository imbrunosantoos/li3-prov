#include "vendedor.h"
#include <stdlib.h>
#include <string.h>


#define TAM_BUFFER 1024

struct vendedor {
    char *id;
    char *nome;
    char *categoria;
    char *data;
};

Vendedor *vendedor_novo(const char *id, const char *nome, const char *categoria, const char *data) {
    Vendedor *v = malloc (sizeof(struct vendedor));
    if (v == NULL) return NULL;
    v -> id = strdup(id);
    v -> nome = strdup (nome);
    v -> categoria = strdup (categoria);
    v -> data = strdup (data);
    
    if (!v->id || !v->nome || !v->categoria || !v->data) {
        free (v -> id);
        free (v -> nome);
        free ( v -> categoria);
        free (v -> data);
        free (v);
        return NULL;
    }
    
     return v;
}    

void vendedor_destroy(void *vendedor_ptr) {
    Vendedor *v = (Vendedor *)vendedor_ptr;
    if (v == NULL) return;
    free (v -> id);
    free (v -> nome);
    free ( v -> categoria);
    free (v -> data);
    free (v);
}

const char *get_vendedor_id (const Vendedor *v){
    if (v == NULL) return NULL;
    return v-> id;
}

const char *get_vendedor_nome (const Vendedor *v){
    if (v == NULL) return NULL;
    return v-> nome;
}

const char *get_vendedor_data (const Vendedor *v){
    if (v == NULL) return NULL;
    return v-> data;
}
const char *get_vendedor_categoria (const Vendedor *v){
    if (v == NULL) return NULL;
    return v-> categoria;
}



