#ifndef HEADERFILE_H
#define HEADERFILE_H

#include "hwlib.hpp"
#include "write.hpp"


class grb{
    private:
    // Variables to save the colors
        uint8_t green;
        uint8_t red;
        uint8_t blue;
    public:
    // constructor for the rgb colors
        grb(uint8_t green, uint8_t red, uint8_t blue);
           
};
#endif