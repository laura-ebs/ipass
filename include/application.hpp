//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "hwlib.hpp"
#include "MAX7219.hpp"


/**
 * @brief 
 * 
 */
struct StatisticsSwitches{
    hwlib::target::pin_in& SWITCH_START_RESET;
    hwlib::target::pin_in& SWITCH_HIGHSCORE;
    hwlib::target::pin_in& SWITCH_TIMES_PLAYED;
    hwlib::target::pin_in& SWITCH_REACTION_TIME;
};

/**
 * @brief 
 * This is the class of the game
 */
class game{
private:

    /**
     * @brief 
     * 
     */
    enum state{
        START_PAGE,
        HIGHSCORE_PAGE,
        REACTION_TIME_PAGE,
        TIMES_PLAYED_PAGE,
        GAME,
        GAME_OVER
    };

    /**
     * @brief 
     * 
     */
    hwlib::port_out& leds;

    /**
     * @brief 
     * 
     */
    hwlib::port_in& switches;

    /**
     * @brief 
     * 
     */
    StatisticsSwitches statistics_switches;

    /**
     * @brief 
     * 
     */
    MAX7219 &display;

    /**
     * @brief 
     * 
     */
    state current_state;

    /**
     * @brief 
     * 
     */
    unsigned int max_game_time = 2500000;

    /**
     * @brief 
     * The games_played contains how many times you played the game.
     */
    unsigned int games_played = 0;

    /**
     * @brief 
     * The current_score contains the score of the game your playing.
     */
    unsigned int current_score = 0;

    /**
     * @brief 
     * The end_score_game contains the score you had when you finished a game.
     */
    unsigned int end_score_game = 0;

    /**
     * @brief 
     * The scores is an array that contains the end score of every game.
     */
    unsigned int scores[512];

    /**
     * @brief 
     * The highscore_num contains the highest score you managed to obtain.
     */
    unsigned int highscore_num = 0;

    /**
     * @brief 
     * The score is an array that contains the score of each game you played.
     */
    unsigned int react[512];

    /**
     * @brief 
     * 
     */
    unsigned int menu_text = 0;

    /**
     * @brief 
     * 
     */
    unsigned int highscore_text = 0;

    /**
     * @brief 
     * 
     */
    unsigned int times_played_text = 0;

    /**
     * @brief 
     * 
     */
    unsigned int reaction_text = 0;

    /**
     * @brief 
     * 
     */
    uint_fast64_t menu_update_time = 0;

    /**
     * @brief 
     * 
     */
    uint_fast64_t highscore_update_time = 0;
    
    /**
     * @brief 
     * 
     */
    uint_fast64_t times_played_update_time = 0;

    /**
     * @brief 
     * 
     */
    uint_fast64_t reaction_update_time = 0;

    /**
     * @brief 
     * This function adds the score to an array at the end of a game.
     */
    void score();

    /**
     * @brief 
     * This function will show the highest score on the display.
     */
    void show_highscore();

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool play();

    /**
     * @brief 
     * This function shows how many times you have played on the display.
     */
    void show_times_played();

    /**
     * @brief 
     * 
     */
    void show_menu();

    /**
     * @brief 
     * 
     */
    void check_menu_buttons();

    /**
     * @brief 
     * This function will calculate the average reaction time and show it on the display.
     */
    void average_reaction_time();

    /**
     * @brief 
     * This function will show you that the game is over.
     */
    void show_game_over();

public: 
    /**
     * @brief Construct a new game object
     * 
     * @param leds 
     * @param switches 
     * @param statistics_switches 
     * @param display 
     */
    game(hwlib::port_out& leds, hwlib::port_in& switches, StatisticsSwitches statistics_switches, MAX7219 &display);

    /**
     * @brief 
     * 
     */
    void run();
};


#endif //APPLICATION_HPP