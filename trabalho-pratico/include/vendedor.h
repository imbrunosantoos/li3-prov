#ifndef VENDEDOR_H
#define VENDEDOR_H


typedef struct vendedor Vendedor;

Vendedor *vendedor_novo (const char *id, const char *nome, const char *categoria, const char *data);
void vendedor_destroy(void *vendedor_ptr);

const char *get_vendedor_id(const Vendedor *c);
const char *get_vendedor_nome(const Vendedor *c);
const char *get_vendedor_categoria(const Vendedor *c);
const char *get_vendedor_data(const Vendedor *c);



#endif 