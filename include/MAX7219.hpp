#ifndef MAX7219_HPP
#define MAX7219_HPP

#include "hwlib.hpp"
#include "define.hpp"

// using hwlib::target::pin_out;

struct font
{
    char ascii;
    char data;
};



class MAX7219{
private:
    hwlib::target::pin_out &data_in;
    hwlib::target::pin_out &cs;
    hwlib::target::pin_out &clock;
public:

    MAX7219(hwlib::target::pin_out &data_in, hwlib::target::pin_out &cs, hwlib::target::pin_out &clock);

    void write(uint16_t data);//done
    unsigned char find_ascii(char ascii_waarde);//done
    void set_intensity(int brighteness);
    void shutdown(); //done
    void normal_operation();//done
    void scan_limit();

};


#endif //MAX7219_HPP