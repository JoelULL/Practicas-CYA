# Universidad de La Laguna
# Escuela Superior de Ingenieria y Tecnologia
# Grado en Ingenieria Informatica
# Asignatura: Computabilidad y Algoritmia
# Curso: 2º
# Practica 4: Expresiones regulares
# Autor: Joel Aday Dorta Hernandez
# Correo: alu0100987584@ull.es
# Fecha: 22/10/2022
# Archivo Makefile: Permite la compilacion del programa y la generacion del
# archivo ejecutable necesario para su uso.


CXXFLAGS = -g -Wall
CXX = g++
OBJS = codeanalyzer.o main.o
BINARY = p04_code_analyzer

all: p04_code_analyzer

p04_code_analyzer: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  
