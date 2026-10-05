.PHONY: all clean 

# Compilador usado
CC = gcc

# Opcoes do compilador
# -Wall - Mostra os warnings
# -Iinclude - Diretoria dos cabeçalhos locais
CFLAGS = -Wall -Wextra -std=c11 -g -D_DEFAULT_SOURCE -Iinclude

# Reúne todos os executáveis numa só variável
OBJS = src/parser.o src/cliente.o src/deque.o src/interpretador.o

# Opcoes de linkagem(Caso usarmos outras bibliotecas sem ser a padrao de C)
LDFLAGS =

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


# Limpa os executaveis
clean:
	rm -f programa-principal programa-testes src/*.o