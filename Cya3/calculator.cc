// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 3: Calculadora de lenguajes formales
// Autor: Joel Aday Dorta Hernández
// Correo: alu0100987584@ull.es
// Fecha: 18/10/2022
// Archivo calculator.cc.
// archivo donde se desarrollan los metodos de la clase calculator
// que permitiran realizar las operaciones entre lenguajes dados
// cada uno de los metodos y variables utilizados usan nombres 
// identificativos para saber que funcion tienen en la clase

#include "calculator.h"

Calculator::Calculator(std::set<Language> languages, std::vector<std::string> operations) {
  languages_ = languages;
  readOperationElements(operations);
  binaryoperator_ = {concatenation, union, intersection, difference};
  unaryoperator_ = {inverse};
}

Calculator::~Calculator() {}

void Calculator::RPNCalc(std::vector<std::string> operation) {
  size_t iterator = 0;
  bool checked = false;
  bool errord = false;
  std::stack<Language> calculatorstack;
  Language result;
  
  do {
    if (isAnOperand(operation[iterator])) {
        calculatorstack.push(operand_); 
    }
    else {
      if (isBinaryOperator(operation[iterator])) {
        if (calculatorstack.size() < 2) {
          errord = true;
          break;
        }
        checked = true;
        Language left;
        Language right;
        
        right = calculatorstack.top();
        calculatorstack.pop();
        left = calculatorstack.top();
        calculatorstack.pop();

        result = binaryOperation(left, right);
        calculatorstack.push(result);
      }
      if (isUnaryOperator(operation[iterator]) && !checked) {
        Language operand;
        checked = true;
        if(calculatorstack.size() < 1) {
          errord = true;
          break;
        }
        operand = calculatorstack.top();
        calculatorstack.pop();
        result = unaryOperation(operand);
        calculatorstack.push(result);
      }
      if (isAnInteger(operation[iterator]) && !checked) {
        if (operation[iterator + 1] == power) {
          int powr = std::stoi(operation[iterator]);
          Language operand = calculatorstack.top();
          calculatorstack.pop();
          result = operand.stringspowers(powr);
          calculatorstack.push(result);
          iterator++;
          checked = true;
        }
      }
      if(!checked) {
          errord = true;
          break;
      }
    }
    iterator++;
    checked = false;
  } while(iterator < operation.size());

  if (calculatorstack.size() == 1 && !errord) {
    result = calculatorstack.top();
    calculatorstack.pop();
    result.set_name(resultname);
    result.automaticAlphabet();
    showResults(result, operation);
  }
  else {
    std::string wrongop = operationToString(operation);
    std::cout << wrongop << " " << errorexpression << "\n";
  }
}

void Calculator::CalculateOperations() {
  for (size_t i = 0; i < operations_.size(); i++) {
    RPNCalc(operations_[i]);
  }
}

void Calculator::showResults(Language toshow, std::vector<std::string> operation) {
  std::string operationstring = operationToString(operation);
  std::cout << operationstring << " tiene el siguiente resultado:\n";
  toshow.showMyLanguage();
  std::cout << "\n";
}

std::string Calculator::operationToString(std::vector<std::string> operation) {
  std::string result = "";
  size_t last = operation.size() - 1;

  for (size_t i = 0; i < operation.size(); i++) {
    result += operation[i];
    if (i != last) {
      result += ' ';
    }
  }
  return result;
}


void Calculator::readOperationElements(std::vector<std::string> listoperations) {
  std::string tovector = "";
  std::vector<std::string> operation;

  for (size_t i = 0; i < listoperations.size(); i++) {
    for (size_t j = 0; j < listoperations[i].size(); j++) {
      if (listoperations[i][j] != ' ') {
        tovector += listoperations[i][j];
      }
      else {
        operation.push_back(tovector);
        tovector = "";
      }
      if (j == listoperations[i].size() - 1) {
        operation.push_back(tovector);
        tovector = "";
      }
    }
    operations_.push_back(operation);
    operation.clear();
  }
}

bool Calculator::isAnOperand(std::string name) {
  Language tocheck;
  for (auto it = languages_.begin(); it != languages_.end(); it++) {
    tocheck = *it;
    if (tocheck.get_name() == name) {
      operand_ = tocheck;
      return true;
    } 
  }
  return false;
}

bool Calculator::isBinaryOperator(std::string tosearch) {
  for (size_t i = 0; i < binaryoperator_.size(); i++) {
    if (tosearch == binaryoperator_[i]) {
      operator_ = tosearch;
      return true;
    }
  }
  return false;
}
bool Calculator::isUnaryOperator(std::string tosearch) {
  for (size_t i = 0; i < unaryoperator_.size(); i++) {
    if (tosearch == unaryoperator_[i]) {
      operator_ = tosearch;
      return true;
    }
  }
  return false;
}

bool Calculator::isAnInteger(const std::string& tocheck) {
  std::string::const_iterator it = tocheck.begin();
  while (it != tocheck.end() && std::isdigit(*it)) ++it;

  return !tocheck.empty() && it == tocheck.end();
}

Language Calculator::binaryOperation(Language left, Language right) {
  char op = operator_[0];
  Language result;
  
  switch (op) {   
    case '+': {
      result = left.languagesConcatenation(right);
      break;
    }
    case '|': {
      result = left.languagesUnion(right);
      break;
    }
    case '^': {
      result = left.languagesIntersection(right);
      break;
    }
    case '-':{
      result = left.languagesDifference(right);
      break;
    }
    default:
      break;
  }
  result.set_name(resultname);

  return result;
}

Language Calculator::unaryOperation(Language operand) {
  char op = operator_[0];
  Language result;
  switch(op) {
    case '!': {
      result = operand.languageInversed();
      break;
    }
    default:
      break;
  }
  result.set_name(resultname);
  
  return result;
}