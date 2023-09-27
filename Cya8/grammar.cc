/**
 * @file grammar.cc
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de cabecera de la clase grammar.cc. 
 * En esta clase se desarrollan los metodos de la clase
 * grammar que la dotaran de funcionalidad y permitira generar
 * un archivo .gra que especifique la gramatica en FNC. Debido al uso de nombres 
 * autodescriptivos solo sera comentado aquello que sea necesaria su explicacion.
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "grammar.h"
Grammar::Grammar() {}
Grammar::Grammar(std::string file_name) {
  error_ = false;
  buildGrammarFromFile(file_name);
}
/**
 * @brief Metodo que se encarga de construir la gramatica 
 * en base al archivo de entrada .gra que ha proporcionado
 * el usuario
 * 
 * @param file_name nombre del archivo de entrada con extension .gra
 */
void Grammar::buildGrammarFromFile(std::string file_name) {
  std::ifstream myfile;
  myfile.open(file_name);

  if (!myfile.is_open()) {
    perror("Error open");
    exit(EXIT_FAILURE);
  }
  std::string line;
  while (std::getline(myfile, line)) {
    content_.push_back(line);
    line.clear();
  }
  readAlphabet();
  readNonTerminals();
  readInitialNonTerminal();
  if (error_) {
    std::cout << "Error no terminal inicial no conocido!\n";
  }
  else {
    readProductions();
    if (error_)
      std::cout << "Error formato de archivo incorrecto, revise" <<
        " el numero de producciones";
    checkSyntaxProductionRules();
    if (error_)
      std::cout << "Una o varias producciones incorrectas!\n";
  }
}
/**
 * @brief obtiene el alfabeto que ha leido del fichero
 * de entrada
 * 
 */
void Grammar::readAlphabet() {
  std::set<std::string> symbols_to_alphabet;
  if (!checkNumber(content_[first_position])) {
    error_ = true;
  }
  if (!error_ ) {
    size_t counter = 0;
    size_t amount_of_symbols = std::stoi(content_[first_position]);
    for (size_t i = 1; i < content_.size(); i++) {
      symbols_to_alphabet.insert(content_[i]);
      counter++;
      if (amount_of_symbols == counter) {
        index_ = i;
        break;
      }
    }
    Alphabet to_grammar(symbols_to_alphabet);
    grammar_alphabet_ = to_grammar;
  }
}
/**
 * @brief Genera los no terminales que el usuario
 * ha especificado en el fichero de entrada
 * 
 */
void Grammar::readNonTerminals() {
  if (!checkNumber(content_[index_ + 1])) {
    error_ = true;
  }
  if (!error_ ) {
    size_t counter = 0;
    size_t amount_of_nonterminals = std::stoi(content_[index_ + 1]);
    index_ += 2;
    for (size_t i = index_; i < content_.size(); i++) {
      NonTerminal to_insert(content_[i]);
      non_terminals_.insert(to_insert);
      counter++;
      if (amount_of_nonterminals == counter) {
        index_ = i;
        break;
      }
    }
  }  
}
/**
 * @brief Detecta el no terminal de inicio de la gramatica
 * 
 */
void Grammar::readInitialNonTerminal() {
  index_ += 1;
  bool founded = false;
  for (auto it = non_terminals_.begin(); it != non_terminals_.end(); it++) {
    NonTerminal to_check = *it;
    if (to_check.get_name() == content_[index_]) {
      founded = true;
      to_check.set_initial_non_terminal(true);
      initial_non_terminal_ = to_check;
      non_terminals_.erase(it);
      non_terminals_.insert(initial_non_terminal_);
      break;
    }
  }
  if (!founded) {
    error_ = true;
  }
  index_++;
}
/**
 * @brief Lee las producciones de la gramatica que
 * se han especificado en el fichero de entrada
 * 
 */
