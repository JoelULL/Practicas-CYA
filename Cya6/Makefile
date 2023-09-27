# Universidad de La Laguna
# Escuela Superior de Ingenieria y Tecnologia
# Grado en Ingenieria Informatica
# Asignatura: Computabilidad y Algoritmia
# Curso: 2º
# Practica 6: Automatas finitos
# Autor: Joel Aday Dorta Hernandez
# Correo: alu0100987584@ull.es
# Fecha: 08/11/2022
# Archivo Makefile: Permite la compilacion del programa y la generacion del
# archivo ejecutable necesario para su uso.


CXXFLAGS = -g -Wall
CXX = g++
OBJS = alphabet.o string.o state.o finiteautomata.o filecheckfunctions.o main.o
BINARY = p06_automata_simulator

all: p06_automata_simulator

p06_automata_simulator: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  
