/**
 * @file main.cpp
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Declaracion del programa principal. En el se comprueba un dfa
 * dado por el usuario y se obtiene una gramatica regular a partir de este
 * usando la clase regulargrammar.h. Se lleva a cabo un control de errores,
 * guiando al usuario en la correcta utilizacion del programa.
 * @version 0.1
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "regulargrammar.h"
#define fa ".fa"
#define gra ".gra"

int main (int argc, char* argv[]) {

  if (argc == 1) {
    std::cout << "dfa2grammar. Pruebe --help para mas informacion\n";
    return 1;
  }
  std::string help = argv[1];
  if (help == "--help" && argc == 2) {
    std::cout << "Modo de empleo: ./dfa2grammar ";
    std::cout << "input.fa output.gra";
    std::cout << "\nPara probar correctamente el programa debe introducir un ";
    std::cout << "archivo con extension .fa donde figure la configuracion del dfa ";
    std::cout << "\ny un archivo con extension .gra donde se detallara la gramatica a partir del dfa.";
    std::cout << "\nAsegurese de que el dfa este correctamente configurado antes de probar el programa.\n";
    return 1;
  }
  if (help != "--help" && argc == 2) {
    std::cout << "Error en la introduccion de comandos.";
    std::cout << " Pruebe con --help para mas informacion.\n";
    return 1;
  }

  std::string file_name = argv[1];
  if (!checkExtension(file_name, fa)) {
    std::cout << "Asegurese de que la extension del archivo del automata es .fa\n";
    std::cout << " Pruebe con --help para mas informacion.\n";
    return 1;
  }
  std::string output_file = argv[2];
  if (!checkExtension(output_file, gra)) {
    std::cout << "Asegurese de que la extension del archivo de la gramatica es .gra\n";
    std::cout << " Pruebe con --help para mas informacion.\n";
    return 1;   
  }

  FiniteAutomata test(file_name);
  if(test.get_error()) {
    std::cout << "Ha ocurrido un error!";
    std::cout << " Pruebe con --help para mas informacion.\n";
    return 1;
  }
  if (!test.detectDfa()) {
    std::cout << "Asegurese de que el automata finito que ha elegido sea determinista (dfa)\n";
    return 1;
  }

  RegularGrammar user_grammar(test);
  user_grammar.grammarInfoTofile(output_file);
  
  return 0;
}