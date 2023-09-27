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

bool checkforhiddenbrackets(std::vector<std::string> myvector) {
  for(size_t i = 0; i < myvector.size(); i++) {
    for(size_t j = 0; j < myvector[i].size(); j++) {
      if(myvector[i][j] == charopenbracket || myvector[i][j] == charclosebracket) {
        std::cout << "\nSe ha detectado un llave incorrecta, las llaves no pueden formar parte del alfabeto o las cadenas";
        return false;
      }
    }
  }
  return true;
}


bool checkbrackets (std::vector<std::string> vectorizedline, std::vector<std::string> &alfabeto, std::vector<std::string> &cadenas) {

  size_t vsize = vectorizedline.size();
  size_t index = 0;

  // caso1: comprobar el primero y el ultimo
  if (vectorizedline[0] != openbracket || vectorizedline[vsize - 1] != closebracket)
    return false;
  //primera mitad
  for (size_t i = 1; i < vsize; i++) {
    if (vectorizedline[i] == openbracket)
      return false;
    if (vectorizedline[i] == closebracket && vectorizedline[i + 1] == openbracket) {
      index = i + 2;
        break;
    }
    //aqui iria el push al vector del alfabeto: alfabeto.push_back(vectorizedline[i]);
    alfabeto.push_back(vectorizedline[i]);
  }

  if(!checkforhiddenbrackets(alfabeto))
    return false;

  //segunda mitad del vector
  for (size_t i = index; i < vsize - 1; i++) {
    if (vectorizedline[i] == openbracket || vectorizedline[i] == closebracket)
      return false;

    //aqui iria el push a las cadenas cadenas.pushback(vectorizedline[i]);
    cadenas.push_back(vectorizedline[i]);
  }

  if(!checkforhiddenbrackets(cadenas))
    return false;

  return true;
}


std::vector<std::string> stringToVector(std::string line) {
  std::string symbol = "";
  std::vector<std::string> linealphabet;

  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] != ' ') {
      symbol+= line[i];
    }
    else {
      linealphabet.push_back(symbol);
      symbol = "";
    }
    if (i + 1 == line.size())
      linealphabet.push_back(symbol);
    }
    return linealphabet;
}

void showmyvector(std::vector<std::string> myvector) {
  for (size_t i = 0; i < myvector.size(); i++) {
    std::cout << myvector [i] << " ";
  }
}


bool checkforepsilon(std::vector<std::string> &strings) {
  std::vector<std::string> checked;
  bool epsilondetected = false;

  for (size_t i = 0; i < strings.size(); i++) {
    if (strings[i] != epsilonstr)
      checked.push_back(strings[i]);
    else
      epsilondetected = true;
  }
  strings = checked;

  return epsilondetected;
}


void filelanguage(std::string line, Language &linelanguage, bool &err) {
  std::string linea = line;
  std::vector<std::string> lineavector;
  std::vector<std::string> alfabeto;
  std::vector<std::string> cadenas;
  bool errordetected = false;
  lineavector = stringToVector(linea);

  if(checkbrackets(lineavector, alfabeto, cadenas)) {
    Alphabet linealphabet(alfabeto);
    if (linealphabet.epsilonDetection()) {
      std::cout << "epsilon no puede formar parte del alfabeto";
    }
   
    if (checkforepsilon(cadenas)) {
      linelanguage.languageHaveEpsilon();
    }

    for (size_t i = 0; i < cadenas.size(); i++) {
      String tolanguage(linealphabet, cadenas[i]);
      if(tolanguage.checkError()) {
        std::cout << "Hay una cadena que no pertecene al lenguaje: ";
        std::cout << tolanguage.get_linestring() << "\n";
        errordetected = true;
        err = errordetected;
        break;
      }
      if(!errordetected)
        linelanguage.set_string(tolanguage);
    }
    //
    if(!errordetected) {
      linelanguage.set_language_alphabet(linealphabet);
    }
    else {
      err = errordetected;
    }
  }
  else {
    err = errordetected;
  }
  
}
