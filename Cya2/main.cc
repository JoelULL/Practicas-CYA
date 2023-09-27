#include "filefunctions.h"
#include "language.h"

#define opcodemax 6
#define opcodemin 1

int main(int argc, char* argv[])
{
  int opcode = std::stoi(argv[1]);
  if (opcode < opcodemin || opcode > opcodemax) {
    std::cout << "inserte un numero entre 1 y 6";
    return 1;
  }
  std::string line;
  std::string line2;
  std::string outputresult = "";
  bool error = false;
  if (opcode == 5 || opcode == 6) {
    Language readlanguage;
      //fichero de entrada
      std::ifstream myfile;
      myfile.open(argv[2]);

    if(!myfile.is_open()) {
      perror("Error open");
      exit(EXIT_FAILURE);
    } 
    //fichero de salida
    std::ofstream outputfile;
    outputfile.open(argv[3], std::ios::out);
    if(!outputfile.is_open()) {
      perror("Error open");
      exit(EXIT_FAILURE);
  }
  while(std::getline(myfile, line)) {
    filelanguage(line, readlanguage, error);
    Language result;
    if (!error) {
      switch(opcode) {
        case 5: {
          Language empty;
          result = readlanguage.languageInversed();
          outputresult = result.showResults();
          readlanguage = empty;
          break;
        }
        case 6: {
          int pwr = 0;
          Language empty;
            std::cout << "Ingrese una potencia: ";
            std::cin >> pwr;
            if(pwr == 0) {
              outputresult = "{ & }";
            }
            else {
            result = readlanguage.stringspowers(pwr);
            outputresult = result.showResults();
            readlanguage = empty;
            }
            break;
        }
      }
      outputfile << outputresult << "\n";
    }
    else
      outputfile << "Lenguaje incorrecto";
  }
  myfile.close();
  outputfile.close();
  } else {
    //fichero de entrada 1
    std::ifstream myfile;
    myfile.open(argv[2]);

    if(!myfile.is_open()) {
      perror("Error open");
      exit(EXIT_FAILURE);
    } 
    //fichero de entrada 2
    std::ifstream myfile2;
    myfile2.open(argv[3]);

    if(!myfile2.is_open()) {
      perror("Error open");
      exit(EXIT_FAILURE);
    }
    //fichero de salida
    std::ofstream outputfile;
    outputfile.open(argv[4], std::ios::out);
    if(!outputfile.is_open()) {
      perror("Error open");
      exit(EXIT_FAILURE); 
  }
  
  Language file1lgs;
  Language file2lgs;
  Language empty;

  std::vector<Language> file1content;
  std::vector<Language> file2content;

  int file1lines = 0;
  int file2lines = 0;

  while(std::getline(myfile, line)) {
    filelanguage(line, file1lgs, error);
    if (!error) {
      file1content.push_back(file1lgs);
      file1lgs = empty;
    }
    else {
      outputfile << "Lenguaje incorrecto";
    }
    ++file1lines;
  }
  while(std::getline(myfile2, line2)) {
    filelanguage(line2, file2lgs, error);
    if (!error) {
    file2content.push_back(file2lgs);
    file2lgs = empty;
    }
    else {
      outputfile << "Lenguaje incorrecto detectado";
    }
    ++file2lines;
  }
  if (file1lines != file2lines) {
    std::cout << "los archivos deben tener el mismo numero de lineas\n";
  }

  switch(opcode) {
    case 1: {
      Language result;
      for (size_t i = 0; i < file1content.size(); i++) {
        result = file1content[i].languagesConcatenation(file2content[i]);
        outputresult = result.showResults();
        outputfile << outputresult;
        outputfile << "\n";
        result = empty;
        outputresult = "";
      }
      break;
    }
    case 2: {

      Language result;
      Alphabet lg1;
      Alphabet lg2;
      
      for (size_t i = 0; i < file1content.size(); i++) {
        lg1 = file1content[i].get_language_alphabet();
        lg2 = file2content[i].get_language_alphabet();
        result = file1content[i].languagesUnion(file2content[i]);
        outputresult = result.showResults();
        if (lg1 == lg2)
          outputfile << outputresult;
        else
          outputfile << "Los alfabetos deben ser iguales";
        outputfile << "\n";
        result = empty;
        outputresult = "";
      }
      break;
    }
    case 3: {
   
      Language result;
      Alphabet lg1;
      Alphabet lg2;
      
      for (size_t i = 0; i < file1content.size(); i++) {
        lg1 = file1content[i].get_language_alphabet();
        lg2 = file2content[i].get_language_alphabet();
        result = file1content[i].languagesIntersection(file2content[i]);
        outputresult = result.showResults();
        if (lg1 == lg2)
          outputfile << outputresult;
        else
          outputfile << "Los alfabetos deben ser iguales";
        outputfile << "\n";
        result = empty;
        outputresult = "";
      }
      break;   
    }
    case 4: {

      Language result;
      Alphabet lg1;
      Alphabet lg2;
      
      for (size_t i = 0; i < file1content.size(); i++) {
        lg1 = file1content[i].get_language_alphabet();
        lg2 = file2content[i].get_language_alphabet();
        result = file1content[i].languagesDifference(file2content[i]);
        outputresult = result.showResults();
        if (lg1 == lg2)
          outputfile << outputresult;
        else
          outputfile << "Los alfabetos deben ser iguales";
        outputfile << "\n";
        result = empty;
        outputresult = "";
      }
      break;    
    }
  }


  /*debug
  std::cout << "El contenido del primer archivo es: \n";
  for (size_t i = 0; i < file1content.size(); i++) {
      file1content[i].showMyLanguage();
  }
  std::cout << "\nEl contenido del segundo archivo es: \n";
    for (size_t i = 0; i < file2content.size(); i++) {
      file2content[i].showMyLanguage();
  }
  std::cout << "\n";
*/
  myfile.close();
  myfile2.close();
  outputfile.close();
  }

  return 0;
}