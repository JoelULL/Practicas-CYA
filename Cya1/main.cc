// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 1: Simbolos, alfabetos y cadenas
// Autor: Joel Aday Dorta Hernández
// Correo: alu0100987584@ull.es
// Fecha: 04/10/2022
// Archivo main.cc: programa cliente.
// Contiene la funcion main del proyecto que usa las clases alphabet y string
// para poder obtener el alfabeto y la linea de cada entrada del texto y poder
//procesarla en funcion del opcode ingresado por el usuario

#include "string.h"
#include "filefunctions.h"

#define opcodemax 5
#define opcodemin 1

int main(int argc, char* argv[]) {
  std::ifstream myfile;
  myfile.open(argv[1]);

  if(!myfile.is_open()) {
    perror("Error open");
    exit(EXIT_FAILURE);
  } 

  std::ofstream outputfile;
  outputfile.open(argv[2], std::ios::out);
  if(!outputfile.is_open()) {
    perror("Error open");
    exit(EXIT_FAILURE);
  }
  int opcode = std::stoi(argv[3]);
  
  std::string line; 
  std::vector<std::string> linetovector; 
  std::string linestring; 
  std::vector<std::string> linealphabet; 
  if (opcode < opcodemin || opcode > opcodemax) {
    std::cout << "inserte un numero entre 1 y 5";
    return 1;
  }
  while(std::getline(myfile, line)) {
    if(haveSpaces(line)){
      linetovector = stringToVector(line);
      linealphabet = separateStringAlphabet(linetovector, linestring);
      Alphabet alphabet(linealphabet);
      String chain(alphabet, linestring);
      outputfile << chain.showResults(opcode);
      outputfile << "\n";
    }
    else {
      String chain(line);
      outputfile << chain.showResults(opcode);
    }
  }

  myfile.close();
  outputfile.close();

  return 0;
}