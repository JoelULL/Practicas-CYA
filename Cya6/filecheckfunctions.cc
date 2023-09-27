/**
 * @file filecheckfunctions.cc
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de desarrollo de las funciones que seran de
 * utilidad para el tratamiento de archivos tanto .txt como .fa
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "filecheckfunctions.h"

bool checkNumberOfStates(std::string line) {
  std::regex detectSpaces("\\d+");
  return std::regex_match(line, detectSpaces);
}
std::set<std::string> getTheAlphabet(std::string line) {
  std::set<std::string> to_return;
  std::string symbol = "";
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] != ' ') {
      symbol += line[i];
    }
    else {
      to_return.insert(symbol);
      symbol = "";
    }
    if (i + 1 == line.size())
      to_return.insert(symbol);
    }   
  return to_return;
}
std::vector<std::string> separateStateDeclaration(std::string line) {
  std::vector<std::string> to_return;
  std::string read;
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] != ' ') {
      read += line[i];
    }
    else {
    to_return.push_back(read);
    read = "";
    }
    if (i + 1 == line.size()) {
      to_return.push_back(read);
    }
  }
  return to_return;
}

bool checkExtension(std::string fullString, std::string ending) {
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
  } 
  return false;
}