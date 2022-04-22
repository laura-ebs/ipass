#include "write.hpp"

void write::write_bit(){
    //Schrijf 0
        di.write(1);
        hwlib::wait_us(0.4);
        di.write(0);
        hwlib::wait_us(0.85);
        //schrijf 1
        di.write(1);
        hwlib::wait_us(0.8);
        di.write(0);
        hwlib::wait_us(0.45);
}

void write::write_byte(uint8_t bytje){
        for (i=0; i<8; i++){
        hwlib::wait_us(1);

        di.flush();
                }
}

void write::reset(){
        hwlib::wait_us(50);
}