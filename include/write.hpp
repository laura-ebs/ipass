#ifndef HEADERFILE_H
#define HEADERFILE_H

#include "hwlib.hpp"

class write{
    private:
        hwlib::pin_out & di;
    public:
    
    void write_bit();
    void write_byte(uint8_t bytje);
    void reset();
   
    

};

#endif