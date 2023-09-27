/**
 * @file nonterminal.h
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de cabecera de la clase grammar.h. 
 * Archivo en la que se declara la clase gramatica que mediante
 * un archivo con extension .gra convertira dicha gramatica a FNC
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "nonterminal.h"
#include "alphabet.h"
#include "filecheckfunctions.h"

#define first_position 0
#define arrow_line '-'
#define arrow_head '>'
class Grammar {
  private:
    Alphabet grammar_alphabet_; /*Alfabeto de la gramatica*/
    std::set<NonTerminal> non_terminals_; /*Conjunto de no terminales de la gramtica*/
    NonTerminal initial_non_terminal_; /*No terminal de inicio de la gramatica*/
    std::set<std::string> productions_readed_; /*producciones leidas del fichero*/
    std::set<std::string> CNF_productions_; /*Producciones en FNC*/
    bool error_; /*En caso de error sera true*/
    std::vector<std::string> content_; /*Contenido del fichero .gra*/
    size_t index_; /**indice*/
    int production_index_; /*indice para recorrer las producciones*/
    std::set<std::vector<std::string> > separated_productions_; /*Una vez realizada la primera parte del algoritmo
                                                                  el resultado de las producciones se almacenan aqui
                                                                  para la segunda parte*/
  public:
    Grammar();
    Grammar(std::string file_name);
    void buildGrammarFromFile(std::string file_name);

    void readAlphabet();
    void readNonTerminals();
    void readInitialNonTerminal();
    void readProductions();

    bool checkSyntaxProductionRules();
    bool checkLeftArrowSide(std::string production_rule);
    bool checkRightArrowSide(std::string production_rule);
    bool checkArrow(std::string production_rule, int str_index);

    bool haveUnitaryProductions(std::string production_rule);
    bool haveEmptyProductions(std::string production_rule);

    void firstPartCNFAlgorithm();
    void replaceInProduction();
    void secondPartCNFAlgorithm();
    std::vector<std::string> productionsToVector(std::string to_check);
    void grammarInfoTofile(std::string file_name);
    bool get_error();
    void showGrammarInfo();
};