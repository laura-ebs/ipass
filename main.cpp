//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#include "hwlib.hpp"
#include "MAX7219.hpp"

int main() {
    hwlib::wait_ms(3000);
    auto max_data_in = hwlib::target::pin_out(hwlib::target::pins::d49);
    auto max_cs = hwlib::target::pin_out(hwlib::target::pins::d51);
    auto max_data = hwlib::target::pin_out(hwlib::target::pins::d53);
    MAX7219 numbers(max_data_in, max_cs, max_data );
    numbers.initzialize();
    numbers.clear();
    hwlib::wait_ms(1000);
    unsigned int tmp = 500;
    //hwlib::string<8> str = "test";
    //numbers.write_string(str, 4);
    numbers.write_int(tmp);
    hwlib::wait_ms(500);
    //numbers.clear();
    //hwlib::wait_ms(500);
    //numbers.write(DIGIT_3, 's');
}