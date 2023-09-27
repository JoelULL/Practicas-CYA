/**
 * @file regulargrammar.cc
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de desarrollo de los metodos de la clase regulargrammar. 
 * En este archivo se dota de funcionalidad a la clase nombrada con el fin
 * de poder crear un objeto que devuelva en un archivo .gra las caracteristicas
 * de la gramatica obtenida mediante un DFA dado. Debido al uso de nombres 
 * autodescriptivos solo sera comentado aquello que sea necesaria su explicacion.
 * @version 0.1
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "regulargrammar.h"

RegularGrammar::RegularGrammar() {}
RegularGrammar::~RegularGrammar() {}

RegularGrammar::RegularGrammar(FiniteAutomata user_dfa) {
  grammar_alphabet_ = user_dfa.automataAlphabet();
  getNonTerminalsFromStatesDfa(user_dfa.get_states_with_transition());
  associateProductionRuleToNonTerminals(user_dfa.get_states_with_transition());
  error = user_dfa.get_error();
}
/**
 * @brief Genera los no terminales a partir de los estados de un dfa dado
 * 
 * @param dfa_states estados del dfa
 */
void RegularGrammar::getNonTerminalsFromStatesDfa(std::set<State> dfa_states) {
  for (auto it = dfa_states.begin(); it != dfa_states.end(); it++) {
    State readed = *it;
    NonTerminal to_insert(readed);
    non_terminal_symbols_.insert(to_insert);
    if (to_insert.get_initial_non_terminal()) {
      initial_symbol_ = to_insert;
    }
  }
}
/**
 * @brief Obtiene para cada uno de los no terminales las producciones pertinentes
 * a partir de los estados del dfa
 * 
 * @param reference no terminal actual
 * @param state_transitions transiciones del estado asociado al no terminal
 * @return std::set<ProductionRule> devuelve un set que contiene las producciones de dicho terminal
 */
std::set<ProductionRule> RegularGrammar::getProductionRulesFromDfa(NonTerminal reference, std::set<Transition> state_transitions) {
  std::set<ProductionRule> to_return;
  ProductionRule to_insert;
  to_insert.actual_symbol = reference;

  for (auto it = state_transitions.begin(); it != state_transitions.end(); it++) {
    Transition to_check = *it;
    to_insert.terminal_symbol = to_check.symbol_;
    for (auto it1 = non_terminal_symbols_.begin(); it1 != non_terminal_symbols_.end(); it1++) {
      NonTerminal to_find = *it1;
      if (to_find.get_name() == to_check.next_state_.get_name()) {
        to_insert.next_symbol = to_find;
        break;
      }
    }
    to_return.insert(to_insert);
  }
  if (reference.get_accept_non_terminal()) {
    ProductionRule accept;
    accept.actual_symbol = reference;
    accept.terminal_symbol = epsilon_str;
    to_return.insert(accept);
  }
  return to_return;
}
/**
 * @brief Metodo que en funcion de las transiciones de los estados del dfa
 * obtiene las reglas de produccion para la gramatica
 * 
 * @param dfa_states estados del dfa
 */
void RegularGrammar::associateProductionRuleToNonTerminals(std::set<State> dfa_states) {
  for (auto it = dfa_states.begin(); it != dfa_states.end(); it++) {
    State to_get = *it;
    NonTerminal to_find;
    for (auto it1 = non_terminal_symbols_.begin(); it1 != non_terminal_symbols_.end(); it1++) {
      to_find = *it1;
      if (to_find.get_name()==to_get.get_name()) {
        to_find.set_production_rules(getProductionRulesFromDfa(to_find, to_get.get_transitions()));
        non_terminal_with_rules_.insert(to_find);
        break;
      }
    } 
  }
}
/**
 * @brief Muestra el listado de los no terminales junto con
 * su informacion
 */
void RegularGrammar::showMyNonTerminals() {
  for (auto it = non_terminal_symbols_.begin(); it != non_terminal_symbols_.end(); it++) {
    NonTerminal toshow = *it;
    std::cout << toshow << "\n";
  }
}
/**
 * @brief Muestra las reglas de produccion para cada
 * no terminal
 */
void RegularGrammar::showProductionRules() {
    
  for (auto it = non_terminal_with_rules_.begin(); it != non_terminal_with_rules_.end(); it++) {
    NonTerminal check_productions = *it;
    check_productions.showProductions();
    std::cout << "\n";
  }
}
/**
 * @brief Metodo principal de la clase, es el encargado de
 * volcar la informacion de la gramatica generada en un 
 * fichero de salida dado por el usuario con extension
 * .gra
 * @param file_name 
 */
void RegularGrammar::grammarInfoTofile(std::string file_name) {
  std::ofstream grammar_file(file_name);
  grammar_file << "Numero de simbolos del alfabeto: " << grammar_alphabet_.size() << "\n";
  grammar_file << "Los simbolos del alfabeto son: \n";
  std::set<std::string> symbols = grammar_alphabet_.alphabetset();
  for (auto it = symbols.begin(); it != symbols.end(); it++) {
    std::string symbol = *it;
    grammar_file << symbol << "\n";
  }
  grammar_file << "Numero de simbolos no terminales: " << non_terminal_with_rules_.size() << "\n";
  grammar_file << "Los simbolos no terminales son: \n";
  for (auto it = non_terminal_with_rules_.begin(); it != non_terminal_with_rules_.end(); it++) {
    NonTerminal to_show = *it;
    grammar_file << to_show.get_name() << "\n";
  }
  grammar_file << "El simbolo de arranque de la gramatica es: "<< initial_symbol_.get_name() << "\n";
  howManyProductions();
  grammar_file << "Numero total de producciones: "<< amount_of_productions_ << "\n";
  grammar_file << "Las producciones de la gramatica son: \n";
  for (auto it = non_terminal_with_rules_.begin(); it != non_terminal_with_rules_.end(); it++) {
    NonTerminal to_show = *it;
    std::set<ProductionRule> non_terminal_productions = to_show.get_production_rules();
    for (auto it1 = non_terminal_productions.begin(); it1 != non_terminal_productions.end(); it1++) {
      ProductionRule to_file = *it1;
      grammar_file << to_file << "\n";
    }
  }
  grammar_file.close();
}
/**
 * @brief Obtiene el numero total de producciones de la gramatica
 * este dato se pide que este en el archivo de salida con la
 * informacion de la gramatica
 */
void RegularGrammar::howManyProductions() {
  amount_of_productions_ = 0;
  for (auto it = non_terminal_with_rules_.begin(); it != non_terminal_with_rules_.end(); it++) {
    NonTerminal get_productions = *it;
    amount_of_productions_ += get_productions.get_production_rules().size();
  }
}
