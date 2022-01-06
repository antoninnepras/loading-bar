/**
 * @file loading.hpp
 * @author Antonin Nepras
 * @brief Loading bars for terminal
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef loading_hpp
#define loading_hpp

#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <vector>
#include <iomanip>
#include <sys/ioctl.h>

/**
 * @brief displays loading bar on stdout in full width of the terminal
 * 
 * @param name name of the loading bar
 * @param value value reference for the loading bar
 */
void loading (std::string name, double* value) {
  using namespace std::chrono;
  int use_segments = 0;
  std::string segs[9] = {" ", "▏", "▍", "▍", "▌", "▋", "▊", "▉", "█"};
  auto start = high_resolution_clock::now();
  int est = 0;
  int segments = 30;

  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  do {
    ioctl(0, TIOCGWINSZ, &w);
    use_segments = segments * *value;
    std::cout << name << ": |";
    
    segments = w.ws_col - name.length() - 4 - 14 - 4;
    
    for (int i = 0; i < segments; i++) {
      if (i < use_segments) {
        std::cout << segs[8];
      } else if (i == use_segments) {
        float tmp = (*value * segments - use_segments);
        std::cout << segs[(int)(tmp * 8)];
      } else {
        std::cout << segs[0];
      }
    }
    
    std::cout << "| " << std::setw(3) << (int)(*value*100) << "% ";

    auto now = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(now - start);

    duration.count();
    est = (duration.count() / *value - duration.count())/1000000;

    std::cout << "[EST:" << std::setw(3);
    if (est < 180) {
      std::cout << est << "s";
    } else if (est < 180 * 60) {
      std::cout << (int)((float)est/60) << "m";
    } else if (est < 72 * 60 * 60) {
      std::cout << (int)((float)est/3600) << "h";
    } else {
      std::cout << (int)((float)est/(3600*24)) << "d";
    } 
    std::cout << "] \n";

    
    usleep(100000);
    std::cout << "\e[A\e[K";
  }
  while (*value < 1);
}


/**
 * @brief data for one loading bar
 * 
 */
struct Loading_tag {
  std::string name;
  double* value;
};


/**
 * @brief displays loading bars on stdout in full width of the terminal
 * 
 * @param tags data for loading bars
 */
void loading_multiple (std::vector<Loading_tag> tags) {
  using namespace std::chrono;
  int name_area_length = 0;
  for (auto i : tags) {
    if (i.name.length() > name_area_length) {
      name_area_length = i.name.length();
    }
  }

  int segments = 30;

  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  int est = 0;
  int use_segments = 0;
  bool done = false;
  std::string segs[9] = {" ", "▏", "▍", "▍", "▌", "▋", "▊", "▉", "█"};
  

  auto start = high_resolution_clock::now();

  while (!done) {
    done = true;
    for (auto tag : tags) {
      if (*tag.value < 1){
        done = false;
        break;
      }
    }

    for (auto tag : tags) {
      ioctl(0, TIOCGWINSZ, &w);
      auto now = high_resolution_clock::now();
      auto duration = duration_cast<microseconds>(now - start);
      duration.count();
      est = (duration.count() / *tag.value - duration.count())/1000000;

      segments = w.ws_col - name_area_length - 4 - 14 - 4;

      std::cout << tag.name;
      for (int i = 0; i < name_area_length - tag.name.length(); i++) {
        std::cout << " ";
      }

      std::cout << " : |";

      use_segments = segments * *tag.value;

      for (int i = 0; i < segments; i++) {
        if (i < use_segments) {
          std::cout << segs[8];
        } else if (i == use_segments) {
          float tmp = (*tag.value * segments - use_segments);
          std::cout << segs[(int)(tmp * 8)];
        } else {
          std::cout << segs[0];
        }
      }
    
      std::cout << "| " <<  std::setw(3) << (int)(*tag.value*100) << "% ";

      std::cout << "[EST:" << std::setw(3);
      if (est < 180) {
        std::cout << est << "s";
      } else if (est < 180 * 60) {
        std::cout << (int)((float)est/60) << "m";
      } else if (est < 72 * 60 * 60) {
        std::cout << (int)((float)est/3600) << "h";
      } else {
        std::cout << (int)((float)est/(3600*24)) << "d";
      } 
      std::cout << "]";

      std::cout << "\n";
    }

    if (!done) {
      usleep(10000);

      for (auto tag : tags) {
        std::cout << "\e[A\e[K";
      }
    }
  }
}


#endif
