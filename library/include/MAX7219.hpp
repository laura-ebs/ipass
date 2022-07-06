//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.


#ifndef MAX7219_HPP
#define MAX7219_HPP

#include "hwlib.hpp"
#include "define.hpp"


/**
 * @brief 
 * This struct contains the font which is made out of unsigned char for the font_char and a uint8_t for the font_binary.
 * @param font_char
 * The char you want the font of.
 * @param font_binary
 * The font data you want in uint8_t.
 */
struct font{
    unsigned char font_char;
    uint8_t font_binary;
};

/**
 * @brief 
 * This is the class of the MAX7219.
 */
class MAX7219{
private:
    /**
     * @brief 
     * hwlib pin_out object refrence to the data_in pin.
     */
    hwlib::target::pin_out &data_in;

    /**
     * @brief 
     * hwlib pin_out object refrence to the cs pin.
     */
    hwlib::target::pin_out &cs;

    /**
     * @brief 
     * hwlib pin_out object refrence to the clock pin.
     */
    hwlib::target::pin_out &clock;

    /**
     * @brief 
     * The limit contains current amount of maximum digits.
     */
    unsigned int limit = 0;

    /**
     * @brief 
     * This function will convert an integer to a unsigned char.
     * @param input_int
     * The input_int contains the integer you want to convert.
     * @param buffer 
     * The buffer contains the converted unsigned chars.
     * @param buffer_length 
     * The buffer_length contains the length of the buffer.
     */
    void convert_int_to_char(unsigned int input_int, unsigned char* buffer, unsigned int buffer_length);

    /**
     * @brief 
     * This function will determine how many digits an int contains.
     * @param input_int 
     * The input_int contains the integer you want to know the count of digits of.
     * @return unsigned int 
     * Retruns the length of the integer.
     */
    unsigned int  check_length_int(unsigned int input_int);

    /**
     * @brief 
     * This function will find the binary that belongs to the unsigned char you want to write to the MAX7219.
     * @param input_char 
     * The input_char contains the unsingned char that you are trying to find the binary of.
     * @return uint8_t
     * Returns the font_binary that belongs to the input_char.
     */
    uint8_t get_font_binary(unsigned char input_char);

public:
    /**
     * @brief Construct a new MAX7219 object
     * 
     * @param data_in 
     * hwlib pin_out object refrence to the data_in pin.
     * @param cs 
     * hwlib pin_out object refrence to the cs pin.
     * @param clock
     * hwlib pin_out object refrence to the clock pin. 
     */
    MAX7219(hwlib::target::pin_out &data_in, hwlib::target::pin_out &cs, hwlib::target::pin_out &clock);

    /**
     * @brief 
     * This function writes 16 bits to the MAX7219.
     * @param data 
     * The data exists out of 2 bytes the 8 most significant bits are the adress,
     * the 8 least significant bits are the charactars.
     */
    void write(uint16_t data);

    /**
     * @brief 
     * * This function writes two 8 bits to the MAX7219.
     * @param adress
     * The adress contains the adress you want to write the char to.
     * @param chardata 
     * The chardata contains the font_binary of the char you want write to the adress
     */

    void write(uint8_t adress, uint8_t chardata);

    /**
     * @brief 
     * This function writes 8 bits(adress) and a char to the MAX7219.
     * @param adress 
     * The adress contains the adress you want to write the input_char to.
     * @param input_char
     * The input_char contains the char you want write to the adress
     * @param dot
     * The dot contains whether you want to write a dot or not.
     */
    void write_char(uint8_t adress, unsigned char input_char, bool dot =false );

    /**
     * @brief 
     * This functinon writes a int to the MAX7219 display.
     * @param input_int 
     * The input_int contains the int you want to write.
     */
    void write_int(unsigned int input_int);

    /**
     * @brief 
     * This function writes a string to the MAX7219 display.
     * @param string_data 
     * The string_data contains the string you want to write 
     * @param length 
     * The length contains the length of the string.
     */
    void write_string(hwlib::string <8> string_data, unsigned int length);

     /**
     * @brief 
     * This will clear the  display of the MAX7219.
     */
    void clear();

    /**
     * @brief 
     * This function will set the intensity of the MAX2719
     * @param brightness 
     * The brightness contains the intensity you want to have on the MAX7219. Minimum 0 and maximum 16.
     */
    void set_intensity(unsigned int brightness);

    /**
     * @brief 
     * This function will shutdown the MAX7219
     */
    void shutdown(); 

    /**
     * @brief 
     * This function will start the MAX7219.
     */
    void normal_operation();

    /**
     * @brief 
     * This function will set the limit of chars you can display with the MAX2719. 
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
     *This function initializes the MAX7219 so you can write to it.
     */
    void initialize();
    
};


#endif //MAX7219_HPP