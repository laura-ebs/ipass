#ifndef MAX7219_HPP
#define MAX7219_HPP

#include "hwlib.hpp"
#include "define.hpp"

// using hwlib::target::pin_out;

struct font{
    char ascii;
    char data;
};


class MAX7219{
private:
    hwlib::target::pin_out &data_in;
    hwlib::target::pin_out &cs;
    hwlib::target::pin_out &clock;
    unsigned int limit=0;
public:

    MAX7219(hwlib::target::pin_out &data_in, hwlib::target::pin_out &cs, hwlib::target::pin_out &clock);

    void write(volatile uint16_t data);
    unsigned char find_ascii(char ascii_waarde);
    void write(volatile uint8_t adress, volatile uint8_t chardata);
    void set_intensity(unsigned int brighteness);
    void shutdown(); 
    void normal_operation();
    void scan_limit(unsigned int limit);
    void decode();
    
};


#endif //MAX7219_HPP