// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 3: Calculadora de lenguajes formales
// Autor: Joel Aday Dorta Hernandez
// Correo: alu0100987584@ull.es
// Fecha: 18/10/2022
// Archivo filefunctions.h: declaracion  losde metodos que se usaran en el main.
// contiene la declaracion de los metodos para ciertas funcionalidades del main.
#pragma once
#include "libraries.h"
#include "string.h"
#include "language.h"


#define openbracket '{'
#define closebracket '}'
#define equal '='
#define coma ','
#define space ' '
#define epsilon '&'

#define epsilonstr "&"


bool checkForbiddenSymbols(std::vector<std::string> myvector); 
bool checkforepsilon(std::vector<std::string> &strings); 
bool checkIfIsLanguage(std::vector<std::string> line);
bool checkBetweenBrackets(std::vector<std::string> &line); 
bool checkForComas(std::vector<std::string> &tocheck); 
std::vector<std::string> serateReadLine(std::string line); 
std::set<String> createSetString(std::vector<std::string> linestrings);
bool multipleStringLanguage(std::vector<std::string> line, std::string name, Language &toset);
bool unaryStringLanguage(std::string readstring, std::string name, Language &toset);
bool checkforBracketsPosition(std::string tocheck);
void eliminateBrackets(std::string &stringread);
//debug method
void showmyvector(std::vector<std::string> myvector); 