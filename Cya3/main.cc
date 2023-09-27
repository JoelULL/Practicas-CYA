// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 3: Calculadora de lenguajes formales
// Autor: Joel Aday Dorta Hernández
// Correo: alu0100987584@ull.es
// Fecha: 18/10/2022
// Archivo main.cc: programa cliente.
// archivo principal del programa se encargara de leer los lenguajes y las
// operaciones del fichero de entrada haciendo uso de las funciones del fichero
// filefuncitons.h generando despues un objeto Calculator donde se realizaran
// las operaciones

#include "filefunctions.h"
#include "calculator.h"

int main(int argc, char* argv[])
{
  std::string line;
  //fichero de entrada
  std::ifstream myfile;
  myfile.open(argv[1]);

  if (!myfile.is_open()) {
    perror("Error open");
    exit(EXIT_FAILURE);
  } 

  std::vector<std::string> vline;
  std::string name = "";
  Language toinsert;
  std::vector<std::string> readoperations;
  std::set<Language> setlanguage;
  Language empty;
  bool errordetected = false;

  while (std::getline(myfile, line)) {
    vline = serateReadLine(line);
    if (checkIfIsLanguage(vline)) {
      name = vline[0]; 
      if (vline.size() > 3) {
        if (multipleStringLanguage(vline, name, toinsert)) {
          setlanguage.insert(toinsert);
          toinsert = empty;
          vline.clear();
        }
        else {
          errordetected = true;
          break;
        }
      }
      else {
        if (vline.size() == 3) {
          int lastposition = vline.size() - 1;
          std::string stringtocheck = vline[lastposition];
          if (unaryStringLanguage(stringtocheck, name, toinsert)) {
            setlanguage.insert(toinsert);
            toinsert = empty;
            vline.clear();
          }
          else {
            errordetected = true;
            break;
          }    
        }
        else {
          std::cout << "error en la declaracion del lenguaje\n";
          errordetected = true; 
          break;
        }
      }
    }
    else {
      readoperations.push_back(line);
      vline.clear();
    }
  }
  myfile.close();

  if (errordetected) {
    std::cout << "Error en la declaracion del lenguaje\n";
    return 1;
  }
  Calculator calculate(setlanguage, readoperations);
  calculate.CalculateOperations();

  return 0;
}