.PHONY: all clean 

# Compilador usado
CC = gcc

# Opcoes do compilador
# -Wall - Mostra os warnings
# -Iinclude - Diretoria dos cabeçalhos locais
CFLAGS = -Wall -Iinclude

# Opcoes de linkagem(Caso usarmos outras bibliotecas sem ser a padrao de C)
LDFLAGS =

# Gera o executável program
all: program

program: src/main.o src/deque.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

src/main.o: src/main.c
src/deque.o: src/deque.c include/deque.h


# Limpa os executaveis
clean:
	rm -f program src/*.o
