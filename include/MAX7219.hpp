//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.


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

    /**
     * @brief 
     * 
     * @param data 
     */
    void write(volatile uint16_t data);

    /**
     * @brief 
     * 
     * @param ascii_waarde 
     * @return unsigned char 
     */
    unsigned char find_ascii(char ascii_waarde);

    /**
     * @brief 
     * 
     * @param adress 
     * @param chardata 
     */
    void write(volatile uint8_t adress, volatile uint8_t chardata);

    /**
     * @brief Set the intensity object
     * 
     * @param brighteness 
     */
    void set_intensity(unsigned int brighteness);

    /**
     * @brief 
     * 
     */
    void shutdown(); 

    /**
     * @brief 
     * 
     */
    void normal_operation();

    /**
     * @brief 
     * 
     * @param limit 
     */
    void scan_limit(unsigned int limit);

    /**
     * @brief 
     * 
     */
    void decode();

    /**
     * @brief 
     * 
     */

    void clear();
    /**
     * @brief 
     * 
     * @param string_data 
     */
    void write_string(hwlib::string <8> string_data);

    void initzialize();
    
};


#endif //MAX7219_HPP