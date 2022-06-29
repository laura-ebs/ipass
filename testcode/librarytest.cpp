//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#include "hwlib.hpp"
#include "MAX7219.hpp"

void test_intensity(MAX7219 numbers){
    hwlib::cout<<"You will see the intensity gradually getting brighter"<<hwlib::endl;
    numbers.initzialize();
    numbers.clear();
    hwlib::wait_ms(300);
    unsigned int brightness =1;
    numbers.write_string(hwlib::string<8>("IPASS"),5);
    for (unsigned int i=0; i<15; i++){
        hwlib::wait_ms(400);
        numbers.set_intensity(brightness);
        brightness+=1;
    }
}

void test_write(MAX7219 numbers){
    hwlib::cout<<"You will see an A appear will apear on the 5th digit"<<hwlib::endl;
    numbers.initzialize();
    numbers.clear();
    numbers.set_intensity(4);
    hwlib::wait_ms(300);
    numbers.write(DIGIT_3, numbers.find_ascii('A'));
}

void test_write_string(MAX7219 numbers){
    hwlib::cout<<"You will see HELLO apear on the display"<<hwlib::endl;
    numbers.initzialize();
    numbers.clear();
    numbers.set_intensity(4);
    hwlib::wait_ms(300);
    numbers.write_string(hwlib::string<8>("HELLO"),5);

}

void test_write_char(MAX7219 numbers){
    hwlib::cout<<"You will see 8.450 appear on the display"<<hwlib::endl;
    numbers.initzialize();
    numbers.clear();
    numbers.set_intensity(4);
    hwlib::wait_ms(300);
    numbers.write_char(DIGIT_7, '8', 1);
    numbers.write_char(DIGIT_6, '4');
    numbers.write_char(DIGIT_5, '5');
    numbers.write_char(DIGIT_4, '0');
}

void test_clear(MAX7219 numbers){
    hwlib::cout<<"You will first see ARDUINO apear on the display and then see the display clear "<<hwlib::endl;
    numbers.initzialize();
    numbers.clear();
    numbers.set_intensity(4);
    hwlib::wait_ms(300);                   
    numbers.write_string(hwlib::string<8>("ARDUINO"),7);
    hwlib::wait_ms(5000);
    numbers.clear();
}

void test_shutdown_and_initzialize(MAX7219 numbers){
    hwlib::cout<<"You will first SLEEP apear on the display and then display will shutdown then it will initzialize and you will see 800"<<hwlib::endl;
    numbers.initzialize();
    numbers.clear();
    numbers.set_intensity(4);
    hwlib::wait_ms(300);                   
    numbers.write_string(hwlib::string<8>("SLEEP"),5);
    hwlib::wait_ms(5000);
    numbers.shutdown();
    hwlib::wait_ms(2000);
    numbers.initzialize();
    numbers.clear();
    numbers.set_intensity(4);
    numbers.write_string(hwlib::string<8>("800"),3);
}



int main(){
    hwlib::wait_ms(3000);
    auto max_data_in = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto max_cs = hwlib::target::pin_out(hwlib::target::pins::d6);
    auto max_data = hwlib::target::pin_out(hwlib::target::pins::d5);
    MAX7219 numbers(max_data_in, max_cs, max_data );
    
    test_write(numbers);

    hwlib::wait_ms(2000);
    test_write_char(numbers);
    
    hwlib::wait_ms(2000);
    test_write_string(numbers);
    
    hwlib::wait_ms(2000);
    test_intensity(numbers);

    hwlib::wait_ms(2000);
    test_clear(numbers);

    hwlib::wait_ms(2000);
    test_shutdown_and_initzialize(numbers);
}