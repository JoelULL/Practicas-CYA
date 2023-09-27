// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 3: Calculadora de lenguajes formales
// Autor: Joel Aday Dorta Hernandez
// Correo: alu0100987584@ull.es
// Fecha: 18/10/2022
// Archivo alphabet.cc: desarrollo de metodos que se usaran en la clase alphabet.
// contiene el desarrollo de los metodos que permitiran crear un objeto que represente
// el alfabeto de las lineas del archivo de entrada

#include "alphabet.h"

Alphabet::Alphabet(std::vector<std::string> input_alphabet) {
  alphabet_ = input_alphabet;
}
Alphabet::Alphabet(){}

Alphabet::Alphabet(std::set<std::string> setalphabet) {
  for (auto it = setalphabet.begin(); it!= setalphabet.end();it++) {
    alphabet_.push_back(*it);
  }
}

Alphabet::~Alphabet(){}

bool Alphabet::epsilonDetection() {
  for (size_t i = 0; i < alphabet_.size(); i++) {
    for (size_t j = 0; j < alphabet_[i].size(); j++) {
      if ( alphabet_[i][j] == epsilon) {
        return true;
      }
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


std::set<std::string> Alphabet::alphabetset() {
  std::set<std::string> toset;
  for (size_t i = 0; i < alphabet_.size(); i++){
    toset.insert(alphabet_[i]);
  }

  return toset;
}

Alphabet Alphabet::unionAlphabet(Alphabet tounion) {
std::set<std::string> alphabetright = alphabetset();
std::set<std::string> alphabetleft = tounion.alphabetset();
std::set<std::string> resultset;
std::vector<std::string> content;

std::set_union(alphabetright.begin(), alphabetright.end(), alphabetleft.begin(), alphabetleft.end(),
    std::inserter(resultset, resultset.begin()));

  for (auto it = resultset.begin(); it!=resultset.end(); it++) {
    content.push_back(*it);
  }
  Alphabet result(content);

  return result;
}

void Alphabet::showAlphabet() {
  
  for (size_t i = 0; i < alphabet_.size(); i++) {
    std::cout << alphabet_[i] << " ";
  }
  std::cout << "\n";
}

bool Alphabet::operator==(Alphabet &tocompare) {
  std::set<std::string> alphset = alphabetset();
  return alphset == tocompare.alphabetset();
}
