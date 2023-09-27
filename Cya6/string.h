/**
 * @file String.h
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de cabecera de la clase string.h. Se declaran los metodos y
 * atributos de la clase string. Los automatas finitos analizan cadenas de simbolos.
 * Debido al uso de nombres autodescriptivos solo sera comentado aquello que sea
 * necesaria su explicacion.
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include "alphabet.h"

#define error_msg "Cadena no valida"

class String {
    private:
    Alphabet string_alphabet_;
    std::string string_;
    std::vector<std::string> string_vector_;
    size_t index_;
    bool error_ = false; /*Si existe algun error en la declaracion de la cadena*/

    public:
    String(Alphabet linealphabet, std::string linestring);
    String(std::string linestring);
    String();
    ~String();
    bool checkLongSymbol(size_t index, std::string symbol);
    bool stringToVector();
    bool checkError();
    std::string get_linestring();
    std::string get_linestring() const;
    std::vector<std::string> get_string_vector();
    std::vector<std::string> get_string_vector() const;
    void set_linestring(std::vector<std::string> stringset);
    void set_string_vector(std::vector<std::string> stringset);
    void showVectorString();
    bool operator<(String const &right) const;
    bool operator==(String &tocompare);
    String operator+(String &left);
    Alphabet get_alphabet() const;
    String inversed();

    
    void getAlphabetFromString();
    int string_lenght();
};


