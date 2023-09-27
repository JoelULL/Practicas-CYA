/**
 * @file finiteautomata.h
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de cabecera de la clase finiteautomata. En este
 * archivo se declara la clase que permitira generar un objeto que 
 * simulara el comportamiento de un automata finito. Debido al uso
 * de nombres autodescriptivos solo sera comentado aquello que sea
 * necesaria su explicacion.
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "state.h"
#include "string.h"
#include "filecheckfunctions.h"

#define first_position 0
#define second_position 1
#define epsilon_str "&"

class FiniteAutomata {
  private:
    Alphabet input_alphabet_; 
    std::set<State> states_; 
    State initial_automata_state_;
    std::set<State> final_states_;
    std::set<State> states_with_transitions_;

    size_t amount_of_states_; /*Cantidad total de estados declarados en el archivo .fa*/
    bool error; /*En caso de que ocurra un error en la declaracion del automata*/
    std::vector<std::vector<std::string> > state_declaration_lines_;
    bool is_dfa_;
  public:
    FiniteAutomata();
    FiniteAutomata(std::string filename);
    ~FiniteAutomata();
    void buildNFA(std::string filename);
    
    void readStateDeclarationLines(std::string state_declaration);
    void getDeclarationState();
    bool checkInitialStateinGroup();
    void getStatesTransitions();
    void readStateTransitions(State state);

    bool checkStringNoEpsilonTransitions(std::string read_line);
    bool checkStringWithEpsilonTransitions(std::string read_line);
    std::set<State> reachedStates(State actual_state, std::string symbol);
    void setTransitionsInitialState();
    std::set<State> stateEpsilonTransitions(std::set<State> closure);
    std::set<State> reachedStatesSet(std::set<State> states_to_check, std::string symbol);
    bool get_error();
    bool detectDfa();
    Alphabet automataAlphabet();

    void showMyStates();
    void checkNextStates();
    void testEpsilon();
    void showInsideSet(std::set<State> set_show);

    std::set<State> get_states_with_transition(); 
};