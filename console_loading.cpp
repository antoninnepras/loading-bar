#include "loading.hpp"
#include <iostream>

void display_help (void);

int main (int argc, char* argv[]) {
  int color = 9;
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
        display_help();
        return 0;
      } else if (std::string(argv[i]) == "-c" || 
          std::string(argv[i]) == "--color") {
        if (i + 1 == argc) {
          std::cerr << "Error missing color argument\n";
          return 1;
        }
        color = std::atoi(argv[i + 1]);
      }
    }
  }

  double value = 0;
  std::cout << "\e[3"<< std::to_string(color) <<"m";
  std::thread th1(&loading, "out", &value);
  
  while (value < 1) {
    std::cin >> value;
    usleep(10);
  }
  
  th1.join();

  //reset color
  std::cout << "\e[0m";

  return 0;
}


void display_help (void) {
  std::cout 
      << "Program displays loading bar\n"
      << "it takes floating point from stdin <0.0-1.0>\n"
      << "takes input after std::endl\n"
      << "exits when input exceeds 1.0\n"
      << "-h, --help dispay this help\n"
      << "-c, --color [0-8] changes color of the loading bar\n"
      << "     \e[30m0 - black\n"
      << "     \e[31m1 - red \n"
      << "     \e[32m2 - green \n"
      << "     \e[33m3 - yellow \n"
      << "     \e[34m4 - blue \n"
      << "     \e[35m5 - violet \n"
      << "     \e[36m6 - cyan \n"
      << "     \e[37m7 - gray \n"
      << "     \e[38m8 - white \e[0m\n";
}
