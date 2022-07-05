//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.


#ifndef MAX7219_HPP
#define MAX7219_HPP

#include "hwlib.hpp"
#include "define.hpp"


/**
 * @brief 
 * This struct contains a ascii to save for the chars and data for the binary that belongs to the ascii.
 */
struct font{
    unsigned char ascii;
    uint8_t data;
};

/**
 * @brief 
 * This is the class of the MAX7219.
 */
class MAX7219{
private:
    /**
     * @brief 
     *  hwlib pin_out object refrence to the data_in pin.
     */
    hwlib::target::pin_out &data_in;

    /**
     * @brief 
     *  hwlib pin_out object refrence to the cs pin.
     */
    hwlib::target::pin_out &cs;

    /**
     * @brief 
     *  hwlib pin_out object refrence to the clock pin.
     */
    hwlib::target::pin_out &clock;

    /**
     * @brief 
     * The current amount of maximum digits.
     */
    unsigned int limit=0;


    void convert_int_to_char(unsigned int input_int, unsigned char* buffer, unsigned int buffer_length);
    unsigned int  check_lenght_int(unsigned int input_int);

    /**
     * @brief 
     * This function will find the binary that belongs to the char you wanna write to the MAX7219.
     * @param ascii_waarde 
     * the char that you are try to find.
     * @return uint8_t
     * The binary data that belongs to the char.
     */
    uint8_t find_ascii(unsigned char ascii_waarde);

public:
    /**
     * @brief Construct a new MAX7219 object
     * 
     * @param data_in 
     * hwlib pin_out object refrence to the data_in pin.
     * @param cs 
     *  hwlib pin_out object refrence to the cs pin.
     * @param clock
     *  hwlib pin_out object refrence to the clock pin. 
     */
    MAX7219(hwlib::target::pin_out &data_in, hwlib::target::pin_out &cs, hwlib::target::pin_out &clock);

    /**
     * @brief 
     * This function writes 16 bits to the MAX7219.
     * @param data 
     * the data exists out of 2 bytes the 8 most significant are the adress ,
     * the 8 least significant are the charactars.
     */
    void write(uint16_t data);


    /**
     * @brief 
     * This function writes 8 bits(adress) and a char to the MAX7219.
     * @param adress 
     * The adress you want to write the char to.
     * @param ascii_1
     * The ascii you want write to the adress
     * @param dot
     * If you want to write a dot or not.
     */
    void write_char(uint8_t adress, unsigned char ascii_1, bool dot =false );

    /**
     * @brief 
     * * This function writes two 8 bits to the MAX7219.
     * @param adress
     * The adress you want to write the char to.
     * @param chardata 
     * The char you want write to the adress
     */
    void write(uint8_t adress, uint8_t chardata);

    void write_int(unsigned int input_int);

    /**
     * @brief 
     * Set the intensity of the MAX2719
     * @param brighteness 
     * The intensity you want to have the MAX2791 to 16;
     */
    void set_intensity(unsigned int brighteness);

    /**
     * @brief 
     * This function will shutdown the MAX7219
     */
    void shutdown(); 

    /**
     * @brief 
     * This will start the MAX7219.
     */
    void normal_operation();

    /**
     * @brief 
     * This will set the limit of chars you can display with the MAX2719. 
     * @param limit 
     * The limit you want to write to the MAX7219. Minimum 0 and maximum 7.
     */
    void scan_limit(unsigned int limit);

    /**
     * @brief 
     * This function enables no decode.
     */
    void decode();

    /**
     * @brief 
     * This will clear the  display of the MAX7219.
     */
    void clear();
    
    /**
     * @brief 
     * This function writes string to the MAX7219 display.
     * @param string_data 
     * The string contains the chars you want to write 
     * @param lenght 
     * Contains the lenght of the string.
     */
    void write_string(hwlib::string <8> string_data, unsigned int lenght);

    /**
     * @brief 
     *This function initzializes the MAX7219 so you can write to it.
     */
    void initzialize();
    
};


#endif //MAX7219_HPP