# Makefile to compile the game

CC = gcc
CFLAGS = -Wall -lncurses -lpthread

# Lista de arquivos fonte
SRCS = main.c game.c ship.c rocket.c tower.c interface.c input.c

# Lista de arquivos objeto
OBJS = $(SRCS:.c=.o)

# Nome do executável
EXEC = game

# Regra padrão
all: $(EXEC)

# Regra para compilar o executável
$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

# Regra para compilar arquivos objeto
%.o: %.c
	$(CC) -c $< $(CFLAGS)

# Regra para limpar arquivos compilados
clean:
	rm -f $(OBJS) $(EXEC)

# Regra para reconstruir tudo
rebuild: clean all

.PHONY: all clean rebuild
