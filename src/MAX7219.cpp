#include "MAX7219.hpp"
#include "hwlib.hpp"

unsigned char MAX7219::find_ascii(char ascii_waarde){
    for(unsigned int i=0; sizeof(MAX7219_Font)<i; i++){
          if(MAX7219_Font[i].ascii==ascii_waarde){
               return MAX7219_Font[i].data;
          }       
    }
 }
   
 void MAX7219::write(uint16_t data){
      cs.set(0);
      hwlib::wait_ns(25);
      for (unsigned int i=0; i<16 ;i++){
          if (data>=65536){
               data_in.set(1);
               clock.set(1);
               hwlib::wait_ns(50);
               data_in.set(0);
               clock.set(0);
               hwlib::wait_ns(50);
          }else{
               data_in.set(0); 
               clock.set(1);
               hwlib::wait_ns(50);
               clock.set(0);
          }
        data<<=1;
      }
      cs.set(1);
      hwlib::wait_ns(50);
 }

 void MAX7219::set_intensity(){
     
 }
 void MAX7219::shutdown(){}

 

