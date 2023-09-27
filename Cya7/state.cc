/**
 * @file state.cc
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de desarrollo de los metodos de la clase state.cc
 * En esta clase se ddesarrollan los metodos de stateh que permitira dotar
 * de funcionalidad al objeto state el cual sera utilizado por la clase finiteautomata.h
 * para su correcto funcionamiento. Debido al uso de nombres autodescriptivos solo 
 * sera comentado aquello que sea necesaria su explicacion.
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "state.h"

State::State() {}
State::State(std::string name, bool accept, bool initial, std::set<Transition> state_transitions) {
  name_ = name;
  accept_state_ = accept;
  initial_state_ = initial;
  state_transitions_ = state_transitions;
}

State::~State() {}

std::string State::get_name() {
  return name_;
}

void State::set_name(std::string name) {
  name_ = name;
}

bool State::get_accept_state() {
  return accept_state_;
}

bool State::get_initial_state() {
  return initial_state_;
}

void State::set_initial_state(bool setter) {
  initial_state_ = setter;
}

void State::set_accept_state(bool setter) {
  accept_state_ = setter;
}

void State::set_state_transitions(std::set<Transition> transitions) {
  state_transitions_ = transitions;
}

std::set<Transition> State::get_transitions() {
  return state_transitions_;
}


void State::set_transition(Transition transition) {
  state_transitions_.insert(transition);
}

inline bool operator<(const Transition& left, const Transition& right) {}

void State::ShowMyState() {
  std::cout << "Nombre: "<<name_ << "\n";
  if (accept_state_)
    std::cout << "Es de aceptacion\n";
  else 
    std::cout << "No es de aceptacion\n";
  if (initial_state_)
    std::cout << "Estado inicial\n";
  else 
    std::cout << "No es el estado inicial\n";

  if (state_transitions_.size() != 0) {
    for (auto it = state_transitions_.begin(); it != state_transitions_.end(); it++) {
      Transition to_show = *it;
      std::cout << to_show.actual_state_.get_name() << " <- ";
      std::cout << to_show.symbol_ << " -> ";
      std::cout << to_show.next_state_.get_name() << "\n";
    }
  }
}

bool State::operator<(State const &right) const {}

