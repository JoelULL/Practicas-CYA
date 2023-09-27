// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 1: Simbolos, alfabetos y cadenas
// Autor: Joel Aday Dorta Hernandez
// Correo: alu0100987584@ull.es
// Fecha: 04/10/2022
// Archivo filefunctions.cc: desarrollo de metodos que se usaran en el main.
// contiene el desarrollo de los metodos para ciertas funcionalidades del main
// con el objetivo de obtener un main.cc mas limpio

#include "filefunctions.h"

bool haveSpaces(std::string mystring) {
  for (size_t i = 0; i < mystring.size(); i++) {
    if (mystring[i] == ' ') return true;
    }
  return false;
}

std::vector<std::string> separateStringAlphabet(std::vector<std::string> linetovector, std::string &finalstring) {
  std::vector<std::string> separatealphabet;

  for (size_t i = 0; i < linetovector.size() - 1; i++) {
    separatealphabet.push_back(linetovector[i]);
  }
  finalstring = linetovector[linetovector.size() - 1];

  return separatealphabet;
}

std::vector<std::string> stringToVector(std::string line) {
  std::string auxiliarstring;

  for (size_t i = 0; i < line.size(); i++) {
    auxiliarstring += line[i];
  }

  std::string symbol = "";
  std::vector<std::string> linealphabet;
  
  for (size_t i = 0; i < auxiliarstring.size(); i++) {
    if (auxiliarstring[i] != ' ') {
      symbol+= auxiliarstring[i];
    }
    else {
      linealphabet.push_back(symbol);
      symbol = "";
    }
    if (i + 1 == auxiliarstring.size())
      linealphabet.push_back(symbol);
    }
    return linealphabet;
}

