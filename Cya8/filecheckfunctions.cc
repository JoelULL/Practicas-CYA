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
/**
 * @brief Detecta si la linea que se ha leido se trata de un
 * numero
 * @param line linea leida en el fichero
 * @return true ha leido un numero
 * @return false ha leido otra cosa
 */
bool checkNumber(std::string line) {
  std::regex detectNumber("\\d+");
  return std::regex_match(line, detectNumber);
}
/**
 * @brief Detecta la extension de los archivos que el usuario 
 * escribe por linea de comandos.
 * 
 * @param fullString nombre del archivo
 * @param ending extension a reconocer
 * @return true extension correcta
 * @return false extension incorrecta
 */
bool checkExtension(std::string fullString, std::string ending) {
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
  } 
  return false;
}