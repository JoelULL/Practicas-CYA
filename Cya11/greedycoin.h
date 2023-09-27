/**
 * @file greedycoin.h
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Computabilidad y algoritmia
 * Curso: 2º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Archivo de cabecera de la clase greedycoin.h. En este
 * archivo se define la clase que permitira ejecutar el algoritmo de
 * obtecion de cambio voraz. A parte de otra forma del algoritmo con orden
 * de complejidad 0(m).
 * @version 0.1
 * @date 2022-12-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "libraries.h"

#define cross_symbol "x"
/**
 * @brief Estructura para representar la
 * moneda del euro.
 */
struct Coin {
  int value; // valor en centimos de la moneda
  std::string name; // nombre de la moneda
};

class GreedyCoin {
  private:
    std::vector<Coin> types_of_coins_; // tipos de monedas 
    std::vector<Coin> change_coins_; // monedas utilizadas en el cambio
    int amount_of_coins_; // cantidad de monedas utilizadas
    std::vector<std::string> result_; // vector para mostrar el resultado mas elaborado
    bool error_; // variable de error
  public:
    GreedyCoin();
    GreedyCoin(std::string user_coin_value);
    ~GreedyCoin();

    void availableCoins();
    void CoinChangeAlgorithm();
    void simpleShowResult();
    void additionalShowResult();
    int howManyTimes(std::string coin_name, int index);
    void additionalAlgorithm();
    void includingBill();
    bool get_error();
};