/**
 * @file main.cpp
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Declaracion del programa principal. En el se le permite
 * al usuario obtener el cambio con el minimo numero de monedas en 
 * funcion de una cantidad en euros especificada en la linea de comandos.
 * Tambien han sido añadidas las opciones -o que permite la ejecucion del
 * algoritmo con un orden de complejidad 0(m) y la opcion -b que añade 
 * la opcion de integrar los billetes de euro.
 * @version 0.1
 * @date 2022-12-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "greedycoin.h"
#include "userinputcontrol.cc"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "greedycoin. Para mas ayuda ejecute: /greedycoin -h\n";
    return 1;
  }
  std::string user_input = argv[1];
  if (argc == 2 && user_input  == "-h") {
    std::cout << "Para ejecutar greedycoin ejecute: /greedycoin seguido " 
      << "de un valor en euros, recuerde que el formato debe ser como los" 
      << " siguientes ejemplos: 5,14€ ó 5€. /greedycoin 5,34€\n";
    std::cout << "Para ejecutar opcionales:\n";
    std::cout << "Para considerar billetes ejecute como en el "
    << "ejemplo: /greedycoin -b 534,45€\n";
    std::cout << "Para usar el algoritmo con orden de complejidad "
      << "O(m) ejecute como en el ejemplo: /greedycoin -o 4,15€\n";

    return 1;
  }
  if (argc == 2) {
    if (!checkUserValue(user_input)) {
      std::cout << "Error, entrada no valida ejecute: "
        << "/greedycoin -h para mas informacion\n";
      return 2;
    }
    std::cout << "moneda: "<<user_input << "\n";
    modifiyUserValue(user_input);
    GreedyCoin test(user_input);
    test.CoinChangeAlgorithm();
    if (test.get_error()) {
      std::cout << "Ha ocurrido un error, tipo de moneda no valido\n";
    }   
    test.additionalShowResult();

    return 0;
  }
  if (argc == 3) {
    std::string value = argv[2];
    if (!checkUserValue(value)) {
      std::cout << "Error, entrada no valida ejecute: "
        << "/greedycoin -h para mas informacion\n";
      return 2;
    }
    std::string option = argv[1];
    std::cout << "moneda: "<< value << "\n";
    modifiyUserValue(value);
    GreedyCoin testop(value);
    if (option == "-b") {
      testop.includingBill();
      testop.CoinChangeAlgorithm();
      if (testop.get_error()) {
        std::cout << "Ha ocurrido un error, tipo de moneda no valido\n";
      }
      testop.additionalShowResult();
      return 0;
    }
    if (option == "-o") {
      testop.additionalAlgorithm();
      testop.additionalShowResult();
      return 0;
    }    
  }
  if  (argc == 4) {
    std::string value = argv[3];
    if (!checkUserValue(value)) {
      std::cout << "Error, entrada no valida ejecute: "
        << "/greedycoin -h para mas informacion\n";
      return 2;
    }
    std::string option1 = argv[1];
    std::string option2 = argv[2];
    std::cout << "moneda: "<< value << "\n";
    modifiyUserValue(value);
    GreedyCoin testop(value);
    if ((option1 == "-b" && option2 == "-o") || (option1 == "-o" && option2 == "-b")) {
      testop.includingBill();
      testop.additionalAlgorithm();
      testop.additionalShowResult();
      return 3;
    }    
  }
  std::cout << "Algo ha ido mal, ejecute: "
    << "/greedycoin -h para mas informacion\n";
  return 0;
}
