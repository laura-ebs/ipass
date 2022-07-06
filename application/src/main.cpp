//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#include "../include/application.hpp"
#include "../../library/include/MAX7219.hpp"
#include "hwlib.hpp"

int main(){
    hwlib::wait_ms(3000);
    //pins MAX7219
    auto max_data_in = hwlib::target::pin_out(hwlib::target::pins::d49);
    auto max_cs = hwlib::target::pin_out(hwlib::target::pins::d51);
    auto max_clock = hwlib::target::pin_out(hwlib::target::pins::d53);
    //pins leds
    auto LED_0 = hwlib::target::pin_out(hwlib::target::pins::d14);
    auto LED_1 = hwlib::target::pin_out(hwlib::target::pins::d3);
    auto LED_2 = hwlib::target::pin_out(hwlib::target::pins::d5);
    auto LED_3 = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto LED_4 = hwlib::target::pin_out(hwlib::target::pins::d9);
    //pins switches
    auto SWITCH_0 = hwlib::target::pin_in(hwlib::target::pins::d15);
    auto SWITCH_1 = hwlib::target::pin_in(hwlib::target::pins::d2);
    auto SWITCH_2 = hwlib::target::pin_in(hwlib::target::pins::d4);
    auto SWITCH_3 = hwlib::target::pin_in(hwlib::target::pins::d6);
    auto SWITCH_4 = hwlib::target::pin_in(hwlib::target::pins::d8);
    auto SWITCH_START_RESET = hwlib::target::pin_in(hwlib::target::pins::d10);
    auto SWITCH_HIGHSCORE = hwlib::target::pin_in(hwlib::target::pins::d11);
    auto SWITCH_TIMES_PLAYED = hwlib::target::pin_in(hwlib::target::pins::d12);
    auto SWITCH_REACTION_TIME = hwlib::target::pin_in(hwlib::target::pins::d13);

    MAX7219 display(max_data_in, max_cs, max_clock);
    //array for switches with statistics
    MenuSwitches menu_switches = {SWITCH_START_RESET,SWITCH_HIGHSCORE ,SWITCH_TIMES_PLAYED, SWITCH_REACTION_TIME};
    //arrays for switches game and leds.
    auto leds = hwlib::port_out_from(LED_0,LED_1,LED_2,LED_3,LED_4);
    auto switches = hwlib::port_in_from(SWITCH_0, SWITCH_1, SWITCH_2, SWITCH_3, SWITCH_4);

    //constuctor game
    game game1(leds,switches, menu_switches, display);

    game1.run();
}