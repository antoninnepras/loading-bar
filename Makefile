cxx = g++
flags = -g -Wall -Werror
target = consload

all: console_loading.cpp loading.hpp
	$(cxx) $(flags) console_loading.cpp -o $(target)

test: test.cpp loading.hpp
	$(cxx) $(flags) test.cpp -o test

consload_test: all consload_test.cpp
	$(cxx) $(flags) consload_test.cpp -o consload_test


install: all
	cp $(target) /usr/bin/

uninstall:
	rm /usr/bin/$(target)
