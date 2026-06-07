# Makefile for PROG-PROJ26-MBY-SSR-HMT
# Compilation: make
# Clean: make clean
# Run: make run

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
TARGET  = PROG-PROJ26-MBY-SSR-HMT
SRCDIR  = PROGRAMME
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/GestionAffichage.c $(SRCDIR)/GestionValeurlotoGagnante.c $(SRCDIR)/GestionFichiersLoto.c $(SRCDIR)/GestionSaisie.c
OBJS    = $(SOURCES:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

PROGRAMME/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
