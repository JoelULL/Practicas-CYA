// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 4: Expresiones regulares
// Autor: Joel Aday Dorta Hernández
// Correo: alu0100987584@ull.es
// Fecha: 22/10/2022
// Archivo codeanalyzer.h
// Se declara la clase condeAnalyzer y sus metodos ademas de
// la estructura simpleCase que servira para guardar el numero de linea
// y el contenido de la linea analizada.

#pragma once

#include "libraries.h"

struct simpleCase {
  int line_number;
  std::string line;
};

class codeAnalyzer {
  private:
    std::regex double_int_regex_;
    std::regex double_slash_comment_;
    std::regex single_asterisk_comment_;
    std::regex combined_single_comment_;
    std::regex multiline_comment_regex_;
    std::regex end_multiline_comment_regex_;
    std::regex no_brackets_loop_regex_;
    std::regex brackets_loop_regex_;
    std::regex main_regex_;

    std::vector<simpleCase> simple_variables_;
    std::vector<simpleCase> simple_comments_;
    std::vector<simpleCase> simple_loops_;

    std::vector<simpleCase> description_;
    std::vector<std::vector<simpleCase> > multiline_comments_;
    
    bool main_detected_;
    bool multiline_comment_detected_;

    simpleCase multiline_comment_first_;
    std::vector<simpleCase> multiline_comment_content_;
  public:

    codeAnalyzer();
    ~codeAnalyzer();
    // Variables
    bool detectIntsDoubles(std::string string_check);
    // Comentarios
    bool detectSingleLineComment(std::string string_check);
    bool detectAsteriskSingleComment(std::string string_check);

    bool detectMultiLineComment(std::string string_check);
    void readMultiLineComment(int line_number, std::string line_read);
    bool endOfMultiLineComment(std::string line_read);
    // bucles
    bool detectLoopNoBrackets(std::string string_check);
    bool detectLoopWithBrackets(std::string string_check);
    
    
    bool detectSimpleMain(std::string string_check);

    bool checkForSimpleCase(int line_number, std::string string_check);
    void doesItHaveComments(int line_number, std::string string_check);

    bool get_multi_comment_detection();
    bool checkMain();

    std::vector<simpleCase> get_simple_variables();
    std::vector<simpleCase> get_simple_comments();
    std::vector<simpleCase> get_simple_loops();

    //debug
    void debugShow();
};