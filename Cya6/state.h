/**
 * @file state.h
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de cabecera de la clase state.h. 
 * En esta clase se declara la clase state que permitira crear
 * un objeto state el cual sera utilizado por la clase finiteautomata.h
 * para su correcto funcionamiento. Un automata finito esta compuesto por estados.
 * Debido al uso de nombres autodescriptivos solo sera comentado aquello que sea
 * necesaria su explicacion.
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "libraries.h"

struct Transition;

class State {
  private:
    std::string name_;
    bool accept_state_;
    bool initial_state_;
    std::set<Transition> state_transitions_;
  public:
    State();
    State(std::string name, bool accept, bool initial, std::set<Transition> state_transitions);
    ~State();

    void set_name(std::string name);
    void set_initial_state(bool setter);
    void set_accept_state(bool setter);
    void set_state_transitions(std::set<Transition> transitions);
    void set_transition(Transition transition);

    std::set<Transition> get_transitions();
    std::string get_name();
    bool get_accept_state();
    bool get_initial_state();
    bool operator<(State const &right) const;
    
    void ShowMyState();
};
/**
 * @brief Desarrollo de la estructura transicion.
 * Cada estado puede tener 0 o más transiciones en
 * un automata finito.
 */
struct Transition {
    State actual_state_;
    std::string symbol_; 
    State next_state_;
};