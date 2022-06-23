#include "hwlib.hpp"
#include "MAX7219.hpp"

int main() {
    auto max_data_in = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto max_cs = hwlib::target::pin_out(hwlib::target::pins::d6);
    auto max_data = hwlib::target::pin_out(hwlib::target::pins::d5);
    MAX7219 numbers(max_data_in, max_cs, max_data );
    numbers.normal_operation();
}