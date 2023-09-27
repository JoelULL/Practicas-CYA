// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 1: Simbolos, alfabetos y cadenas
// Autor: Joel Aday Dorta Hernandez
// Correo: alu0100987584@ull.es
// Fecha: 04/10/2022
// Archivo filefunctions.h: declaracion  losde metodos que se usaran en el main.
// contiene la declaracion de los metodos para ciertas funcionalidades del main.

#include "libraries.h"
#include "string.h"
bool haveSpaces(std::string mystring);
std::vector<std::string> separateStringAlphabet(std::vector<std::string> linetovector, std::string &finalstring);
std::vector<std::string> stringToVector(std::string line);