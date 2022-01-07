/**
 * @file main.cpp
 * @author Antonin Nepras
 * @brief Loading bars test
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include "loading.hpp"

int main () {
  double value1 = 0;
  double value2 = 0;

  std::cout << "\e[33m";

  std::vector<Loading_tag> loading_tags;
  Loading_tag t1;
  t1.name = "proc1";
  t1.value = &value1;

  Loading_tag t2;
  t2.name = "procces2";
  t2.value = &value2;
  loading_tags.push_back(t1);
  loading_tags.push_back(t2);

  std::thread th1(&loading_multiple, loading_tags);
  
  while (value1 < 1 || value2 < 1) {
    if (value1 < 1) {
      value1 += 0.000002;
    }

    if (value2 < 1) {
      value2 += 0.00002;

    }

    usleep(1000);
  }
  
  th1.join();
  std::cout << "\e[0m";

  return 0;
}
