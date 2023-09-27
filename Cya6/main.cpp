/**
 * @file main.cpp
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Declaracion del programa principal. En el se genera un automata
 * usando la clase finiteautomata.h. Se lleva a cabo un control de errores,
 * guiando al usuario en la correcta utilizacion del programa.
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "finiteautomata.h"
#define txt ".txt"
#define fa ".fa"

int main (int argc, char* argv[]) {

  if (argc == 1) {
    std::cout << "P06 automata_simulator. Pruebe --help para mas informacion\n";
    return 1;
  }
  std::string help = argv[1];
  if (help == "--help" && argc == 2) {
    std::cout << "Modo de empleo: ./p06_automata_simulator ";
    std::cout << "input.fa input.txt";
    std::cout << "\nPara probar correctamente el programa debe introducir un ";
    std::cout << "archivo con extension .fa donde figure la configuracion del automata ";
    std::cout << "\ny un archivo con extension .txt donde escriba las cadenas para su testeo.";
    std::cout << "\nAsegurese de que el nfa este correctamente configurado antes de probar el programa.\n";
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
  FiniteAutomata test(file_name);
  if(test.get_error()) {
    std::cout << "Ha ocurrido un error!";
    std::cout << " Pruebe con --help para mas informacion.\n";
    return 1;
  }
  std::ifstream myfile;
  std::string input_text = argv[2];
  if (!checkExtension(input_text, txt)) {
    std::cout << "Asegurese de que la extension del archivo de las cadenas es .txt\n";
    std::cout << " Pruebe con --help para mas informacion.\n";
    return 1;
  }
  myfile.open(input_text);

  if(!myfile.is_open()) {
    perror("Error open");
    exit(EXIT_FAILURE);
  }
  std::string line;
  std::cout << "\n";
  std::cout << "A continuacion se muestra el resultado para cada cadena:\n\n";
  while(std::getline(myfile, line)) {
    if(test.checkStringWithEpsilonTransitions(line)) {
      std::cout << line << " --- " << "ACEPTADA\n";
    }
    else {
      std::cout << line << " --- " << "NO ACEPTADA\n";
    }
  }
  std::cout << "\n";
  myfile.close();
  

  return 0;
}