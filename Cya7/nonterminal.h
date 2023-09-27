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
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "libraries.h"
#include "state.h"

#define notInitial "No es el simbolo inicial"
#define notAccept "No es de aceptacion"
#define isAccept "Es de aceptacion"
#define isInitial "Es de inicio"
#define spaceStr " "
#define arrow "->"

struct ProductionRule;

class NonTerminal {
  private:
  std::string name_;
  bool accept_;
  bool initial_;
  std::set<ProductionRule> productions_;

  public:
  NonTerminal();
  NonTerminal(State dfa_state); /*Permite generar un no terminal a partir de un estado de un DFA*/
  ~NonTerminal();

  std::string get_name();
  bool get_accept_non_terminal();
  bool get_initial_non_terminal();
  std::set<ProductionRule> get_production_rules();

  void set_name_non_terminal(std::string new_name);
  void set_accept_non_terminal(bool is_accept);
  void set_initial_non_terminal(bool is_initial);
  void set_production_rules(std::set<ProductionRule> productions);
  void set_production_rule(ProductionRule rule);
  

  void ShowNonTerminalInfo();
  void showProductions();

  friend std::ostream& operator<<(std::ostream& os, NonTerminal& dt);
  bool operator<(NonTerminal const &right) const;
};

/**
 * @brief Desarrollo de la estructura ProductionRule.
 * Cada no terminal tiene una o varias producciones 
 * formadas por conjuntos de simbolos terminales y no 
 * terminales
 */
struct ProductionRule {
  NonTerminal actual_symbol;
  std::string terminal_symbol;
  NonTerminal next_symbol;
  
  friend std::ostream& operator<<(std::ostream& os, ProductionRule& dt) {
  os << dt.actual_symbol.get_name() << spaceStr << arrow<< spaceStr
    <<dt.terminal_symbol << dt.next_symbol.get_name();
  return os;
  }
  
};

inline bool operator<(const ProductionRule& left, const ProductionRule& right) {}
