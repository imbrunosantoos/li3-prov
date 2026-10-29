.PHONY: all clean test

# Compilador usado
CC = gcc

# Opcoes do compilador
# -Wall -Wextra - Mostra os warnings
# -Iinclude - Diretoria dos cabeçalhos locais
# -std=c11  - usa a norma C11
# -g - faz com que o valgrind mostre linhas de codigo ao invés de endereço
# -D_DEFAULT_SOURCE -  torna visíveis funções como strdup, strsep e getline
# pkg-config --cflags glib-2.0 - acrescenta as diretorias dos cabeçalhos da glib
CFLAGS = -Wall -Wextra -std=c11 -g -D_DEFAULT_SOURCE -Iinclude `pkg-config --cflags glib-2.0`

# Reúne todos os executáveis numa só variável
OBJS = src/validadores.o src/vendedor.o src/parser.o src/cliente.o src/deque.o src/interpretador.o src/produto.o src/linha_encomenda.o src/encomenda.o src/gestor_produtos.o src/queries.o src/gestor_encomendas.o src/utils.o src/gestor_clientes.o src/gestor_vendedores.o src/carregamento.o src/gestor_linhas_encomenda.o src/dados.o src/output.o src/comparador.o src/gestor_estatisticas.o

# Opcoes de linkagem(Caso usarmos outras bibliotecas sem ser a padrao de C)
# pkg-config --libs glib-2.0 - indica a biblioteca da glib
LDFLAGS = `pkg-config --libs glib-2.0`

# Gera os executáveis programa-principal e programa-testes
all: programa-principal programa-testes


programa-principal: src/main.o $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

programa-testes: src/main_testes.o $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


src/main_testes.o: src/main_testes.c include/comparador.h include/interpretador.h include/dados.h include/gestor_produtos.h include/produto.h include/gestor_encomendas.h include/encomenda.h include/gestor_clientes.h include/cliente.h include/gestor_vendedores.h include/vendedor.h include/gestor_linhas_encomenda.h include/linha_encomenda.h include/carregamento.h include/dados.h
src/main.o: src/main.c include/interpretador.h include/dados.h include/gestor_produtos.h include/produto.h include/gestor_encomendas.h include/encomenda.h include/gestor_clientes.h include/cliente.h include/gestor_vendedores.h include/vendedor.h include/gestor_linhas_encomenda.h include/linha_encomenda.h include/carregamento.h include/dados.h
src/validadores.o: src/validadores.c include/validadores.h
src/vendedor.o: src/vendedor.c include/vendedor.h
src/parser.o: src/parser.c include/parser.h
src/cliente.o: src/cliente.c include/cliente.h
src/deque.o: src/deque.c include/deque.h
src/interpretador.o: src/interpretador.c include/parser.h include/interpretador.h include/dados.h include/gestor_produtos.h include/produto.h include/gestor_encomendas.h include/encomenda.h include/gestor_clientes.h include/cliente.h include/gestor_vendedores.h include/vendedor.h include/gestor_linhas_encomenda.h include/linha_encomenda.h include/queries.h include/output.h
src/produto.o: src/produto.c include/produto.h
src/linha_encomenda.o: src/linha_encomenda.c include/linha_encomenda.h
src/encomenda.o: src/encomenda.c include/encomenda.h
src/gestor_produtos.o: src/gestor_produtos.c include/gestor_produtos.h include/produto.h
src/queries.o: src/queries.c include/queries.h include/dados.h include/gestor_produtos.h include/produto.h include/gestor_encomendas.h include/encomenda.h include/gestor_clientes.h include/cliente.h include/gestor_vendedores.h include/vendedor.h include/gestor_linhas_encomenda.h include/linha_encomenda.h include/output.h
src/gestor_clientes.o: src/gestor_clientes.c include/gestor_clientes.h include/cliente.h
src/gestor_vendedores.o: src/gestor_vendedores.c include/gestor_vendedores.h include/vendedor.h
src/output.o: src/output.c include/output.h
src/carregamento.o: src/carregamento.c include/carregamento.h include/gestor_clientes.h include/cliente.h include/gestor_vendedores.h include/vendedor.h include/parser.h include/validadores.h include/produto.h include/encomenda.h 
src/utils.o: src/utils.c include/utils.h
src/gestor_encomendas.o: src/gestor_encomendas.c include/gestor_encomendas.h include/encomenda.h
src/comparador.o: src/comparador.c include/comparador.h
src/dados.o: src/dados.c include/dados.h include/gestor_produtos.h include/produto.h include/gestor_encomendas.h include/encomenda.h include/gestor_clientes.h include/cliente.h include/gestor_vendedores.h include/vendedor.h include/gestor_linhas_encomenda.h include/linha_encomenda.h
src/gestor_linhas_encomenda.o : src/gestor_linhas_encomenda.c include/gestor_linhas_encomenda.h include/linha_encomenda.h
src/gestor_estatisticas.o : src/gestor_estatisticas.c include/gestor_estatisticas.h include/linha_encomenda.h include/encomenda.h


#testes unitarios - compila testes.c com os modulos q ele testa
testes/testes: testes/testes.c src/gestor_produtos.o src/produto.o src/gestor_encomendas.o src/encomenda.o src/gestor_linhas_encomenda.o src/linha_encomenda.o src/gestor_estatisticas.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# Corre os testes unitários dos gestores
test: testes/testes
	./testes/testes
# Limpa os executaveis
clean:
	rm -f programa-principal programa-testes testes/testes src/*.o