void Grammar::readProductions() {
  if (!checkNumber(content_[index_])) {
    error_ = true;
  }
  if (!error_ ) {
    size_t counter = 0;
    size_t amount_of_productions = std::stoi(content_[index_]);
    index_++;
    for (size_t i = index_; i < content_.size(); i++) {
      productions_readed_.insert(content_[i]);
      counter++;
      if (amount_of_productions == counter) {
        index_ = i;
        break;
      }
    }
    if (counter != amount_of_productions) {
      error_ =  true;
    }
    if (index_ != content_.size() - 1) {
      error_ = true;
    }
  }  
}
/**
 * @brief Comprueba que las producciones que han sido especificadas
 * no contengan producciones unitarias por ejemplo:
 * A -> B
 * 
 * @param production_rule regla de produccion a revisar
 * @return true en caso de que se trate de una produccion unitaria
 * @return false en caso contrario
 */
bool Grammar::haveUnitaryProductions(std::string production_rule) {
  std::string to_check = "";
  for (size_t i = production_index_; i < production_rule.size(); i++) {
    to_check += production_rule[i];
  }
  if (to_check.size() > 1)
    return false;
  for (auto it = non_terminals_.begin(); it != non_terminals_.end(); it++) {
    NonTerminal non_terminal = *it;
    if (non_terminal.get_name() == to_check) {
      return true;
    }
  }
  return false;
}
/**
 * @brief Detecta si en las producciones especificadas hay alguna 
 * que sea vacia por ejemplo:
 * A ->
 * @param production_rule produccion a revisar
 * @return true en caso de que se trate de una produccion vacia
 * @return false en caso contrario
 */
bool Grammar::haveEmptyProductions(std::string production_rule) {
  std::string to_check = "";
  for (size_t i = production_index_; i < production_rule.size(); i++) {
    to_check += production_rule[i];
  }
  return to_check.size() == 0;
}
/**
 * @brief Comprueba que la sintaxis de las producciones sea correcta
 * es decir que tengan la siguiente forma:
 * No terminal -> conjunto de terminales y no terminales
 * 
 * @return true en caso de que las producciones sean correctas 
 * sintacticamente
 * @return false en caso contrario
 */
bool Grammar::checkSyntaxProductionRules() {
  bool syntax_OK = false;
  for (auto it = productions_readed_.begin(); it != productions_readed_.end(); it++) {
    syntax_OK = false;
    std::string to_check = *it;
    if(checkLeftArrowSide(to_check)) {
      if(checkArrow(to_check, production_index_)) {
        if(checkRightArrowSide(to_check)) {
          syntax_OK = true;
        }
      }
    }
    if (syntax_OK) {
      if (haveEmptyProductions(to_check) || haveUnitaryProductions(to_check)) {
        error_ = false;
        return false;
      }
        
    }
    else {
      error_ = true;
      return false;
    }
  }
  return true;
}
/**
 * @brief Comprueba que el no terminal del lado izquierdo de la produccion
 * sea uno de los no terminales especificado
 * 
 * @param production_rule produccion a analizar
 * @return true se ha especificado
 * @return false en caso contrario
 */
bool Grammar::checkLeftArrowSide(std::string production_rule) {
  std::string non_terminal_name = "";
  for (size_t i = 0; i < production_rule.size(); i++) {
    if (production_rule[i] != ' ') {
      non_terminal_name += production_rule[i];
    }
    else {
      production_index_ = i + 1;
      break;
    }
  }
  bool founded = false;
  for (auto it = non_terminals_.begin(); it != non_terminals_.end(); it++) {
    NonTerminal to_check = *it;
    if (to_check.get_name() == non_terminal_name) {
      founded = true;
      break;
    }
  }
  return founded;
}
/**
 * @brief Comprueba que las producciones tengan la flecha que separa
 * el no terminal del conjunto de terminales y no terminales del otro
 * extremo de la produccion
 * 
 * @param production_rule produccion analizar
 * @param str_index indice de la produccion leida
 * @return true en caso de que tenga la flecha
 * @return false en caso contrario
 */
