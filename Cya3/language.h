// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 3: Calculadora de lenguajes formales
// Autor: Joel Aday Dorta Hernández
// Correo: alu0100987584@ull.es
// Fecha: 18/10/2022
// Archivo language.h
// Archivo language.h: Definicion de la clase language.h.
// En este archivo se define la clase que permite generar un objeto 
// language con sus caracteristicas (cadenas y alfabeto)
// ademas consta con todas las operaciones de lenguajes necesarias
// para esta practica


#pragma once

#include "string.h"

class Language {
  private:

    std::set<String> language_;
    Alphabet languagealphabet_;
    bool haveepsilon_ = false;
    bool isempty_ = false;
    std::string name_;
  
  public:

    Language();
    Language(std::set<String> strings);
    Language(std::string name, std::set<String> strings);
    ~Language();

    void set_string(String newstring);
    void showMyLanguage();
    std::set<String> get_language_set();
    std::set<String> get_language_set_const() const;
    size_t get_language_size();
    void set_language_alphabet(Alphabet languagealphabet);
    Alphabet get_language_alphabet();
    std::string get_name();
    void set_name(std::string name);
    void languageHaveEpsilon();
    void deleteEpsilon();
    bool checkEpsilon();
    bool checkForEmpty();
    bool EpsilonLanguage();
    Language languagesIntersection(Language tocompare);
    Language languagesUnion(Language tocompare);
    Language languagesDifference(Language tocompare);
    Language languagesConcatenation(Language toconcatenate);
    Language languageInversed();
    Language stringspowers(int npower);
    std::string showResults();
    void automaticAlphabet();
    bool operator<(Language const &right) const;
};