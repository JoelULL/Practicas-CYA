/**
 * @file Alphabet.h
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de cabecera de la clase alphabet.h. Se declaran los metodos y
 * atributos de la clase alphabet. Todo automata finito necesita un alfabeto de entrada.
 * Debido al uso de nombres autodescriptivos solo sera comentado aquello que sea
 * necesaria su explicacion.
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "libraries.h"

#define epsilon '&'

class Alphabet {
  private:
  std::vector<std::string> alphabet_;
  bool epsilondetected_ = false; /*La cadena vacia no puede formar parte del alfabeto*/

  public:
  Alphabet(std::vector<std::string> input_alphabet);
  Alphabet(std::set<std::string> setalphabet);
  Alphabet();
  ~Alphabet();
  bool epsilonDetection();
  void set_symbol(std::string symbol);
  std::string get_symbol(int index);
  std::set<std::string> alphabetset();
  Alphabet unionAlphabet(Alphabet tounion);
  size_t size();
  bool operator==(Alphabet &tocompare);
  void showAlphabet();
};
