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
// Archivo language.cc.
// En este archivo se desarrollan los metodos de la clase que permite generar un objeto 
// language con sus caracteristicas (cadenas y alfabeto)

#include "language.h"

Language::Language(){}

Language::Language(std::set<String> strings) {
  language_ = strings;
}

Language::Language(std::string name, std::set<String> strings) {
  name_ = name;
  language_ = strings;
  automaticAlphabet();
}

Language::~Language(){}

void Language::set_string(String newstring) {
    language_.insert(newstring);
}


void Language::showMyLanguage(){
    String toshow;
    if(name_ == "") {
      name_ = "-unnamed-";
    }
    if (!checkForEmpty()) {
      if (haveepsilon_)
        std::cout << "{ & ";  
      else
        std::cout << "{ ";
      for (auto it = language_.begin(); it != language_.end(); it++)
      {
        toshow = *it;
        toshow.showVectorString();
        std::cout << " ";
        }
        std::cout << "}";
        std::cout << "\n";
        std::cout << "el alfabeto de mi lenguaje es: ";
        languagealphabet_.showAlphabet();
        std::cout << "\n";
    }
    else {
      if (haveepsilon_) {
        std::cout << "{&}";
      }
      else {
        std::cout << "{}\n";
      }
    }
      
}

std::set<String> Language::get_language_set() {
    return language_;
}

size_t Language::get_language_size() {
    return language_.size();
}


Language Language::languagesIntersection(Language tocompare) {
  std::set<String> comparedstrings = tocompare.get_language_set();
  std::set<String> resultset;
  std::set_intersection(language_.begin(), language_.end(), comparedstrings.begin(), comparedstrings.end(),
      std::inserter(resultset, resultset.begin()));

  Language result(resultset);
  result.set_language_alphabet(languagealphabet_);

  if (haveepsilon_ && tocompare.checkEpsilon())
    result.languageHaveEpsilon();

  return result;
}


Language Language::languagesUnion(Language tocompare) {
  std::set<String> comparedstrings = tocompare.get_language_set();
  std::set<String> resultset;
  std::set_union(language_.begin(), language_.end(), comparedstrings.begin(), comparedstrings.end(),
      std::inserter(resultset, resultset.begin()));

  Language result(resultset);
  result.set_language_alphabet(languagealphabet_);

  if(checkEpsilon() || tocompare.checkEpsilon())
    result.languageHaveEpsilon();

  return result;
}


Language Language::languagesDifference(Language tocompare) {
  std::set<String> comparedstrings = tocompare.get_language_set();
  std::set<String> resultset;
  std::set_difference(language_.begin(), language_.end(), comparedstrings.begin(), comparedstrings.end(),
      std::inserter(resultset, resultset.begin()));

  Language result(resultset);
  result.set_language_alphabet(languagealphabet_);

  if (haveepsilon_)
    result.languageHaveEpsilon();

  if (haveepsilon_ && tocompare.checkEpsilon())
    result.deleteEpsilon();

  return result;
}

Language Language::languagesConcatenation(Language toconcatenate) {
  std::set<String> concatenate = toconcatenate.get_language_set();
  Alphabet left_alphabet = toconcatenate.get_language_alphabet();
  std::set<String> concresult;
  String toadd;
  String right;
  String left;

  if (haveepsilon_) {
    
  }

  for (auto itA = language_.begin(); itA != language_.end(); itA++) {
    for (auto itB = concatenate.begin(); itB != concatenate.end(); itB++) {
      right = *itA;
      left = *itB;
      toadd = right + left;
      concresult.insert(toadd);
    }
  }
  Language result(concresult);
  Alphabet result_alphabet = languagealphabet_.unionAlphabet(left_alphabet);
  result.set_language_alphabet(result_alphabet);

    if (EpsilonLanguage()) {
    result = toconcatenate;
    result.automaticAlphabet();
    result.languageHaveEpsilon();
  }
  if (toconcatenate.EpsilonLanguage()) {
    Language result1(language_);
    result.automaticAlphabet();
    result.languageHaveEpsilon();
    return result1;
  }

    if (haveepsilon_ && toconcatenate.checkEpsilon())
      result.languageHaveEpsilon();

  return result;
}


Language Language::languageInversed() { 
  String reversed;
  String toequal;
  Language reversedlanguage;
  for (auto it = language_.begin(); it != language_.end(); it++) {
    toequal = *it;
    reversed = toequal.inversed();
    reversedlanguage.set_string(reversed);
  }
  reversedlanguage.set_language_alphabet(languagealphabet_);

  if (haveepsilon_)
    reversedlanguage.languageHaveEpsilon();

  return reversedlanguage;
}

Language Language::stringspowers(int npower) {
  Language mylanguage(language_);
  Language result;

  //if (npower >= 1 ) {
    result = mylanguage;
    for (int i = 0; i < npower - 1; i++) {
      result = mylanguage.languagesConcatenation(result);
    }
  //}

  result.set_language_alphabet(languagealphabet_);


  if (haveepsilon_)
    result.languageHaveEpsilon();

  return result;
}


void Language::set_language_alphabet(Alphabet languagealphabet) {
  languagealphabet_ = languagealphabet;
}

Alphabet Language::get_language_alphabet() {
  return languagealphabet_;
}

void Language::languageHaveEpsilon() {
  haveepsilon_ = true;
}

bool Language::checkEpsilon() {
  return haveepsilon_;
}


 bool Language::checkForEmpty() {
  if (language_.size() == 0 && !haveepsilon_) {
    isempty_ = true;
    return true;
  }
  return false;
 }

 std::string Language::get_name() {
  return name_;
 }

void Language::set_name(std::string name) {
  name_ = name;
}

 std::string Language::showResults() {
  std::string result = "";
  std::set<std::string> alphabetshow = languagealphabet_.alphabetset();
  std::string toadd = "";

  if (isempty_) {
    result += "{ ";
    for (auto it = alphabetshow.begin(); it != alphabetshow.end(); it++) {
      toadd += *it;
      result += toadd;
      result += " ";
      toadd = "";
    }
    result += "}";
    std::string stringlanguage = "{ }";
    result += stringlanguage;
  } else {
    //alfabeto
    result += "{ ";
    for (auto it = alphabetshow.begin(); it != alphabetshow.end(); it++) {
      toadd += *it;
      result += toadd;
      result += " ";
      toadd = "";
    }
    result += "}";

  //lenguaje
  result += " { ";
  std::set<String> showstrings = language_;
  String aux;
  for (auto it = showstrings.begin(); it != showstrings.end(); it++) {
      aux = *it;
      toadd += aux.get_linestring();
      result += toadd;
      toadd = "";
      result += " ";
  }
  result += "}";
  }

    return result;
 }

std::set<String> Language::get_language_set_const() const {
  return language_;
}

 void Language::automaticAlphabet() {
  String getitalphabet;
  Alphabet autoalphabet;
  for (auto it = language_.begin(); it != language_.end(); it++) {
    getitalphabet = *it;
    autoalphabet = autoalphabet.unionAlphabet(getitalphabet.get_alphabet());
  }
  set_language_alphabet(autoalphabet);
 }

 bool Language::operator<(Language const &right) const {
  return language_ < right.get_language_set_const();
 }


bool Language::EpsilonLanguage() {
  if (language_.size() == 0 && haveepsilon_) {
    return true;
  }
  return false;
}


void Language::deleteEpsilon() {
  haveepsilon_ = false;
}