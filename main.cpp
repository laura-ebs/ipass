#include "hwlib.hpp"
#include "MAX7219.hpp"

int main() {
    hwlib::wait_ms(3000);
    auto max_data_in = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto max_cs = hwlib::target::pin_out(hwlib::target::pins::d6);
    auto max_data = hwlib::target::pin_out(hwlib::target::pins::d5);
    MAX7219 numbers(max_data_in, max_cs, max_data );
    numbers.scan_limit(7);
    numbers.decode();
    numbers.normal_operation();
    numbers.write(DISPLAY_TEST, 0);
    numbers.set_intensity(16);
    
    numbers.write(DIGIT_7, numbers.find_ascii('.'));
}