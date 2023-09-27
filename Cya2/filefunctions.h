// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 1: Simbolos, alfabetos y cadenas
// Autor: Joel Aday Dorta Hernandez
// Correo: alu0100987584@ull.es
// Fecha: 04/10/2022
// Archivo filefunctions.h: declaracion  losde metodos que se usaran en el main.
// contiene la declaracion de los metodos para ciertas funcionalidades del main.

#include "libraries.h"
#include "string.h"
#include "language.h"

#define openbracket "{"
#define closebracket "}"
#define charopenbracket '{'
#define charclosebracket '}'

#define epsilonstr "&"

std::vector<std::string> stringToVector(std::string line);
bool checkbrackets (std::vector<std::string> vectorizedline, std::vector<std::string> &alfabeto, std::vector<std::string> &cadenas);
bool checkforhiddenbrackets(std::vector<std::string> myvector);
void showmyvector(std::vector<std::string> myvector); //debug method
bool checkforepsilon(std::vector<std::string> &strings);
void filelanguage(std::string line, Language &linelanguage, bool &err);
