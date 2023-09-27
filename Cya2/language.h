#pragma once

#include "string.h"

class Language {
  private:

  std::set<String> language_;
  Alphabet languagealphabet_;
  bool haveepsilon_ = false;
  bool isempty_ = false;
  
  public:

  Language();
  Language(std::set<String> strings);
  ~Language();

  void set_string(String newstring);
  void showMyLanguage();
  std::set<String> get_language_set();
  size_t get_language_size();
  void set_language_alphabet(Alphabet languagealphabet);
  Alphabet get_language_alphabet();
  void languageHaveEpsilon();
  bool checkEpsilon();
  bool checkForEmpty();

  //Para hacer estos metodos el alfabeto debe ser el mismo 
  //entre lenguajes
  Language languagesIntersection(Language tocompare);
  Language languagesUnion(Language tocompare);
  Language languagesDifference(Language tocompare);
  
  //se debe hacer union entre alfabetos en caso de ser distintos
  Language languagesConcatenation(Language toconcatenate);
 
  //Operaciones para un solo lenguaje
  Language languageInversed();
  Language stringspowers(int npower);
  
  std::string showResults();
};