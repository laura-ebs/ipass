//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "hwlib.hpp"
#include "MAX7219.hpp"

class game{
private:
    //pins
    hwlib::target::pin_out &leds[5];
    hwlib::target::pin_in &switches[5];
    hwlib::target::pin_in &statistics_switches[4];
    MAX7219 max7219_display(max_data_in, max_cs, max_clock );
    //game
    unsigned int max_game_time = 2500000;
    unsigned int games_played = 0;
    unsigned int current_score = 0;
    unsigned int end_score_game = 0;
    unsigned int scores[512];
    unsigned int highscore_num = 0;
    unsigend int
    void statistics();
    void start_reset();
    void score();
    void highscore();
    bool check();
    void times_played();
public: 

    game(hwlib::target::pin_out &leds[5],hwlib::target::pin_in &switches[5],hwlib::target::pin_in &statistic_switches[4],MAX7219 max7219_display(max_data_in, max_cs, max_clock ));

    void game_it();

};


#endif //APPLICATION_HPP