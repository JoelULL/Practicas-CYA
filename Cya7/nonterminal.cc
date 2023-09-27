/**
 * @file nonterminal.cc
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de cabecera de la clase nonterminal.cc. 
 * En esta clase se desarrollan los metodos de la clase
 * nonterminal los cuales la dotaran de la funcionalidad necesaria para
 * generar un objeto nonterminal el cual sera utilizado por la clase regulargrammar
 * para su correcto funcionamiento. Una gramatica esta compuesto por simbolos finales
 * y no terminales. Debido al uso de nombres autodescriptivos solo sera comentado aquello 
 * que sea necesaria su explicacion.
 * @version 0.1
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "nonterminal.h"

NonTerminal::NonTerminal() {}
NonTerminal::NonTerminal(State dfa_state) {
  name_ = dfa_state.get_name();
  initial_ = dfa_state.get_initial_state();
  accept_ = dfa_state.get_accept_state();
}
NonTerminal::~NonTerminal() {}

std::string NonTerminal::get_name() {
  return name_;
}
bool NonTerminal::get_accept_non_terminal() {
  return accept_;
}
bool NonTerminal::get_initial_non_terminal() {
  return initial_;
}
std::set<ProductionRule> NonTerminal::get_production_rules() {
  return productions_;
}

void NonTerminal::set_name_non_terminal(std::string new_name) {
  name_ = new_name;
}

void NonTerminal::set_accept_non_terminal(bool is_accept) {
  accept_ = is_accept;
}

void NonTerminal::set_initial_non_terminal(bool is_initial) {
  initial_ = is_initial;
}

void NonTerminal::set_production_rules(std::set<ProductionRule> productions) {
  productions_ = productions;
}

void NonTerminal::set_production_rule(ProductionRule rule) {
  productions_.insert(rule);
}

void NonTerminal::ShowNonTerminalInfo() {
  std::cout << "Caracteristicas del simbolo no terminal: \n";
  std::cout << this;
  std::cout <<"\nTiene las siguientes producciones: \n";
  for (auto it = productions_.begin(); it != productions_.end(); it++) {
    ProductionRule toshow = *it;
    std::cout << toshow << "\n";
  }
}
void NonTerminal::showProductions() {
  for (auto it = productions_.begin(); it != productions_.end(); it++) {
    ProductionRule to_show = *it;
    std::cout << to_show << "\n";
  }
}

std::ostream& operator<<(std::ostream& os, NonTerminal& dt) {
  std::string initial;
  std::string accept;

  if (dt.get_initial_non_terminal()) {
    initial = isInitial;
  }
  else {
    initial = notInitial;
  }
  if (dt.get_accept_non_terminal()) {
    accept = isAccept;
  }
  else { 
    accept = notAccept;
  }
  os << dt.get_name() << spaceStr << initial << spaceStr << accept;
  return os;
}

bool NonTerminal::operator<(NonTerminal const &right) const {}




