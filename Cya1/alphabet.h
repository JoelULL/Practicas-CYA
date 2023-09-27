// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 1: Simbolos, alfabetos y cadenas
// Autor: Joel Aday Dorta Hernandez
// Correo: alu0100987584@ull.es
// Fecha: 04/10/2022
// Archivo alphabet.h: declaracion de los metodos que se usaran en la clase alphabet.
// contiene la declaracion de los metodos que se desarrollaran en alphabet.cc

#include "libraries.h"

#define epsilon '&'

class Alphabet {
  private:
  std::vector<std::string> alphabet_; 
  public:
  Alphabet(std::vector<std::string> input_alphabet);
  Alphabet();
  ~Alphabet();
  bool epsilonDetection();
  void set_symbol(std::string symbol);
  std::string get_symbol(int index);
  size_t size();
};
