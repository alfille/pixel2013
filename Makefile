CC = gcc

p2013dim: p2013dim.c
	$(CC) -o $@ $^
	chmod +x $@


all: p2013dim

install: all
	install -m 6711 p2013dim /usr/bin
	
