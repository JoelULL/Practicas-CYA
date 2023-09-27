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
    std::string inverse_string_;
    std::vector<std::string> sufix_;
    std::vector<std::string> prefix_;
    std::set<std::string> substringset_;
    size_t index_;
    bool error = false;
    public:
    String(Alphabet linealphabet, std::string linestring);
    String(std::string linestring);
    ~String();
    bool checkLongSymbol(size_t index, std::string symbol);
    bool stringToVector();
    void getAlphabetFromString();

    int string_lenght();
    std::string inverse_string();
    void sufix_string();
    void prefix_string();
    void substrings();
    std::string showResults(int opcode);
};
