// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 3: Calculadora de lenguajes formales
// Autor: Joel Aday Dorta Hernández
// Correo: alu0100987584@ull.es
// Fecha: 18/10/2022
// Archivo calculator.h: Definicion de la clase calculator.
// En este archivo se define la clase que permite generar un objeto 
// calculator y en el que se podra dar uso a las funciones de calculo
// mediante operandos (lenguajes) y operaciones entre estos

#pragma once

#include "language.h"

#define concatenation "+"
#define union "|"
#define intersection "^"
#define difference "-"
#define inverse "!"
#define power "*"

#define resultname "result"
#define errorexpression "ERROR: Operacion incorrecta\n"

class Calculator {
  private:
    std::set<Language> languages_;
    std::vector<std::vector<std::string> > operations_;
    std::set<Language> results_;
    Language operand_;
    std::string operator_;
    std::vector<std::string> binaryoperator_;
    std::vector<std::string> unaryoperator_;
  
  public:
    Calculator(std::set<Language> languages, std::vector<std::string> operations);
    ~Calculator();

    void RPNCalc(std::vector<std::string> operation);
    void showResults(Language toshow, std::vector<std::string> operation);
    void readOperationElements(std::vector<std::string> listoperations);
    void CalculateOperations();
    bool isAnOperand(std::string name);
    bool isBinaryOperator(std::string tosearch);
    bool isUnaryOperator(std::string tosearch);
    bool isAnInteger(const std::string& tocheck);
    std::string operationToString(std::vector<std::string> operation);
    Language binaryOperation(Language right, Language left);
    Language unaryOperation(Language operand);
};