/**
 * @file finiteautomata.cc
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de desarrollo de metodos de la clase finiteautomata. 
 * En este archivo se desarrollan los metodos de la clase finiteautomata
 * que dotaran de funcionalidad a el objeto generado por la misma. Debido
 * al uso de nombres autodescriptivos solo se comentaran aquellos metodos y
 * variables que requieran una descripcion adicional que expliquen su funcionalidad
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "finiteautomata.h"

FiniteAutomata::FiniteAutomata() {}
FiniteAutomata::FiniteAutomata(std::string filename) {
  buildNFA(filename);
}
FiniteAutomata::~FiniteAutomata() {}
/**
 * @brief Metodo que se encarga de obtener la configuracion
 * de un fichero de entrada .fa para la construccion del 
 * automata finito
 * @param filename Se trata del nombre del fichero .fa
 */
void FiniteAutomata::buildNFA(std::string filename) {
  std::ifstream myfile;
  myfile.open(filename);
  error = false;

  if (!myfile.is_open()) {
    perror("Error open");
    exit(EXIT_FAILURE);
  }
  std::string line;
  int line_counter = 1;
  while (std::getline(myfile, line)) {
    switch (line_counter)
    {
      case 1: {
        Alphabet readed_from_text(getTheAlphabet(line));
        input_alphabet_ = readed_from_text;
        
        std::cout << "El alfabeto es: ";
        input_alphabet_.showAlphabet();
        break;
      }
      case 2: {
        if (!checkNumberOfStates(line)) {
          std::cout << "Debe especificar un numero de estados correcto!\n";
          error = true;
          break;
        }
        int to_number = std::stoi(line);
        amount_of_states_ = to_number;
         
        std::cout << "numero de estados: " << amount_of_states_<<"\n";
        break;
      } 
      case 3: {
        initial_automata_state_.set_name(line);
        initial_automata_state_.set_initial_state(true);
        initial_automata_state_.set_accept_state(false);
        
        std::cout << "Estado de inicio: " << initial_automata_state_.get_name();
        std::cout << "\n";
        break;
      }  
        
      default: {
        readStateDeclarationLines(line);
        break;
      }
    }
    line_counter++;
    if (error)
      break;
  }
  myfile.close(); 
  getDeclarationState();
  getStatesTransitions();
  if (states_with_transitions_.size() != amount_of_states_){
    std::cout << "Error en la declaracion de los estados!\n";
    error = true;
  }
  std::cout << "\nEstados y sus transiciones: \n\n";
  showMyStates();
  std::cout << "\n";
}

/**
 * @brief Metodo que se permitira leer del archivo .fa
 * la declaracion de los estados junto con sus transiciones
 * 
 * @param state_declaration 
 */
void FiniteAutomata::readStateDeclarationLines(std::string state_declaration) {
  state_declaration_lines_.push_back(separateStateDeclaration(state_declaration));
}

void FiniteAutomata::getDeclarationState() {
  for (size_t i = 0; i < state_declaration_lines_.size(); i++) {
    State to_insert;
    to_insert.set_name(state_declaration_lines_[i][first_position]);

    if (state_declaration_lines_[i][second_position] == "0") {
       to_insert.set_accept_state(false);
    }
    if (state_declaration_lines_[i][second_position] == "1") {
      to_insert.set_accept_state(true);
    }
    if (state_declaration_lines_[i][second_position] != "0" && state_declaration_lines_[i][second_position] != "1") {
      std::cout << "Error especificacion de estado de aceptacion\n";
      error = true;
    }
    states_.insert(to_insert);
  }
  if (!checkInitialStateinGroup())
    error = true;
}

bool FiniteAutomata::checkInitialStateinGroup() {
  for (auto it = states_.begin(); it != states_.end(); it++) {
    State check = *it;
    if (check.get_name() == initial_automata_state_.get_name()) {
      check.set_initial_state(true);
      states_.erase(it);
      states_.insert(check);
      return true;
    }
  }
  return false;
}

