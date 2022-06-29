//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#ifndef DEFINE_HPP
#define DEFINE_HPP

//define address
#define NO_OP 0x0
#define DIGIT_0 0x1
#define DIGIT_1 0x2
#define DIGIT_2 0x3
#define DIGIT_3 0x4
#define DIGIT_4 0x5
#define DIGIT_5 0x6
#define DIGIT_6 0x7
#define DIGIT_7 0x8
#define DECODE_MODE 0x9
#define INTENSITY 0xA
#define SCAN_LIMIT 0xB
#define SHUTDOWN 0xC 
#define DISPLAY_TEST 0xF

//define pins MAX7219
#define MAX_DATA_IN hwlib::target::pins::d7
#define MAX_CS hwlib::target::pins::d6
#define MAX_DATA hwlib::target::pins::d5

// define pins aplication
#define LED_0 
#define LED_1
#define LED_2
#define LED_3
#define LED_4
#define LED_5
#define SWITCH_0
#define SWITCH_1
#define SWITCH_2
#define SWITCH_3
#define SWITCH_4
#define SWITCH_5


#endif //DEFINE_HPP