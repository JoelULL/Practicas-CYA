// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Inform ́atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 3: Calculadora de lenguajes formales
// Autor: Nombre y Apellidos
// Correo: alu0100987584@ull.es
// Fecha: 18/10/2022
// Archivo string.cc: desarrollo de metodos de la case string.
// Contiene el desarrollo de los metodos de la clase string
// que incluyen la funcionalidad requerida


#include "string.h"

String::String(Alphabet linealphabet, std::string linestring) {
  for (size_t i = 0; i < linealphabet.size(); i++) {
    string_alphabet_.set_symbol(linealphabet.get_symbol(i));
  }
  
  string_ = linestring;
  index_ = 0;

  if (stringToVector()) {
    error_ = true;
  }
}

String::String(std::string linestring) {
  string_ = linestring;
  getAlphabetFromString();

  if (stringToVector()) {
    error_ = true;
  }
}
String::String(){}
String::~String(){}

/**
 * Comprueba en caso de que un simbolo del alfabeto
 * tenga tamaño mayor que 1 que se encuentre en su totalidad
 * en la cadena y en el orden establecido
 */
bool String::checkLongSymbol(size_t index, std::string symbol) {
  index++;
  size_t counter = 1;
  for (size_t i = 1; i < symbol.size(); i++) {
    if (string_[index] == symbol[i]) {
      index++;
      counter++;
    }
  }
  if (counter == symbol.size()) {
    index_ = index;
    return true;
  }
  else {
    return false;
  }
}
/**
 * Metodo que se encargara de que en caso de que todos
 * los simbolos del cadena pertenezcan al alfabeto, introduce
 * simbolo por simbolo de la cadena a un vector.
 */
bool String::stringToVector() {
  std::string auxsymbol = "";
  for (size_t i = 0; i < string_.size(); i++) {
    for (size_t j = 0; j < string_alphabet_.size();j++){
      auxsymbol = string_alphabet_.get_symbol(j);
      if (string_[i] == auxsymbol[0]) {
        if (auxsymbol.size() > 1) {
          if (checkLongSymbol(i, auxsymbol)) {
            string_vector_.push_back(auxsymbol);
            i = index_;
          }
          else {
            return true;
          }
        }
        else {
          string_vector_.push_back(auxsymbol);
        }
      }
    }
  }
  size_t comparesizes = 0;
  for (size_t i = 0; i < string_vector_.size();i++) {
    comparesizes+= string_vector_[i].size();
  }
  if (comparesizes != string_.size()) {
    std::cout << error_msg <<"\n";
    return true;
  }
     
  return false;
}

int String::string_lenght() {
    return string_vector_.size();
}

/**
 * En caso de que el alfabeto tenga un tamaño 0 
 * porque no se define en la linea de texto, se
 * calcula automaticamente con este metodo
 */
void String::getAlphabetFromString() {
  std::set<std::string> alphabet;
  std::string aux = "";
  for (size_t i = 0; i < string_.size();i++) {
    aux = string_[i];
    alphabet.insert(aux);
  }
  for (auto it = alphabet.begin(); it!=alphabet.end();it++)
  {
    string_alphabet_.set_symbol(*it);
  }
}


bool String::checkError() {
  return error_;
}

std::string String::get_linestring() {
  return string_;
}

std::vector<std::string> String::get_string_vector() {

  std::vector<std::string> returnedvector = string_vector_;

  return returnedvector;
}

void String::showVectorString() {
  for (size_t i = 0; i < string_vector_.size(); i++) {
    std::cout << string_vector_[i];
  }
}

bool String::operator<(String const &right) const {
 return string_vector_ < right.string_vector_;
}

bool String::operator==(String &tocompare) {
  return string_vector_ == tocompare.get_string_vector();
}


Alphabet String::get_alphabet() const {
  return string_alphabet_;
}

void String::set_linestring(std::vector<std::string> stringset) {
  std::string toset = "";

  for (size_t i = 0; i < stringset.size(); i++) {
    toset += stringset[i];
  }
  string_ = toset;
}
void String::set_string_vector(std::vector<std::string> stringset) {
  string_vector_ = stringset;
}

std::vector<std::string> String::get_string_vector() const {
  return string_vector_;
}

std::string String::get_linestring() const {
  return string_;
}


String String::operator+(String &left) {
  Alphabet otheralphabet = left.get_alphabet();
  Alphabet myalph = string_alphabet_.unionAlphabet(otheralphabet);

  std::string resultstring = string_ + left.get_linestring();

  return String(myalph, resultstring);
}

String String::inversed() {
  std::string toinverse = string_;
  size_t stringsize = toinverse.size();
  for (size_t i = 0; i < stringsize / 2; i++)
    std::swap(toinverse[i], toinverse[stringsize - i - 1]);
      
  Alphabet inversealphabet(string_alphabet_);
  String result(inversealphabet,toinverse);

  return result;
}