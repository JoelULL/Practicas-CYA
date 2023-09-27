# Universidad de La Laguna
# Escuela Superior de Ingenieria y Tecnologia
# Grado en Ingenieria Informatica
# Asignatura: Computabilidad y Algoritmia
# Curso: 2º
# Practica 11: Algoritmos voraces(greedy).Cambio de monedas
# Autor: Joel Aday Dorta Hernandez
# Correo: alu0100987584@ull.es
# Fecha: 17/12/2022
# Archivo Makefile: Permite la compilacion del programa y la generacion del
# archivo ejecutable necesario para su uso.


CXXFLAGS = -g -Wall
CXX = g++
OBJS = greedycoin.o main.o
BINARY = greedycoin

all: greedycoin

greedycoin: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  