bool Grammar::checkArrow(std::string production_rule, int str_index) {
  bool checked = false;
  if (production_rule[str_index] == arrow_line) {
    if (production_rule[str_index + 1] == arrow_head) {
      production_index_ += 3;
      checked = true;
    }
  }
  return checked;
}
/**
 * @brief Comprueba que el conjunto de los terminales y no
 * terminales del lado derecho de la flecha de la produccion
 * sean correctos y se hayan espeficado con anterioridad
 * 
 * @param production_rule produccion a analizar
 * @return true en caso de que sea correcto el conjunto
 * @return false en caso contrario
 */
bool Grammar::checkRightArrowSide(std::string production_rule) {
  std::set<std::string> alphabet_set = grammar_alphabet_.alphabetset();
  std::string non_terminals = "";
  std::string readed_symbol = "";
  bool founded = false;

  for (size_t i = production_index_; i < production_rule.size(); i++) {
    readed_symbol += production_rule[i];
    founded = false;
    for (auto it = alphabet_set.begin(); it != alphabet_set.end(); it++) {
      std::string symbol = *it;
      if (symbol == readed_symbol) {
        founded = true;
        readed_symbol = "";
        break;
      }
    }
    if (!founded) {
      non_terminals += readed_symbol;
      readed_symbol = "";
    }
  }
  founded = false;
  std::string to_check = "";
  size_t counter = 0;

  for (size_t i = 0; i < non_terminals.size(); i++) {
    to_check += non_terminals[i];
    founded = false;
    for (auto it = non_terminals_.begin(); it != non_terminals_.end(); it++) {
      NonTerminal check = *it;
      if (check.get_name() == to_check) {
        counter++;
        founded = true;
        to_check = "";
        break;
      }
    }
    if (!founded)
      return false;
  }
  return counter == non_terminals.size();
}
/**
 * @brief Ejecuta la primera parte del algoritmo de CNF
 * convirtiendo todas aquellas producciones del tipo: 
 * A -> b
 * en:
 * A -> Cb
 * 
 */
void Grammar::firstPartCNFAlgorithm() {
  std::set<std::string> alphabet = grammar_alphabet_.alphabetset();
  std::vector<std::string> new_non_terminals_names;
  std::set<std::string> result;
  for (auto it = productions_readed_.begin(); it != productions_readed_.end(); it++) {
    std::string readed = *it;
    std::string production_part = "";
    for (size_t i = production_index_; i < readed.size(); i++) {
      production_part += readed[i];
    }
    if (production_part.size() >= 2) {
      std::string symbol_read = "";
      for (size_t j = 0; j < production_part.size(); j++) {
        symbol_read += production_part[j];
        for (auto it1 = alphabet.begin(); it1 != alphabet.end(); it1++) {
          std::string symbol = *it1;
          if (symbol_read == symbol) {
            std::string new_name = "C" + symbol;
            new_non_terminals_names.push_back(new_name);
          }
        }
        symbol_read = "";
      }
      
    }
    else {
      CNF_productions_.insert(readed);
    }
  }
  for (size_t i = 0; i < new_non_terminals_names.size(); i++) {
    result.insert(new_non_terminals_names[i]);
  }
  for (auto it = result.begin(); it != result.end(); it++) {
    std::string show = *it;
    NonTerminal to_insert(show);
    non_terminals_.insert(to_insert);
    CNF_productions_.insert(show + " -> "+show[1]);
  }
  replaceInProduction();
}
/**
 * @brief Permite realizar la segunda parte de la primera
 * parte del algoritmo de CNF de sustitucion.
 * sustituye en las producciones aquel simbolo terminal
 * por aquel no terminal que le corresponda ejemplo:
 * A -> aB
 * Ca -> a
 * el resultado final:
 * A -> CaB
 * Ca -> a
 */
