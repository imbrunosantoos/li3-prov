#include "cliente.h"
#include <stdlib.h>
#include <string.h>





struct cliente {
    char *id;
    char *nome;
    char *regiao;
    char *data;
};

Cliente *cliente_novo (const char *id, const char *nome, const char *regiao, const char *data){
    Cliente *c = malloc (sizeof(struct cliente));
    if (c == NULL) return NULL;
    c -> id = strdup(id);
    c -> nome = strdup (nome);
    c -> regiao = strdup (regiao);
    c -> data = strdup (data);
    
    if (!c->id || !c->nome || !c->regiao || !c->data) {
        free(c->id);
        free(c->nome);
        free(c->regiao);
        free(c->data);
        free(c);
        return NULL;
    }

    return c;
}
    
    
    
    

void cliente_destroy(void *cliente_ptr) {
    Cliente *c = (Cliente *) cliente_ptr;
    if (c == NULL) return;
    free (c -> id);
    free (c -> nome);
    free ( c -> regiao);
    free (c -> data);
    free (c);
}


const char *get_cliente_id (const Cliente *c){
    if (c == NULL) return NULL;
    return c-> id;
}

const char *get_cliente_nome (const Cliente *c){
    if (c == NULL) return NULL;
    return c-> nome;
}

const char *get_cliente_data (const Cliente *c){
    if (c == NULL) return NULL;
    return c-> data;
}
const char *get_cliente_regiao (const Cliente *c){
    if (c == NULL) return NULL;
    return c-> regiao;
}



