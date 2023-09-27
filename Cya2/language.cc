#include "language.h"

Language::Language(){}

Language::Language(std::set<String> strings/*alphabet*/) {
  language_ = strings;
  //igualar alfabeto
}

Language::~Language(){}

void Language::set_string(String newstring) {
    language_.insert(newstring);
}


void Language::showMyLanguage(){
    String toshow;
    if (!checkForEmpty()) {
      std::cout << "Las cadenas que forman parte del lenguaje son: ";
      for (auto it = language_.begin(); it != language_.end(); it++)
      {
      toshow = *it;
      toshow.showVectorString();
      std::cout << " ";
      }  
      std::cout << "\n";
      std::cout << "el alfabeto de mi lenguaje es: ";
      languagealphabet_.showAlphabet();
      std::cout << "\n";
    }
    else
      std::cout << "Es el lenguaje vacio\n";
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

  return result;
}


Language Language::languagesUnion(Language tocompare) {
  std::set<String> comparedstrings = tocompare.get_language_set();
  std::set<String> resultset;
  std::set_union(language_.begin(), language_.end(), comparedstrings.begin(), comparedstrings.end(),
      std::inserter(resultset, resultset.begin()));

  Language result(resultset);
  result.set_language_alphabet(languagealphabet_);

  return result;
}


Language Language::languagesDifference(Language tocompare) {
  std::set<String> comparedstrings = tocompare.get_language_set();
  std::set<String> resultset;
  std::set_difference(language_.begin(), language_.end(), comparedstrings.begin(), comparedstrings.end(),
      std::inserter(resultset, resultset.begin()));

  Language result(resultset);
  result.set_language_alphabet(languagealphabet_);

  return result;
}

Language Language::languagesConcatenation(Language toconcatenate) {
  std::set<String> concatenate = toconcatenate.get_language_set();
  Alphabet left_alphabet = toconcatenate.get_language_alphabet();
  std::set<String> concresult;
  String toadd;
  String right;
  String left;

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