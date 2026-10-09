#ifndef VENDEDOR_H
#define VENDEDOR_H


typedef struct vendedor Vendedor;

Vendedor *criar_vendedor (const char *id, const char *nome, const char *categoria, const char *data);
void destruir_vendedor(void *vendedor_ptr);

const char *get_vendedor_id(const Vendedor *c);
const char *get_vendedor_nome(const Vendedor *c);
const char *get_vendedor_categoria(const Vendedor *c);
const char *get_vendedor_data(const Vendedor *c);




void processar_vendedores (const char *caminho_entrada, const char *caminho_erros);

#endif 