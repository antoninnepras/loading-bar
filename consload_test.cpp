#include <iostream>
#include <unistd.h>


int main () {
    float val = 0;
    while (val < 1) {
        val += 0.001;
        usleep(100000 * val);
        std::cout << val << std::endl;
    }

    return 0;
}
