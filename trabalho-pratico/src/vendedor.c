#include "vendedor.h"
#include <stdlib.h>
#include <string.h>


#define TAM_BUFFER 1024
// a struct fica aqui, por isso o resto do programa só acede aos campos pelos getters
struct vendedor {
    char *id;
    char *nome;
    char *categoria;
    char *data;
};

Vendedor *vendedor_novo(const char *id, const char *nome, const char *categoria, const char *data) {
    Vendedor *v = malloc (sizeof(struct vendedor));
    if (v == NULL) return NULL;
    // strdup copia as strings, assim o vendedor não depende da linha de onde vieram
    v -> id = strdup(id);
    v -> nome = strdup (nome);
    v -> categoria = strdup (categoria);
    v -> data = strdup (data);
     // se algum strdup falhou, liberta o que já tinha alocado para não deixar leaks
    // free(NULL) é seguro, por isso não é preciso ver qual falhou
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
// recebe void * para servir de destrutor da GHashTable do gestor (GDestroyNotify)
void vendedor_destroy(void *vendedor_ptr) {
    Vendedor *v = (Vendedor *)vendedor_ptr;
    if (v == NULL) return;
    // primeiro os campos, só depois a struct que os guarda
    free (v -> id);
    free (v -> nome);
    free ( v -> categoria);
    free (v -> data);
    free (v);
}

// os getters devolvem const char * para ninguém alterar nem libertar a string do vendedor
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



