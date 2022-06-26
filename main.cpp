//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#include "hwlib.hpp"
#include "MAX7219.hpp"

int main() {
    hwlib::wait_ms(3000);
    auto max_data_in = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto max_cs = hwlib::target::pin_out(hwlib::target::pins::d6);
    auto max_data = hwlib::target::pin_out(hwlib::target::pins::d5);
    MAX7219 numbers(max_data_in, max_cs, max_data );
    numbers.initzialize();
    numbers.clear();
    hwlib::wait_ms(3000);
    numbers.write_string(hwlib::string<5>("HELLO"));
}