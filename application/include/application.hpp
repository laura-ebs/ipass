//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "hwlib.hpp"
#include "../../library/include/MAX7219.hpp"


/**
 * @brief 
 * A struct that contains the pins for the menu.
 * @param SWITCH_START_RESET
 * This is a pin_in refrence object for the start_reset switch.
 * @param SWITCH_HIGHSCORE
 * This is a pin_in refrence object for the highscore switch.
 * @param SWITCH_TIMES_PLAYED
 * This is a pin_in refrence object for the played_times switch.
 * @param SWITCH_REACTION_TIME
 * This is a pin_in refrence object for the reaction_time switch.
 */
struct MenuSwitches{
    hwlib::target::pin_in& SWITCH_START_RESET;
    hwlib::target::pin_in& SWITCH_HIGHSCORE;
    hwlib::target::pin_in& SWITCH_TIMES_PLAYED;
    hwlib::target::pin_in& SWITCH_REACTION_TIME;
};

/**
 * @brief 
 * This is the class of the game.
 */
class game{
private:

  /**
   * @brief 
   * This enum contains all the states the game can be in.
   * @param START_PAGE
   * Shows the menu.
   * @param HIGHSCORE_PAGE 
   * Shows the highscore.
   * @param REACTION_TIME_PAGE
   * Shows the reaction time.
   * @param TIMES_PLAYED_PAGE
   * Shows times played.
   * @param GAME
   * Play the game.
   * @param GAME_OVER
   * Shows when game is over
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
     * A port_out object with all the leds.
     */
    hwlib::port_out& leds;

    /**
     * @brief 
     * A port_in object with all the switches.
     */
    hwlib::port_in& switches;

    /**
     * @brief 
     * A struct for the menu switches.
     */
    MenuSwitches menu_switches;

    /**
     * @brief 
     * A  refrence to MAX7219 object.
     */
    MAX7219 &display;

    /**
     * @brief 
     * This contains the state the game is in.
     */
    state current_state;

    /**
     * @brief 
     * The max_reaction_time contains the maximum time you to press a switch.
     */
    unsigned int max_reaction_time = 2500000;

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
     * This contains how many things need displayed on the menu.
     */
    unsigned int menu_text = 0;

    /**
     * @brief 
     * This contains how many things need displayed for the higscore.
     */
    unsigned int highscore_text = 0;

    /**
     * @brief 
     * This contains how many things need displayed for the times played.
     */
    unsigned int times_played_text = 0;

    /**
     * @brief 
     * This contains how many things need displayed for the reaction time.
     */
    unsigned int reaction_text = 0;

    /**
     * @brief 
     * The menu_update_time contains after how much time the display will update.
     */
    uint_fast64_t menu_update_time = 0;

    /**
     * @brief 
     * The highscore_update_time contains after how much time the display will update.
     */
    uint_fast64_t highscore_update_time = 0;
    
    /**
     * @brief 
     * The times_played_update_time contains after how much time the display will update.
     */
    uint_fast64_t times_played_update_time = 0;

    /**
     * @brief 
     * The reaction_update_time contains after how much time the display will update.
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
     * This funtion will play the game.
     */
    void play();

    /**
     * @brief 
     * This function shows how many times you have played on the display.
     */
    void show_times_played();

    /**
     * @brief 
     * This function shows the menu.
     */
    void show_menu();

    /**
     * @brief 
     * This function this functoin checks if one of the menu switches is pressed if so it will put to the correct state.
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
     * @brief 
     * Construct a new game object
     * @param leds
     * A port_out reference object that contains the pins to the leds.
     * @param switches 
     * A port_in reference object that contains the pins to the game switches.
     * @param menu_switches 
     * A port_in reference object that contains the pins to the menu switches.
     * @param display 
     * A reference to the object of MAX7219 chip.
     */
    game(hwlib::port_out& leds, hwlib::port_in& switches, MenuSwitches menu_switches, MAX7219 &display);

    /**
     * @brief 
     * This function will start the game.
     */
    void run();
};


#endif //APPLICATION_HPP