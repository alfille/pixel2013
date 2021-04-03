CC = gcc
OBJ = p2013dim

%.o: %.c
	$(cc) -c -o $@ $<



all: 
