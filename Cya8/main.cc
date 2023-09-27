/**
 * @file main.cpp
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Declaracion del programa principal. En el se hace uso de
 * la clase grammar pasando como parametro un archivo con extension .gra
 * y esperando como resultado en otro fichero .gra especificado por el usuario
 * los detalles de la gramatica en FNC
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "grammar.h"

int main (int argc, char* argv[]) {

    if (argc == 1) {
    std::cout << "dfa2grammar. Pruebe --help para mas informacion\n";
    return 1;
  }
  std::string help = argv[1];
  if (help == "--help" && argc == 2) {
    std::cout << "Modo de empleo: ./grammar2cnf ";
    std::cout << "input.gra output.gra";
    std::cout << "\nPara probar correctamente el programa debe introducir un ";
    std::cout << "archivo con extension .gra donde figure la configuracion de la gramatica ";
    std::cout << "\ny un archivo con extension .gra donde se detallara la gramatica en CNF.";
    std::cout << "\nAsegurese de que la gramatica este correctamente configurada antes de probar el programa.\n";
    return 1;
  }
  if (help != "--help" && argc == 2) {
    std::cout << "Error en la introduccion de comandos.";
    std::cout << " Pruebe con --help para mas informacion.\n";
    return 1;
  }

  std::string input_file_name = argv[1];
  if (!checkExtension(input_file_name, "gra")) {
    std::cout << "Asegurese de que la extension del archivo de la gramatica de entrada es .gra\n";
    std::cout << " Pruebe con --help para mas informacion.\n";
    return 1;
  }
  std::string output_file_name = argv[2];
  if (!checkExtension(output_file_name , "gra")) {
    std::cout << "Asegurese de que la extension del archivo de la gramatica de salida es .gra\n";
    std::cout << " Pruebe con --help para mas informacion.\n";
    return 1;
  }
  Grammar user_grammar(input_file_name);
  if (!user_grammar.get_error()) {
    user_grammar.grammarInfoTofile(output_file_name);
  }
  return 0;
}