/**
 * @file filecheckfunctions.h
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de cabecera de ciertas funciones que seran de
 * utilidad para el tratamiento de archivos tanto .txt como .fa
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "libraries.h"

bool checkNumberOfStates(std::string line);
std::set<std::string> getTheAlphabet(std::string line);
std::vector<std::string> separateStateDeclaration(std::string line);
bool checkExtension(std::string fullString, std::string ending);