void FiniteAutomata::getStatesTransitions() {
  for (auto it = states_.begin(); it != states_.end(); it++) {
    State get_transitions = *it;
    readStateTransitions(get_transitions);
  }
}
void FiniteAutomata::readStateTransitions(State state) {
  std::vector<std::string> auxiliar;
  bool finded = false;
  for (size_t i = 0; i < state_declaration_lines_.size(); i++) {
    if (state.get_name() == state_declaration_lines_[i][first_position]) {
      finded = true;
      auxiliar = state_declaration_lines_[i];
      break;
    }
  }
  if (!finded) {
    error = true;
  }
  else {
    int amount_of_transitions = std::stoi(auxiliar[2]);
    int checker = 0;
    Transition state_transition;
    state_transition.actual_state_ = state;
    bool symbol_finded = false;
    bool state_finded = false;
    for (size_t j = 3; j < auxiliar.size(); j++) {
      if (j % 2 == 0) {
        for (auto it = states_.begin(); it != states_.end(); it++) {
          State tofind = *it;
          if (tofind.get_name() == auxiliar[j]) {
            state_transition.next_state_ = tofind;
            state_finded = true;
            checker++;
            break;
          } 
        }
      }
      else {
        state_transition.symbol_ = auxiliar[j];
        checker++;
        symbol_finded = true;
      }
      if (symbol_finded && state_finded) {
        state.set_transition(state_transition);
        Transition empty;
        empty.actual_state_ = state;
        state_transition = empty;
        symbol_finded = false;
        state_finded = false;
      }

    }
    if (checker != amount_of_transitions * 2) {
      error = true;
      std::cout << "No se han declarado bien las trancisiones para el estado\n";
    }
    states_with_transitions_.insert(state);
  }
}

bool FiniteAutomata::checkStringNoEpsilonTransitions(std::string read_line) {
  setTransitionsInitialState();
  if (read_line == epsilon_str && read_line.size() == 1) {
    if (initial_automata_state_.get_accept_state())
      return true;
    else
      return false;
  }
  String tocheck(input_alphabet_, read_line);
  if (tocheck.checkError())
    return false;
  
  std::vector<std::string> separated_symbols = tocheck.get_string_vector();
  
  std::set<State> reacheables_states;
  std::set<State> auxiliar_set;
  reacheables_states = reachedStates(initial_automata_state_, separated_symbols[first_position]);
  if (reacheables_states.size() == 0)
    return false;

  for (size_t i = second_position; i < separated_symbols.size(); i++) {
    for (auto it = reacheables_states.begin(); it != reacheables_states.end(); it++) {
      State finded = *it;
      std::set<State> each_state = reachedStates(finded, separated_symbols[i]);
      for (auto it1 = each_state.begin(); it1 != each_state.end(); it1++) {
        State to_insert_set = *it1;
        auxiliar_set.insert(to_insert_set);
      }
    }
    reacheables_states = auxiliar_set;
    auxiliar_set.clear();
  }
  for (auto it = reacheables_states.begin(); it != reacheables_states.end(); it++) {
    State is_final_state = *it;
    if (is_final_state.get_accept_state())
      return true;
  }
  return false;
}

/**
 * @brief Metodo que se encarga de obtener aquellos estados a los que un estado
 * actual puede llegar en funcion de un simbolo de entrada
 * 
 * @param actual_state estado a analizar 
 * @param symbol simbolo de transicion
 * @return std::set<State> devuelve el conjunto de estados a los que el estado actual puede
 * alcanzar con dicho simbolo
 */
std::set<State> FiniteAutomata::reachedStates(State actual_state, std::string symbol) {
  std::set<std::string> states_names;
  std::set<Transition> actual_state_transitions = actual_state.get_transitions();
  std::set<State> to_return;

  for (auto it = actual_state_transitions.begin(); it != actual_state_transitions.end(); it++) {
    Transition tocheck = *it;
    if (tocheck.symbol_ == symbol) {
      states_names.insert(tocheck.next_state_.get_name());
    }
  }

  for (auto it = states_names.begin(); it != states_names.end(); it++) {
    std::string name = *it;
    for (auto it1 = states_with_transitions_.begin(); it1 != states_with_transitions_.end(); it1++) {
      State to_find = *it1;
      if (name == to_find.get_name()) {
        to_return.insert(to_find);
        break;
      }
    } 
  }
  return to_return;
}

void FiniteAutomata::setTransitionsInitialState() {
  for (auto it = states_with_transitions_.begin(); it != states_with_transitions_.end(); it++) {
    State check = *it;
    if (check.get_name() == initial_automata_state_.get_name()) {
      initial_automata_state_ = check;
      break;
    }   
  }
}

