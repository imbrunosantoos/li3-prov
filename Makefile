.PHONY: all clean 

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
OBJS = src/parser.o src/cliente.o src/deque.o src/interpretador.o src/produto.o src/linha_encomenda.o src/encomenda.o

# Opcoes de linkagem(Caso usarmos outras bibliotecas sem ser a padrao de C)
# pkg-config --libs glib-2.0 - indica a biblioteca da glib
LDFLAGS = `pkg-config --libs glib-2.0`

# Gera os executáveis programa-principal e programa-testes
all: programa-principal programa-testes


programa-principal: src/main.o $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

programa-testes: src/main_testes.o $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

src/main.o: src/main.c
src/main_testes.o: src/main_testes.c
src/parser.o: src/parser.c include/parser.h
src/cliente.o: src/cliente.c include/cliente.h
src/deque.o: src/deque.c include/deque.h
src/interpretador.o: src/interpretador.c include/interpretador.h include/parser.h
src/produto.o: src/produto.c include/produto.h
src/linha_encomenda.o: src/linha_encomenda.c include/linha_encomenda.h
src/encomenda.o: src/encomenda.c include/encomenda.h


# Limpa os executaveis
clean:
	rm -f programa-principal programa-testes src/*.o