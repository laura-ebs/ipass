#include "MAX7219.hpp"
#include "hwlib.hpp"

char MAX7219::find_ascii(char ascii_waarde){
    for(unsigned int i=0; sizeof(MAX7219_Font)<i; i++){
          if(MAX7219_Font[i].ascii==ascii_waarde){
               return MAX7219_Font[i].data;
          }       
    }
 }
   
 void MAX7219::write(uint8_t adress, uint8_t data){
      uint16_t write_data= adress+data;
      cs.set(0);
      clock.set(1);
      hwlib::wait_ms(200);
      data_in.set(write_data);
      hwlib::wait_ms(200);
      clock.set(0);
      cs.set(1);
 }

 void MAX7219::set_intensity(){
     
 }
 void MAX7219::shutdown(){}

 