bool FiniteAutomata::checkStringWithEpsilonTransitions(std::string read_line) {
  setTransitionsInitialState();
  std::set<State> initial;
  initial.insert(initial_automata_state_);
  std::set<State> epsilon_closure = stateEpsilonTransitions(initial);
  if (read_line == epsilon_str && read_line.size() == 1) {
    for (auto it = epsilon_closure.begin(); it != epsilon_closure.end(); it++) {
      State tocheck = *it;
      if (tocheck.get_accept_state())
        return true;
    }
    return false;
  }
  String tocheck(input_alphabet_, read_line);
  if (tocheck.checkError())
    return false;  
  std::vector<std::string> separated_symbols = tocheck.get_string_vector();
  std::set<State> extended_transition;

  for (size_t i = 0; i < separated_symbols.size(); i++) {
    extended_transition = reachedStatesSet(epsilon_closure, separated_symbols[i]);
    if (extended_transition.size() == 0)
      return false;
    epsilon_closure = stateEpsilonTransitions(extended_transition);
  }
  
  for (auto it = extended_transition.begin(); it != extended_transition.end(); it++) {
    State accept = *it;
    if (accept.get_accept_state())
      return true;
  }
  return false;
}


std::set<State> FiniteAutomata::stateEpsilonTransitions(std::set<State> closure) {
  std::set<State> to_return;
  std::stack<State> state_stack;
  
  for (auto it = closure.begin(); it != closure.end(); it++) {
    State to_stack = *it;
    state_stack.push(to_stack);
  }

  do {
    State check_epsilon = state_stack.top();
    state_stack.pop();
    to_return.insert(check_epsilon);
    bool founded = false;
    std::set<State> state_epsilon_transition = reachedStates(check_epsilon, epsilon_str);
    for (auto it = state_epsilon_transition.begin(); it != state_epsilon_transition.end(); it++) {
      State stacked = *it;
      founded = false;
      for (auto it1 = to_return.begin(); it1 != to_return.end(); it1++) {
        State is_it_here = *it1;
        if (stacked.get_name() == is_it_here.get_name()) {
          founded = true;
          break;
        }
      }
      if (!founded) {
        state_stack.push(stacked);
      }
    }
  } while(state_stack.size() != 0);


  return to_return;
}

std::set<State> FiniteAutomata::reachedStatesSet(std::set<State> states_to_check, std::string symbol) {
  std::set<State> to_return;
  std::set<State> auxiliar;
  std::set<State> check;
  for (auto it = states_to_check.begin(); it != states_to_check.end(); it++) {
    State to_insert = *it;
    for (auto it1 = states_with_transitions_.begin(); it1 != states_with_transitions_.end(); it1++) {
      State to_compare = *it1;
      if (to_insert.get_name() == to_compare.get_name()) {
        check.insert(to_compare);
        break;
      }
    }
  }
  for (auto it = check.begin(); it != check.end(); it++) {
    State to_check = *it;
    auxiliar = reachedStates(to_check, symbol);
    for (auto it1 = auxiliar.begin(); it1 != auxiliar.end(); it1++) {
      State to_insert = *it1;
      to_return.insert(to_insert);
    }
    auxiliar.clear();
  } 

  return to_return;
}

bool FiniteAutomata::get_error() {
  return error;
}


void FiniteAutomata::showMyStates() {
  for (auto it = states_with_transitions_.begin(); it != states_with_transitions_.end(); it++) {
    State show = *it;
    show.ShowMyState();
  }
}

void FiniteAutomata::checkNextStates() {
  State check;
  for (auto it = states_with_transitions_.begin(); it != states_with_transitions_.end(); it++) {
    State test = *it;
    if (test.get_name() == "0") {
      check = test;
      break;
    }
  }
  std::set<State> to_show = reachedStates(check, "1");
  std::cout << "Los estados a los que puede transitar el estado inicial con un 1: ";
  for (auto it = to_show.begin(); it != to_show.end(); it++) {
    State showit = *it;
    std::cout << showit.get_name() << ", ";
  }
  std::cout << "\n";
}

void FiniteAutomata::testEpsilon() {
  State epsilon_closure;
for (auto it = states_with_transitions_.begin(); it != states_with_transitions_.end(); it++) {
  State to_check = *it;
  if (to_check.get_name() == "q2") {
    epsilon_closure = to_check;
    break;
  }
}
  std::set<State> to_show;
  to_show.insert(epsilon_closure);
  std::set<State> show_set = reachedStatesSet(to_show, "b");
  for (auto it = show_set.begin(); it != show_set.end(); it++) {
    State inside = *it;
    std::cout << inside.get_name() << " ";
  }
  std::cout << "\n";
}

void FiniteAutomata::showInsideSet(std::set<State> set_show) {
  for (auto it = set_show.begin(); it != set_show.end(); it++) {
    State show = *it;
    std::cout << show.get_name() << " ";
  }
  std::cout << "\n";
}
