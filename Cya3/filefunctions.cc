// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 3: Calculadora de lenguajes formales
// Autor: Joel Aday Dorta Hernandez
// Correo: alu0100987584@ull.es
// Fecha: 18/10/2022
// Archivo filefunctions.cc: desarrollo de metodos que se usaran en el main.
// contiene el desarrollo de los metodos para ciertas funcionalidades del main
// con el objetivo de obtener un main.cc mas limpio

#include "filefunctions.h"
std::vector<char> forbiddensymbols = {openbracket, closebracket, coma, equal, epsilon, space};

//usar una vez tenemos aisladas las cadenas del lenguaje y 
//se haya checkeado a epsilon
bool checkForbiddenSymbols(std::vector<std::string> myvector) {

  for(size_t i = 0; i < myvector.size(); i++) {
    for(size_t j = 0; j < myvector[i].size(); j++) {
      for (size_t k = 0; k < forbiddensymbols.size(); k++) {
        if (myvector[i][j] == forbiddensymbols[k]) {
          std::cout << "Lenguage incorrecto, contiene simbolos prohibidos\n";
          return true;
        }
      }
    }
  }
  return false;
}

//debug method
void showmyvector(std::vector<std::string> myvector) {
  for (size_t i = 0; i < myvector.size(); i++) {
    std::cout << myvector [i] << " ";
  }
}

//usar una vez tengamos aisladas las cadenas del lenguaje
bool checkforepsilon(std::vector<std::string> &strings) {
  std::vector<std::string> checked;
  bool epsilondetected = false;

  for (size_t i = 0; i < strings.size(); i++) {
    if (strings[i] != epsilonstr)
      checked.push_back(strings[i]);
    else
      epsilondetected = true;
  }
  strings = checked;

  return epsilondetected;
}

//comprueba la parte comun que tienen las declaraciones de
//los tres tipos posibles de lenguajes
//tipo A: L1 = {a, b, c}
//tipo B: L2 = {&} ó L2 = {b}
//tipo C: L3 = {}
//        ||||--> Parte comun
bool checkIfIsLanguage(std::vector<std::string> line) {
  //comprobar que la linea no este vacia
  if (line.empty()) {
    return false;
  }
  //comprobar lo que sera el nombre del lenguaje no contenga 
  //simbolos prohibidos
  for (size_t i = 0; i < line[0].size(); i++) {
    for (size_t j = 0; j < forbiddensymbols.size(); j++) {
      if (line[0][j] == forbiddensymbols[j])
        return false;
    }
  }
  //comprueba que el segundo elemento sea un igual
  if (line[1] != "=")
    return false;

  return true;
}

bool checkBetweenBrackets(std::vector<std::string> &line) {
  std::vector<std::string> checked;
  for (size_t i = 2; i < line.size();i++) {
    checked.push_back(line[i]);
  }
  int vectorlastposition = checked.size() - 1;
  int laststringcheck = checked[vectorlastposition].size() - 1;

  //comprueba que el primer elemento del vector despues del igual
  //contenga como primer elemento una llave abierta y que el ultimo
  //tenga en la ultima posicion una llave cerrada
  if (checked[0][0] != openbracket)
    return false;
  if (checked[vectorlastposition][laststringcheck] != closebracket)
    return false;

  //comprueba que todos los elementos despues del igual
  //excepto el ultimo tengan una coma al final
  std::string laststring = checked[vectorlastposition];

  checked.erase(checked.begin() + vectorlastposition);
  
  if (!checkForComas(checked)) {
    return false;
  }
  checked.insert(checked.begin() + vectorlastposition, laststring);

  //si todo esto hasta aqui es correcto entonces elimina las llaves del primer
  // y ultimo elemento en las zonas en las que deben estar
  checked[0].erase(checked[0].begin());
  checked[vectorlastposition].erase(checked[vectorlastposition].begin() + laststringcheck);

  line = checked;
  
  return true;
}

//separa la linea por espacios
std::vector<std::string> serateReadLine(std::string line) {
  std::string topush = "";
  std::vector<std::string> returned;
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] != ' ') {
      topush += line[i];
    }
    else {
      returned.push_back(topush);
      topush = "";
    }
    if (i + 1 == line.size())
      returned.push_back(topush);
    }

    return returned;
  }


  bool checkForComas(std::vector<std::string> &tocheck) {
    for (size_t i = 0; i < tocheck.size(); i++) {
      int laststringcheck = tocheck[i].size() - 1;
      if (tocheck[i][laststringcheck] != coma) {
        return false;
      }
      tocheck[i].erase(tocheck[i].begin() + laststringcheck);     
    }
    return true;
  }

std::set<String> createSetString(std::vector<std::string> linestrings) {
  std::set<String> toreturn;
  
  for (size_t i = 0; i < linestrings.size(); i++) {
    String toinsert(linestrings[i]);
    toreturn.insert(toinsert);
  }
  return toreturn;
}

bool multipleStringLanguage(std::vector<std::string> vline, std::string name, Language &toset) {
  Language toreturn;
  bool epsilondetected = false;

  if (checkBetweenBrackets(vline)) {
    epsilondetected = checkforepsilon(vline); //checkea si existe epsilon
    if (checkForbiddenSymbols(vline)) {
        return false;
      }
      else {
        std::set<String> readedstrings = createSetString(vline);
        Language newlanguage(name,readedstrings);
        if (epsilondetected)
          newlanguage.languageHaveEpsilon();
        
        toset = newlanguage;
      }
    }
    else {
      std::cout << "Error en la declaracion del lenguaje\n";
      return false;
    }

  return true;
}

bool checkforBracketsPosition(std::string tocheck) {
  int tochecklast = tocheck.size() - 1;
  return (tocheck[0] == openbracket && tocheck[tochecklast] == closebracket);
}

void eliminateBrackets(std::string &stringread) {
  stringread.erase(stringread.begin());
  int lastposition = stringread.size() - 1;
  stringread.erase(stringread.begin() + lastposition);
}

bool unaryStringLanguage(std::string readstring, std::string name, Language &toset) {
  Language empty;
  if (!checkforBracketsPosition(readstring)) {
    return false;
  }
  //caso del lenguaje vacio
  if (readstring.size() == 2) {
    toset = empty;
    toset.set_name(name);
    return true;
  }
  else {
    eliminateBrackets(readstring);
    std::vector<std::string> vstring = {readstring};
    if(checkforepsilon(vstring)) { //caso de que solo contenga la cadena vacia
      toset = empty;
      toset.languageHaveEpsilon();
      toset.set_name(name);
      return true;
    }
    if (!checkForbiddenSymbols(vstring)) {
      toset = empty;
      toset.set_string(vstring[0]);
      toset.set_name(name);
      toset.automaticAlphabet();

      return true;
    }
  }
  return false;
}