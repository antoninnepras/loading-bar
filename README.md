# LOADING BAR in C++

loading.hpp contains two functions:

- void loading (std::string name, double* value)
- void loading_multiple (std::string<Loading_tag> tags)

and one struct

- Loading_tag {std::string name, double* value}

values are in range <0;1>

Loading bars stops, when values are greater than 1.

Loading estimates remaining time based on percentage and time taken from start.

![](loading.gif)

### TEST
Test can be compiled with:

 ```
make test
```

execute:
```
./test
```

## CONSOLE LOAD
program loads doubles from stdin and displays them in loading bar

![](cons_load.gif)

### options
| flag |option |
| -------|----------- | 
|-h \--help | displays help |
|-c \--color n| change color |

|n|color|
|-|-|
|0|black|
|1|red|
|2|green|
|3|yellow|
|4|blue|
|5|violet|
|6|cyan|
|7|gray|
|8|white|

### use
```
program_outputing_values | consload -c [color]
```

### compile
``` 
cd loading-bar
make
```

### install
```
sudo make install
```

### uninstall
```
sudo make uninstall
```


