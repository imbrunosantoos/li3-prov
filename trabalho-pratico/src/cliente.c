#include "cliente.h"
#include <stdlib.h>
#include <string.h>



// a struct fica aqui, por isso o resto do programa só acede aos campos pelos getters

struct cliente {
    char *id;
    char *nome;
    char *regiao;
    char *data;
};

Cliente *cliente_novo (const char *id, const char *nome, const char *regiao, const char *data){
    Cliente *c = malloc (sizeof(struct cliente));
    if (c == NULL) return NULL;
     // strdup copia as strings, assim o cliente não depende da linha de onde vieram
    c -> id = strdup(id);
    c -> nome = strdup (nome);
    c -> regiao = strdup (regiao);
    c -> data = strdup (data);
   // se algum strdup falhou, liberta o que já tinha alocado para não deixar leaks
    // free(NULL) é seguro, por isso não é preciso ver qual falhou
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
    
    

// recebe void * para servir de destrutor da GHashTable do gestor (GDestroyNotify)
void cliente_destroy(void *cliente_ptr) {
    Cliente *c = (Cliente *) cliente_ptr;
    if (c == NULL) return;
    // primeiro os campos, só depois a struct que os guarda
    free (c -> id);
    free (c -> nome);
    free ( c -> regiao);
    free (c -> data);
    free (c);
}

// os getters devolvem const char * para ninguém alterar nem libertar a string do cliente
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



