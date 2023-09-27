// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 4: Expresiones regulares
// Autor: Joel Aday Dorta Hernández
// Correo: alu0100987584@ull.es
// Fecha: 22/10/2022
// Archivo main.cc: programa cliente.
// Archivo principal del programa permitira reconocer las variables y comentarios
// de un archivo.cc que el usuario introduzca por comando y el resultado se escribira
// en un archivo de texto que tambien debe el usuario indicar por parametros

#include "codeanalyzer.h"

#define checkfor "for"
#define checkwhile "while"

bool isaFor(std::string check_for) {
  if (check_for.find(checkfor) != std::string::npos)
    return true;
  return false;
}
bool isaWhile(std::string check_while) {
  if (check_while.find(checkwhile) != std::string::npos)
    return true;
  return false;
}

int main (int argc, char* argv[]) {

  if(argc != 3) {
    std::cout << "\nPorfavor indique un codigo a analizar y despues un archivo para los resultados\n";
    return 1;
  }

  std::ifstream myfile;
  myfile.open(argv[1]);
  codeAnalyzer analyzer;
  std::string line;
  int counter = 0;
  while (std::getline(myfile, line)) {
    counter++;
    if(!analyzer.checkForSimpleCase(counter,line)) {
      analyzer.doesItHaveComments(counter, line);
    }
  }
  myfile.close();

  std::ofstream outputfile;
  outputfile.open(argv[2], std::ios::out);
  if(!outputfile.is_open()) {
    perror("Error open");
    exit(EXIT_FAILURE);
  }

  std::vector<simpleCase> simple_variables = analyzer.get_simple_variables();
  std::vector<simpleCase> simple_comments = analyzer.get_simple_comments();
  std::vector<simpleCase> simple_loops = analyzer.get_simple_loops();

  outputfile << "Variables detectadas:\n";
  for (size_t i = 0; i < simple_variables.size(); i++) {
    outputfile << "[linea: " << simple_variables[i].line_number << " ]";
    outputfile << " " << simple_variables[i].line << "\n";   
  }

  outputfile << "comentarios detectados:\n";
  for (size_t i = 0; i < simple_comments.size(); i++) {
    outputfile << "[linea: "<< simple_comments[i].line_number << " ]";
    outputfile << " " << simple_comments[i].line << "\n";
  }

  outputfile << "bucles detectados:\n";
  for (size_t i = 0; i < simple_loops.size(); i++) {
    if (isaFor(simple_loops[i].line)) {
      outputfile << "[linea: "<< simple_loops[i].line_number << " ]";
      outputfile << "Loop: " << checkfor << "\n";
    }
    if (isaWhile(simple_loops[i].line)) {
      outputfile << "[linea: "<< simple_loops[i].line_number << " ]";
      outputfile << "Loop: " << checkwhile << "\n";
    }
  }
  if (analyzer.checkMain()) {
    outputfile << "\nMAIN: True";
  }
  else
    outputfile << "\nMAIN: False";


  outputfile.close();
  //analyzer.debugShow(); 
  return 0;
}