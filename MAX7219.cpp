//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#include "MAX7219.hpp"
#include "hwlib.hpp"

font MAX7219_Font[] = {
  {'A',0b1110111},{'B',0b1111111},{'C',0b1001110},{'D',0b1111110},{'E',0b1001111},{'F',0b1000111},       
  {'G',0b1011110},{'H',0b0110111},{'I',0b0110000},{'J',0b0111100},{'L',0b0001110},{'N',0b1110110},       
  {'O',0b1111110},{'P',0b1100111},{'R',0b0000101},{'S',0b1011011},{'T',0b0001111},{'U',0b0111110},       
  {'Y',0b0100111},{'[',0b1001110},{']',0b1111000},{'_',0b0001000},{'a',0b1110111},{'b',0b0011111},       
  {'c',0b0001101},{'d',0b0111101},{'e',0b1001111},{'f',0b1000111},{'g',0b1011110},{'h',0b0010111},       
  {'i',0b0010000},{'j',0b0111100},{'l',0b0001110},{'n',0b0010101},{'o',0b1111110},{'p',0b1100111},       
  {'r',0b0000101},{'s',0b1011011},{'t',0b0001111},{'u',0b0011100},{'y',0b0100111},{'-',0b0000001},
  {' ',0b0000000},{'0',0b1111110},{'1',0b0110000},{'2',0b1101101},{'3',0b1111001},{'4',0b0110011},
  {'5',0b1011011},{'6',0b1011111},{'7',0b1110000},{'8',0b1111111},{'9',0b1111011},{'\0',0b0000000},
  };

uint8_t registers [8] ={DIGIT_7,DIGIT_6,DIGIT_5,DIGIT_4,DIGIT_3,DIGIT_2,DIGIT_1,DIGIT_0};


MAX7219::MAX721z(hwlib::target::pin_out &data_in, hwlib::target::pin_out &cs, hwlib::target::pin_out &clock):
data_in(data_in),
cs(cs),
clock(clock)
{}


unsigned char MAX7219::find_ascii(char ascii_waarde){
    for(unsigned int i=0; sizeof(MAX7219_Font)>i; i++){
          if(MAX7219_Font[i].ascii==ascii_waarde){
               return MAX7219_Font[i].data;       
          }
    }
    return 0b0000000;
 }

 void MAX7219::write(volatile uint8_t adress, volatile uint8_t chardata){
     uint16_t write_data = 0;
     write_data|=adress;
     write_data<<=8;
     write_data|=chardata;
     write(write_data);
 }
   
 void MAX7219::write(volatile uint16_t data){
      cs.write(0);
      hwlib::wait_ns(25);
      unsigned int tmp = 16;
      while(data<32768) { 
        data_in.write(0); 
        clock.write(1);
        hwlib::wait_ns(50);
        clock.write(0);
        data<<=1;
        tmp--;
      }
      for (unsigned int i=0; i<tmp ;i++){
          if (data>=32768){
               data_in.write(1);
               clock.write(1);
               hwlib::wait_ns(50);
               data_in.write(0);
               clock.write(0);
               hwlib::wait_ns(50);
            }else{
               data_in.write(0); 
               clock.write(1);
               hwlib::wait_ns(50);
               clock.write(0);
          }
        data<<=1;
      }
      cs.write(1);
      hwlib::wait_ns(50);
 }

 void MAX7219::set_intensity(unsigned int brighteness){
     uint8_t adress= INTENSITY;
     uint8_t bit = 0b00000000;
     bit|=brighteness;
     bit+=1;
     write(adress,bit);
 }

 void MAX7219::shutdown(){
     uint8_t bit = 0b00000000;
     uint8_t adress= SHUTDOWN;
     write(adress,bit);
    
 }

 void MAX7219::normal_operation(){
     uint8_t bit = 0b11111111;
     uint8_t adress= SHUTDOWN;
     write(adress,bit);
 }

 void MAX7219::scan_limit(unsigned int limit){
     uint8_t adress= SCAN_LIMIT;
     uint8_t bit = 0b00000000;
     bit|=limit;
     write(adress,bit);    
 }

void MAX7219::decode(){
    uint8_t adress= DECODE_MODE;
    uint8_t bit = 0b00000000;
    write (adress,bit);
}

void MAX7219::clear(){
    for(unsigned int i=0; i<sizeof(registers); i++ ){
        write(registers[i],0b00000000);
    }
}

void MAX7219::write_string(hwlib::string <8> string_data){
    for(unsigned int i=0; i<sizeof(registers); i++ ){
        write(registers[i],find_ascii(string_data[i]));
    }
}
 
 void MAX7219::initzialize(){
    scan_limit(7);
    decode();
    normal_operation();
    set_intensity(16); //TODO fix this
 }
    
