#ifndef CLIENTE_H
#define CLIENTE_H


typedef struct cliente Cliente;

Cliente *cliente_novo(const char *id, const char *nome, const char *regiao, const char *data);
void cliente_destroy(void *cliente_ptr);

const char *get_cliente_id(const Cliente *c);
const char *get_cliente_nome(const Cliente *c);
const char *get_cliente_regiao(const Cliente *c);
const char *get_cliente_data(const Cliente *c);


void processar_clientes (const char *caminho_entrada, const char *caminho_erros ); 


#endif
