// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Inform ́atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 1: Simbolos, alfabetos y cadenas
// Autor: Nombre y Apellidos
// Correo: alu0100987584@ull.es
// Fecha: 04/10/2022
// Archivo string.cc: desarrollo de metodos de la case string.
// Contiene el desarrollo de los metodos de la clase string
// que incluyen la funcionalidad requerida


#include "string.h"
/**
  * Metodo que recibe un string como parametro y 
  * devuelve un string con el inverso de ese.
 */
std::string swapstrings (std::string mystring) {
  size_t size = mystring.size();
  for (size_t i = 0; i < size / 2; i++) {
    std::swap(mystring[i], mystring[size - i - 1]);
  }
  return mystring;
}

String::String(Alphabet linealphabet, std::string linestring) {
  for (size_t i = 0; i < linealphabet.size(); i++) {
    string_alphabet_.set_symbol(linealphabet.get_symbol(i));
  }
  
  string_ = linestring;
  index_ = 0;

  if (stringToVector()) {
    error = true;
  }
}

String::String(std::string linestring) {
  string_ = linestring;
  getAlphabetFromString();

  if (stringToVector()) {
    error = true;
  }
}

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

std::string String::inverse_string() {
  size_t stringlenght = string_.size();
  std::string reversed = string_;
  for (size_t i = 0; i < stringlenght / 2; i++) {
    std::swap(reversed[i], reversed[stringlenght - i - 1]);
  }
  return reversed;
}

void String::prefix_string() {

  std::string auxprefix = string_vector_[0];
  prefix_.push_back("&");
  prefix_.push_back(auxprefix);

  for (size_t i = 1; i < string_vector_.size(); i++) {
    auxprefix += string_vector_[i];
    prefix_.push_back(auxprefix);
  }
}

void String::sufix_string() {
  std::vector<std::string> reversed;
  for (int i = string_vector_.size() - 1; i >= 0; i--) {
    reversed.push_back(string_vector_[i]);
  }

  std::string auxsufix = reversed[0];
  sufix_.push_back("&");
  sufix_.push_back(auxsufix);

  for (size_t i = 1; i < reversed.size(); i++) {
    auxsufix += reversed[i];
    sufix_.push_back(swapstrings(auxsufix));
    
  }
}

void String::substrings() {
  std::string auxcadena = "";
  substringset_.insert("&");
  for (size_t i = 0; i < string_vector_.size();i++) {
    auxcadena = "";
    for(size_t j = i; j < string_vector_.size();j++) {
      auxcadena += string_vector_[j];
      substringset_.insert(auxcadena);
    }
  }
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

std::string String::showResults(int opcode) {

  if(error) {
    return error_msg;
  }
  switch (opcode)
  {
    case 1:{
      return std::to_string(string_lenght());
    }  
    case 2: {
      
      std::string inverseresult = inverse_string();
      return inverseresult;
    }

    case 3: {
      prefix_string();
      std::string prefixresult = "";
      std::string aux = "";
      for (size_t i = 0; i < prefix_.size(); i++) {
        aux = prefix_[i] + " ";
        prefixresult+=aux;
      }
      return prefixresult;
    }
      
    case 4: {
      sufix_string();
      std::string sufixresult = "";
      std::string aux = "";
      for (size_t i = 0; i < sufix_.size(); i++) {
        aux = sufix_[i] + " ";
        sufixresult += aux;
      }
      return sufixresult;
    }
      
    case 5: {
      substrings();
      std::string substringresult = "";
      std::string aux = "";
      for (auto it = substringset_.begin(); it!=substringset_.end();it++)
      {
        aux = *it + " ";
        substringresult += aux;
      }  
      return substringresult;
    }
  }
}