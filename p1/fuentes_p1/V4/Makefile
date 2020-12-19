#*****************************************************************
# File:   Makefile
# Author: PSCD-Unizar
# Date:   octubre 2017
# Coms:   Ejecutar "make" para compilar (o "make -f Makefile")
#         Ejecutar "make clean" para limpiar (borrar lo que genere)
#*****************************************************************

CC=g++
CPPFLAGS=-std=c++11 -Wall
LDFLAGS=-pthread
FILE=practica_1_V4

##linkar
$(FILE): $(FILE).o Saludador.o
	$(CC) $(CPPFLAGS) $(LDFLAGS) Saludador.o $(FILE).cpp -o $(FILE)

##compilar
$(FILE).o: $(FILE).cpp Saludador.hpp
	$(CC) $(CPPFLAGS) $(FILE).cpp -c

Saludador.o: Saludador.cpp Saludador.hpp
	$(CC) $(CPPFLAGS) Saludador.cpp -c

##borrar
clean:
	rm -rf *o $(FILE)