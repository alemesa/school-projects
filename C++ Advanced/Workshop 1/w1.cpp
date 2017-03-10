/*
OOP345
Workshop 1
Title    : From One Translation Unit to Another
Date     : 02/28/17

Author   : Alejandro Mesa
Student# : 038515151
Email    : amesasuarez@myseneca.ca
*/

#include <iostream>
#include "process.h"
#include "CString.h"

using namespace w1;

int main(int argc, char* argv[])
{
  if(argc<=1) {
    std::cout << "Insufficient number of arguments (min 1)" << std::endl;
    return 1;
  }
  std::cout << "Maximum number of characters stored : " << MAX << std::endl;
  int n=1;
  while(n<argc) {
    process(argv[n++]);
  }
  return 0;
}
