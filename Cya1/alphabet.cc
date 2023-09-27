// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 1: Simbolos, alfabetos y cadenas
// Autor: Joel Aday Dorta Hernandez
// Correo: alu0100987584@ull.es
// Fecha: 04/10/2022
// Archivo alphabet.cc: desarrollo de metodos que se usaran en la clase alphabet.
// contiene el desarrollo de los metodos que permitiran crear un objeto que represente
// el alfabeto de las lineas del archivo de entrada

#include "alphabet.h"

Alphabet::Alphabet(std::vector<std::string> input_alphabet) {
  alphabet_ = input_alphabet;
}
Alphabet::Alphabet(){}

Alphabet::~Alphabet(){}

bool Alphabet::epsilonDetection() {
  for (size_t i = 0; i < alphabet_.size(); i++) {
    for (size_t j = 0; j < alphabet_[i].size(); j++) {
      if ( alphabet_[i][j] == epsilon)
        return true;
    }
  }
  return false;
}

void Alphabet::set_symbol(std::string symbol) {
  alphabet_.push_back(symbol);
}

std::string Alphabet::get_symbol(int index) {
  return alphabet_[index];
}

size_t Alphabet::size() {
  return alphabet_.size();
}
