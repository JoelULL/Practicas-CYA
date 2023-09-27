/**
 * @file regulargrammar.h
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de cabecera de la clase regulargrammar. En este
 * archivo se declara la clase que permitira obtener a partir de un
 * objeto fa que tenga la particularidad de ser un DFA, una gramatica 
 * regular tal que L(DFA) = L(GR). Debido al uso de nombres autodescriptivos 
 * solo sera comentado aquello que sea necesaria su explicacion.
 * @version 0.1
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include "finiteautomata.h"
#include "nonterminal.h"

class RegularGrammar {
  private:
  Alphabet grammar_alphabet_; /**Toda gramtica tiene un alfabeto de entrada*/
  NonTerminal initial_symbol_; 
  std::set<NonTerminal> non_terminal_symbols_; 
  std::set<NonTerminal> non_terminal_with_rules_; /*conjunto de no terminales con sus producciones asociadas*/
  bool error; /**En caso de error la variable se pondra en true*/
  int amount_of_productions_; 

  public:
    RegularGrammar();
    RegularGrammar(FiniteAutomata user_dfa);
    ~RegularGrammar();

    void getNonTerminalsFromStatesDfa(std::set<State> dfa_states);
    std::set<ProductionRule> getProductionRulesFromDfa(NonTerminal reference, std::set<Transition> state_transitions);
    void associateProductionRuleToNonTerminals(std::set<State> dfa_states);
    void grammarInfoTofile(std::string file_name);
    void howManyProductions();

    void showMyNonTerminals();
    void showProductionRules();
};