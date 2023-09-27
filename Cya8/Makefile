# Universidad de La Laguna
# Escuela Superior de Ingenieria y Tecnologia
# Grado en Ingenieria Informatica
# Asignatura: Computabilidad y Algoritmia
# Curso: 2º
# Practica 7: Gramatica regular a partir de un DFA
# Autor: Joel Aday Dorta Hernandez
# Correo: alu0100987584@ull.es
# Fecha: 20/11/2022
# Archivo Makefile: Permite la compilacion del programa y la generacion del
# archivo ejecutable necesario para su uso.


CXXFLAGS = -g -Wall
CXX = g++
OBJS = alphabet.o filecheckfunctions.o nonterminal.o grammar.o main.o
BINARY = grammar2cnf

all: grammar2cnf

grammar2cnf: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  
