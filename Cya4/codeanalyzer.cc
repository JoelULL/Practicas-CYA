// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 4: Expresiones regulares
// Autor: Joel Aday Dorta Hernández
// Correo: alu0100987584@ull.es
// Fecha: 22/10/2022
// Archivo codeanalyzer.cc
// En este archivo se desarrollan los metodos de la clase CodeAnalyzer
// dotando de funcionalidad a los metodos. Todas los nombres de las variables
// y los metodos son autoexplicativos, es decir, en el propio nombre se define
// su funcionalidad. Sin embargo ciertos metodos han sido comentados para especificar
// su funcionalidad. Ademas se incluye un metodo de debug que mostrara los resultados
// cuando se requiera.

#include "codeanalyzer.h"

codeAnalyzer::codeAnalyzer() {

  std::string variable_no_equal("[ ]*(int|double)[ ][a-zA-Z_]+;[ ]*");
  std::string variable_with_equal("[ ]*(int|double)[ ][a-zA-Z_]+[ ]?=[ ]?\\d+\\.?\\d*;[ ]*");
  std::string cmbn_regex = variable_no_equal + "|" + variable_with_equal;

  std::string double_slash = "[ ]*[//]{2}.*";
  std::string single_asterisk = "[ ]*/\\*.*\\*/[ ]*";
  std::string combined_single_comments = double_slash + "|" + single_asterisk;
    
  double_int_regex_ = cmbn_regex;
  double_slash_comment_ = double_slash;
  single_asterisk_comment_ = single_asterisk;
  multiline_comment_regex_ = "^[ ]*/\\*[\\w\\W]*"; 
  no_brackets_loop_regex_ = "[ ]*(for|while)[ ]?[(][\\w*\\W]+[)];?[ ]*";
  brackets_loop_regex_ = "[ ]*(for|while)[ ]?[(][\\w*\\W]+[)][ ]?[{][\\w*\\W]*[}]?[ ]*";
  end_multiline_comment_regex_ ="[ ]*\\/";
  combined_single_comment_ = combined_single_comments;
  main_regex_ = "int main[ ]?[(][\\w\\W]*[)][ ]*([;]|[{])?";

  main_detected_ = false;
  multiline_comment_detected_ = false;
}
codeAnalyzer::~codeAnalyzer() {}

bool codeAnalyzer::detectIntsDoubles(std::string string_check) {
  return std::regex_match(string_check, double_int_regex_);
}

bool codeAnalyzer::detectSingleLineComment(std::string string_check) {
  return std::regex_match(string_check, double_slash_comment_);
}

bool codeAnalyzer::detectAsteriskSingleComment(std::string string_check) {
  return std::regex_match(string_check,single_asterisk_comment_);
}

bool codeAnalyzer::detectLoopNoBrackets(std::string string_check) {
  return std::regex_match(string_check, no_brackets_loop_regex_);
}

bool codeAnalyzer::detectLoopWithBrackets(std::string string_check) {
  return std::regex_match(string_check, brackets_loop_regex_);
}

bool codeAnalyzer::detectSimpleMain(std::string string_check) {
  return std::regex_match(string_check, main_regex_);
}

bool codeAnalyzer::checkForSimpleCase(int line_number, std::string string_check) {
  simpleCase toinsert;
  if(detectIntsDoubles(string_check)) {
    toinsert.line_number = line_number;
    toinsert.line = string_check;
    simple_variables_.push_back(toinsert);
    return true;
  }
  if(detectSingleLineComment(string_check) || detectAsteriskSingleComment(string_check)) {
    toinsert.line_number = line_number;
    toinsert.line = string_check;
    simple_comments_.push_back(toinsert);
    return true;
  }
  if (detectLoopNoBrackets(string_check) || detectLoopWithBrackets(string_check)) {
    toinsert.line_number = line_number;
    toinsert.line = string_check;
    simple_loops_.push_back(toinsert);
    return true;
  }

  if (detectSimpleMain(string_check)) {
    main_detected_ = true;
    return true;
  }

  return false;
}

void codeAnalyzer::doesItHaveComments(int line_number, std::string string_check) {
  std::smatch double_slash_match;
  std::smatch asterisk_match;
  // detecta si la linea tiene un comentario de doble barra
  if (std::regex_search(string_check, double_slash_match, double_slash_comment_)) {
    std::string double_slash_string = double_slash_match[0];

    checkForSimpleCase(line_number, double_slash_string);

    std::string::size_type slash_iterator = string_check.find(double_slash_string);
    if (slash_iterator != std::string::npos){
      string_check.erase(slash_iterator, double_slash_string.length());
    }
  }
  // detecta si tiene comentarios con asterisco de una linea
    if (std::regex_search(string_check, asterisk_match, single_asterisk_comment_)) {
    std::string asterisk_string = asterisk_match[0];

    checkForSimpleCase(line_number, asterisk_string);

    std::string::size_type asterisk_iterator = string_check.find(asterisk_string);
    if (asterisk_iterator != std::string::npos){
      string_check.erase(asterisk_iterator, asterisk_string.length());
    }
  }

  checkForSimpleCase(line_number, string_check);
}


bool codeAnalyzer::get_multi_comment_detection() {
  return multiline_comment_detected_;
}

void codeAnalyzer::readMultiLineComment(int line_number, std::string line_read) {
  simpleCase toinsert;
  toinsert.line = line_read;
  toinsert.line_number = line_number;

  multiline_comment_content_.push_back(toinsert);
}

std::vector<simpleCase> codeAnalyzer::get_simple_variables() {
  return simple_variables_;
}
std::vector<simpleCase> codeAnalyzer::get_simple_comments() {
  return simple_comments_;
}
std::vector<simpleCase> codeAnalyzer::get_simple_loops() {
  return simple_loops_;
}

bool codeAnalyzer::checkMain() {
  return main_detected_;
}


//degug method

void codeAnalyzer::debugShow() {
  std::cout << "Variables detectadas:\n";
  for (size_t i = 0; i < simple_variables_.size(); i++) {
    std::cout << "[linea: "<< simple_variables_[i].line_number << " ]";
    std::cout << " " << simple_variables_[i].line << "\n";
  }
  std::cout << "comentarios detectados:\n";
  for (size_t i = 0; i < simple_comments_.size(); i++) {
    std::cout << "[linea: "<< simple_comments_[i].line_number << " ]";
    std::cout << " " << simple_comments_[i].line << "\n";
  }
  std::cout << "bucles detectados:\n";
  for (size_t i = 0; i < simple_loops_.size(); i++) {
    std::cout << "[linea: "<< simple_loops_[i].line_number << " ]";
    std::cout << " " << simple_loops_[i].line << "\n";
  } 
  if (main_detected_)
    std::cout << "MAIN:\nTrue\n";

}