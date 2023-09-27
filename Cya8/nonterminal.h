/**
 * @file nonterminal.h
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de cabecera de la clase nonterminal.h. 
 * En esta clase se declara la clase nonterminal que permitira crear
 * un objeto nonterminal el cual sera utilizado por la clase regulargrammar
 * para su correcto funcionamiento. Una gramatica esta compuesto por simbolos finales
 * y no terminales. Debido al uso de nombres autodescriptivos solo sera comentado aquello 
 * que sea necesaria su explicacion.
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "libraries.h"

#define notInitial "No es el simbolo inicial"
#define notAccept "No es de aceptacion"
#define isAccept "Es de aceptacion"
#define isInitial "Es de inicio"
#define spaceStr " "
#define arrow "->"

class NonTerminal {
  private:
  std::string name_;
  bool accept_; 
  bool initial_; 

  public:
  NonTerminal();
  NonTerminal(std::string name_readed);
  ~NonTerminal();

  std::string get_name();
  bool get_accept_non_terminal();
  bool get_initial_non_terminal();

  void set_name_non_terminal(std::string new_name);
  void set_accept_non_terminal(bool is_accept);
  void set_initial_non_terminal(bool is_initial);

  void ShowNonTerminalInfo();
  void showProductions();

  friend std::ostream& operator<<(std::ostream& os, NonTerminal& dt);
  bool operator<(NonTerminal const &right) const;
};