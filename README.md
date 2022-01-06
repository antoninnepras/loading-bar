# LOADING BAR in C++

loading.hpp contains two functions:

- void loading (std::string name, double* value)
- void loading_multiple (std::string<Loading_tag> tags)

and one struct

- Loading_tag {std::string name, double* value}

values are in range <0;1>

Loading bars stops, when values are greater than 1.

Loading estimates remaining time based on percentage and time taken from start.

![test program](loading.gif)

## TEST
Test can be compiled with:

 > g++ main.cpp -o main

