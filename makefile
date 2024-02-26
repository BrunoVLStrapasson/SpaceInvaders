# Makefile do trabalho A4 prog2

CC = gcc
CFLAGS = -Wall -g
LIBS = -lallegro -lallegro_main -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf

SRC = main.c elementos.c entradas.c muros.c tiros.c
OBJ = $(SRC:.c=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

purge: clean
	rm -f $(EXEC)
