/**
 * @file userinputcontrol.cc
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo userinputcontrol.cc. Con el fin de ordenar mejor
 * las funcionalidades del programa, se ha creado este archivo para 
 * dotarlo de metodos encargados de comprobar la cantidad en euros
 * que el usuario ha introducido, asi como dejarla en el formato adecuado
 * para que pueda ser procesada por la clase greedycoin.
 * @version 0.1
 * @date 2022-12-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "libraries.h"

bool checkUserValue(std::string coin_value) {
  std::regex test("(\\d)+(,(\\d)+)?€");
  if (std::regex_match(coin_value, test)) {
    return true;
  }
  return false;
}
void modifiyUserValue(std::string &user_value) {  
  user_value = std::regex_replace(user_value, std::regex(","), "");
  user_value = std::regex_replace(user_value, std::regex("€"), "");
}