void Grammar::replaceInProduction() {
  std::set<std::string> replaced;
  std::set<std::string> alphabet = grammar_alphabet_.alphabetset();
  bool founded = false;
  for (auto it = productions_readed_.begin(); it != productions_readed_.end(); it++) {
    std::string production = *it;
    if (production.size() > 6) {
      std::string to_insert = "";
      for (size_t i = 0; i < production.size(); i++) {
        std::string symbol_read = "";
        founded = false;
        symbol_read += production[i];
        for (auto it1 = alphabet.begin(); it1 != alphabet.end(); it1++) {
          std::string symbol = *it1;
          if (symbol == symbol_read) {
            std::string new_non_terminal = "C" + symbol;
            to_insert += new_non_terminal;
            founded = true;
            break;
          }
        }
        if(!founded)
          to_insert += symbol_read; 
      }
      replaced.insert(to_insert);
      to_insert = "";
    }else
      replaced.insert(production);
  }

  std::set<std::vector<std::string> > separated_productions;
  for (auto it = replaced.begin(); it != replaced.end(); it++) {
    std::string production = *it;
    separated_productions.insert(productionsToVector(production));
  }

  separated_productions_ = separated_productions;
}
/**
 * @brief En este metodo iria la segunda parte del algoritmo
 * de CNF que se encarga de convertir la gramatica en FNC
 * dejando producciones de estos dos tipos unicamente:
 * A -> a ó A -> AB
 * no siendo posible otros casos como producciones unitarias
 * o conjuntos de varios terminales.
 * A -> A ó A -> ab X
 */
void Grammar::secondPartCNFAlgorithm() {

}
/**
 * @brief Convierte las producciones una vez realizada la primera
 * parte del algoritmo en un vector para poder realizar la segunda 
 * parte del algoritmo de CNF
 * 
 * @param to_check 
 * @return std::vector<std::string> 
 */
std::vector<std::string> Grammar::productionsToVector(std::string to_check) {
  std::vector<std::string> result;
  std::string to_vector = "";
  size_t j = 0;
  do {
    switch(to_check[j]) {
      case 'C': {
        to_vector += to_check[j];
        j++;
        to_vector += to_check[j];
        result.push_back(to_vector);
        to_vector = " ";
        break;
      }
      case '-': {
        to_vector += to_check[j];
        j++;
        to_vector += to_check[j];
        result.push_back(to_vector);
        to_vector = " ";
        break;         
      }
      default: {
        if (to_check[j] != ' ') {
          to_vector += to_check[j];
          result.push_back(to_vector);
          to_vector = "";
          break;
        }
      }
    }
    j++;
  }while(j < to_check.size());

  for (size_t i = 0; i < result.size(); i++) {
  std::string::iterator end_pos = std::remove(result[i].begin(), result[i].end(), ' ');
  result[i].erase(end_pos, result[i].end());
  }  
  return result;
}
/**
 * @brief Permite conocer si la gramatica tiene algun error
 * 
 * @return true en caso de error
 * @return false en caso contrario
 */
bool Grammar::get_error() {
  return error_;
}
/**
 * @brief Metodo de debug
 * 
 */
void Grammar::showGrammarInfo() {
  firstPartCNFAlgorithm();
}
/**
 * @brief Metodo que se encarga de especificar las caracteristicas
 * de la gramatica en FNC en un fichero de salida especificado por el usuario
 * en este caso solo mostrara las producciones obtenidas en el primer paso
 * del algoritmo de FNC puesto que no se ha termiando la segunda parte.
 * 
 * @param file_name fichero con extension .gra de salida
 */
void Grammar::grammarInfoTofile(std::string file_name) {
  firstPartCNFAlgorithm();
  std::ofstream grammar_file(file_name);
  grammar_file << grammar_alphabet_.size() << "\n";
  std::set<std::string> symbols = grammar_alphabet_.alphabetset();
  for (auto it = symbols.begin(); it != symbols.end(); it++) {
    std::string symbol = *it;
    grammar_file << symbol << "\n";
  }
  grammar_file << non_terminals_.size() << "\n";

  for (auto it = non_terminals_.begin(); it != non_terminals_.end(); it++) {
    NonTerminal to_show = *it;
    grammar_file << to_show.get_name() << "\n";
  }
  grammar_file << initial_non_terminal_.get_name() << "\n";
  

  for (auto it = separated_productions_.begin(); it != separated_productions_.end(); it++) {
    std::vector<std::string> to_show = *it;
    for (size_t i = 0; i < to_show.size(); i++) {
      grammar_file << to_show[i];
    }
    grammar_file << "\n";
  }
  grammar_file.close();
}