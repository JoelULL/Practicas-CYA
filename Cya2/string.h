// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 1: Simbolos, alfabetos y cadenas
// Autor: Joel Aday Dorta Hernandez
// Correo: alu0100987584@ull.es
// Fecha: 04/10/2022
// Archivo string.h: declaracion de metodos de la case string.
// Contiene la declaracion de los metodos de la clase string
// para el posterior desarrollo de su funcionalidad 

#pragma once
#include "alphabet.h"

#define error_msg "Cadena no valida"

class String {
    private:
    Alphabet string_alphabet_;
    std::string string_;
    std::vector<std::string> string_vector_;
    size_t index_;
    bool error_ = false;

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

    // probablemente pa los aires
    void getAlphabetFromString();
    int string_lenght();
};


