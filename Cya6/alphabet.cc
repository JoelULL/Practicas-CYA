/**
 * @file Alphabet.cc
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de desarrollo de la clase alphabet.h. Se desarrollanlos metodos 
 * de la clase alphabet. Todo automata finito necesita un alfabeto de entrada.
 * Debido al uso de nombres autodescriptivos solo sera comentado aquello que sea
 * necesaria su explicacion.
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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
