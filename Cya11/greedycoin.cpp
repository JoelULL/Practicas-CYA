/**
 * @file greedycoin.cc
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de desarrollo de la clase greedycoin.cc. En este
 * archivo se desarrollan los metodos que dotaran de funcionalidad
 * a la clase greedycoin. Debido al uso de nombres de metodos y variables
 * autodescriptivos solo sera comentado aquello que requiera una explicacion
 * con mas detalle. 
 * @version 0.1
 * @date 2022-12-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "greedycoin.h"

GreedyCoin::GreedyCoin() {}
GreedyCoin::GreedyCoin(std::string user_coin_value) {
  amount_of_coins_ = std::stoi(user_coin_value);
  availableCoins();
  error_ = false;
}
GreedyCoin::~GreedyCoin() {}
/**
 * @brief Metodo en el que se declaran todas 
 * las monedas de euro.
 */
void GreedyCoin::availableCoins() {
  Coin two_euro;
  two_euro.name = "2€";
  two_euro.value = 200;
  Coin one_euro;
  one_euro.name = "1€";
  one_euro.value = 100;
  Coin fifty_cent;
  fifty_cent.name = "50c";
  fifty_cent.value = 50;
  Coin twenty_cent;
  twenty_cent.name = "20c";
  twenty_cent.value = 20;
  Coin ten_cent;
  ten_cent.name = "10c";
  ten_cent.value = 10;
  Coin five_cent;
  five_cent.name = "5c";
  five_cent.value = 5;
  Coin two_cent;
  two_cent.name = "2c";
  two_cent.value = 2;
  Coin one_cent;
  one_cent.name = "1c";
  one_cent.value = 1;

  types_of_coins_.push_back(two_euro);
  types_of_coins_.push_back(one_euro);
  types_of_coins_.push_back(fifty_cent);
  types_of_coins_.push_back(twenty_cent);
  types_of_coins_.push_back(ten_cent);
  types_of_coins_.push_back(five_cent);
  types_of_coins_.push_back(two_cent);
  types_of_coins_.push_back(one_cent);
}
/**
 * @brief Algoritmo voraz principal. Permite
 * devolver el cambio de moneda utilizando una 
 * estrategia de algoritmos voraces.
 */
void GreedyCoin::CoinChangeAlgorithm() {
  int add = 0;
  int index = 0;
  int value;
  bool founded;
  do {
    founded = false;
    for (size_t i = index; i < types_of_coins_.size(); i++) {
      if ((add + types_of_coins_[i].value) <= amount_of_coins_) {
        change_coins_.push_back(types_of_coins_[i]);
        index = i;
        value = types_of_coins_[i].value;
        founded = true;
        break;
      }
    }
    if (!founded) {
      error_ = true;
      break;
    }
    add += value;
  } while(add != amount_of_coins_);
}
void GreedyCoin::simpleShowResult() {
  std::cout << "Solucion: ";
  for (size_t i = 0; i < change_coins_.size() - 1; i++) {
    std::cout << change_coins_[i].name << ", ";
  }
  std::cout << change_coins_[change_coins_.size() - 1].name << "\n";
  std::cout << "Total monedas: " << change_coins_.size() << "\n";
}
/**
 * @brief Metodo encargado de mostrar el resultado final,
 * pero que muestra cuantas monedas de cada tipo han sido
 * seleccionadas.
 */
void GreedyCoin::additionalShowResult() {
  int index = 0;
  int amount;
  std::string to_insert;
  for (size_t i = index; i < change_coins_.size(); i++) {
    amount = howManyTimes(change_coins_[i].name, index);
    if (amount > 1) { 
      to_insert = std::to_string(amount) + cross_symbol + change_coins_[i].name;
      result_.push_back(to_insert);
      index = index + amount;
    }
    if (amount == 1) {
      to_insert = change_coins_[i].name;
      result_.push_back(to_insert);
      index++;
    }
    to_insert = "";
  }
  std::cout << "Solucion: ";
  for (size_t i = 0; i < result_.size() - 1; i++) {
    std::cout << result_[i] << ", ";
  }
  std::cout << result_[result_.size() - 1] << "\n";
  std::cout << "Total monedas: " << change_coins_.size() << "\n";  
}

int GreedyCoin::howManyTimes(std::string coin_name, int index) {
  int counter = 0;
  for (size_t i = index; i < change_coins_.size(); i++) {
    if (coin_name == change_coins_[i].name)
      counter++;
  }
  return counter;
}
/**
 * @brief Al igual que el algoritmo utilizado
 * en CoinChangeAlgorithm(), este algoritmo
 * resulve el mismo problema solo que su orden
 * de complejidad pasa a ser O(m).
 */
void GreedyCoin::additionalAlgorithm() {
  int add = 0;
  int index = 0;
  int auxiliar;
  for (size_t i = index; i < types_of_coins_.size(); i++) {
    auxiliar = (amount_of_coins_ - add) / types_of_coins_[i].value;
    if (auxiliar > 0) {
      for (int j = 0; j < auxiliar; j++) {
        change_coins_.push_back(types_of_coins_[i]);
      }
      add = add + (auxiliar * types_of_coins_[i].value);
    }
  }
}
/**
 * @brief Metodo en el que se declaran 
 * todos los billetes de euro.
 */
void GreedyCoin::includingBill() {
  Coin five_hundred_euro;
  five_hundred_euro.name = "500€";
  five_hundred_euro.value = 50000;
  Coin two_hundred_euro;
  two_hundred_euro.name = "200€";
  two_hundred_euro.value = 20000;
  Coin one_hundred_euro;
  one_hundred_euro.name = "100€";
  one_hundred_euro.value = 10000;
  Coin fifty_euro;
  fifty_euro.name = "50€";
  fifty_euro.value = 5000;
  Coin twenty_euro;
  twenty_euro.name = "20€";
  twenty_euro.value = 2000;
  Coin ten_euro;
  ten_euro.name = "10€";
  ten_euro.value = 1000;
  Coin five_euro;
  five_euro.name = "5€";
  five_euro.value = 500;

  types_of_coins_.insert(types_of_coins_.begin(), five_euro);
  types_of_coins_.insert(types_of_coins_.begin(), ten_euro);
  types_of_coins_.insert(types_of_coins_.begin(), twenty_euro);
  types_of_coins_.insert(types_of_coins_.begin(), fifty_euro);
  types_of_coins_.insert(types_of_coins_.begin(), one_hundred_euro);
  types_of_coins_.insert(types_of_coins_.begin(), two_hundred_euro);
  types_of_coins_.insert(types_of_coins_.begin(), five_hundred_euro);
}

bool GreedyCoin::get_error() {
  return error_;
}