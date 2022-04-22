#include "hwlib.hpp"
#include "test.hpp"
int main() {
    hwlib::wait_ms(1000);
    hwlib::cout << "test\n";

    test();
}