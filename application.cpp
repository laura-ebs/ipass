//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#include "application.hpp"
#include "MAX7219.hpp"
#include "hwlib.hpp"

game::game(hwlib::port_out& leds, hwlib::port_in& switches, StatisticsSwitches statistics_switches, MAX7219 &display):
    leds(leds),
    switches(switches),
    statistics_switches(statistics_switches),
    display(display),
    current_state(START_PAGE)
{
    display.initialize();
    display.clear();

    for(unsigned int i = 0; i < (sizeof(scores) / sizeof(unsigned int)); ++i){
        scores[i] = 0;
    }
}

void game::run()
{
    while(true)
    {
        switch (current_state)
        {
        case START_PAGE:
            show_menu();
            check_menu_buttons();
            hwlib::cout<<"test"<<hwlib::endl;
            break;

        case HIGHSCORE_PAGE:
            show_highscore();
            check_menu_buttons();
            hwlib::wait_ms(10);
            hwlib::cout<<"test1"<<hwlib::endl;
            break;
        
        case REACTION_TIME_PAGE:
            check_menu_buttons();
            hwlib::wait_ms(10);
            hwlib::cout<<"test2"<<hwlib::endl;
            break;
        
        case TIMES_PLAYED_PAGE:
            show_times_played();
            check_menu_buttons();
            hwlib::wait_ms(10);
            hwlib::cout<<"test3"<<hwlib::endl;
            break;
        
        case GAME:
            hwlib::cout<<"test4"<<hwlib::endl;
            break;
        }
    }
}

void game::check_menu_buttons()
{
    if (statistics_switches.SWITCH_START_RESET.read() == 0){ 
        current_state = GAME;
    } else if (statistics_switches.SWITCH_HIGHSCORE.read() == 0){
        current_state = HIGHSCORE_PAGE;
    } else if (statistics_switches.SWITCH_TIMES_PLAYED.read() == 0){
        current_state = TIMES_PLAYED_PAGE;
    } else if (statistics_switches.SWITCH_REACTION_TIME.read() == 0){
        current_state = REACTION_TIME_PAGE;
    }
}

void game::show_menu(){
    
    if (hwlib::now_us()> menu_update_time +800000){
        menu_update_time = hwlib::now_us();
        display.clear();
        switch (menu_text)
        {
        case 0:
            display.write_string("push", 4);
            break;
        case 1:
            display.write_string("the", 3);
            break;
        case 2:
            display.write_string("green", 5);
            break;
        case 3:
            display.write_string("button", 6);
            break;
        case 4:
            display.write_string("to", 2);
            break;
        case 5:
           display.write_string("start", 5);
           break; 
        }
        menu_text++;
        if(menu_text>=6){
            menu_text = 0; 
        }
    }
}

void game::start_reset(){
    game_it();
    games_played++;
}

void game::score(){
    scores[games_played] = end_score_game;
}

void game::show_highscore(){
    for(unsigned int i = 0; i < (sizeof(scores) / sizeof(unsigned int)); ++i){
        if (scores[i] > highscore_num){
            highscore_num = scores[i];
        }  
    }
    display.clear();
    display.write_int(highscore_num);
}


bool game::check(){
    if(current_score % 5 == 0) {
        max_game_time -= 100000;
    }
    auto led=hwlib::random_in(0,4);
    auto start_time= hwlib::now_us();
    leds.write(0x01 << led);
    while((switches.read() & (0x01 << led)) == 1){
        if((start_time + max_game_time) < hwlib::now_us()) {
            end_score_game = current_score;
            current_score=0;
            return 0;
        }
    }
    current_score++;

    return 1;
}

void game::show_times_played(){
    display.clear();
    display.write_int(games_played);
}





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
    StatisticsSwitches statistics_switches = {SWITCH_START_RESET,SWITCH_HIGHSCORE ,SWITCH_TIMES_PLAYED, SWITCH_REACTION_TIME};
    //arrays for switches game and leds.
    auto leds = hwlib::port_out_from(LED_0,LED_1,LED_2,LED_3,LED_4);
    auto switches = hwlib::port_in_from(SWITCH_0, SWITCH_1, SWITCH_2, SWITCH_3, SWITCH_4);


    //constuctor game
    game game1(leds,switches,statistics_switches, display);

    game1.run();
}