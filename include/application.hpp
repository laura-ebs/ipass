//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "hwlib.hpp"
#include "MAX7219.hpp"

struct StatisticsSwitches{
    hwlib::target::pin_in& SWITCH_START_RESET;
    hwlib::target::pin_in& SWITCH_HIGHSCORE;
    hwlib::target::pin_in& SWITCH_TIMES_PLAYED;
    hwlib::target::pin_in& SWITCH_REACTION_TIME;
};

class game{
private:
    enum state{
        START_PAGE,
        HIGHSCORE_PAGE,
        REACTION_TIME_PAGE,
        TIMES_PLAYED_PAGE,
        GAME
    };

    //pins
    hwlib::port_out& leds;
    hwlib::port_in& switches;
    StatisticsSwitches statistics_switches;
    MAX7219 &display;

    //game
    state current_state;
    unsigned int max_game_time = 2500000;
    unsigned int games_played = 0;
    unsigned int current_score = 0;
    unsigned int end_score_game = 0;
    unsigned int scores[512];
    unsigned int highscore_num = 0;
    unsigned int menu_text = 0;
    uint_fast64_t menu_update_time = 0;
    void start_reset();
    void score();
    void show_highscore();
    bool check();
    void show_times_played();
    void game_it();
    void show_menu();
    void check_menu_buttons();
    void average_reaction_time();

public: 

    game(hwlib::port_out& leds, hwlib::port_in& switches, StatisticsSwitches statistics_switches, MAX7219 &display);

    void run();
};


#endif //APPLICATION_HPP