//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#include "application.hpp"
#include "MAX7219.hpp"
#include "hwlib.hpp"

game::game(hwlib::port_out& leds, hwlib::port_in& switches, MenuSwitches menu_switches, MAX7219 &display):
    leds(leds),
    switches(switches),
    menu_switches(menu_switches),
    display(display),
    current_state(START_PAGE)
{
    display.initialize();
    display.set_intensity(8);
    display.clear();
    leds.write(0);
}

void game::run(){
    while(true){
        switch (current_state)
        {
        case START_PAGE:
            show_menu();
            check_menu_buttons();
            hwlib::wait_ms(10);
            break;

        case HIGHSCORE_PAGE:
            show_highscore();
            check_menu_buttons();
            hwlib::wait_ms(10);
            break;
        
        case REACTION_TIME_PAGE:
            average_reaction_time();
            check_menu_buttons();
            hwlib::wait_ms(10);
            break;
        
        case TIMES_PLAYED_PAGE:
            show_times_played();
            check_menu_buttons();
            hwlib::wait_ms(10);
            break;

        case GAME:
            play();
            hwlib::wait_ms(10);
            break;

        case GAME_OVER:
            show_game_over();
            hwlib::wait_ms(10);
            break;
        }
    }
}

void game::check_menu_buttons(){
    if (menu_switches.SWITCH_START_RESET.read() == 0){ 
        current_state = GAME;
    } else if (menu_switches.SWITCH_HIGHSCORE.read() == 0){
        current_state = HIGHSCORE_PAGE;
    } else if (menu_switches.SWITCH_TIMES_PLAYED.read() == 0){
        current_state = TIMES_PLAYED_PAGE;
    } else if (menu_switches.SWITCH_REACTION_TIME.read() == 0){
        current_state = REACTION_TIME_PAGE;
    }
}

void game::show_game_over(){
    leds.write(0);
    display.write_string("game", 4);
    hwlib::wait_ms(1000);
    display.write_string("ouer", 4);
    hwlib::wait_ms(2000);
    games_played++;
    max_reaction_time = 2500000;
    current_state = START_PAGE;
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


void game::score(){
    scores[games_played] = end_score_game;
}

void game::show_highscore(){
    for(unsigned int i = 0; i < games_played; ++i){
        if (scores[i] > highscore_num){
            highscore_num = scores[i];
        }  
    }

    if (hwlib::now_us() > highscore_update_time + 800000){
        highscore_update_time = hwlib::now_us();
        display.clear();
        switch (highscore_text)
        {
        case 0:
            display.write_string("hiscore" ,7);
            break;
        case 1:
            display.write_int(highscore_num);
            break;
        }
        highscore_text++;
        if(highscore_text>=2){
            highscore_text = 0; 
        } 
    }
}


void game::play(){
    if(current_score % 5 == 0) {
        max_reaction_time -= 100000;
    }
    auto led=hwlib::random_in(0,4);
    auto start_time= hwlib::now_us();
    leds.write(0x01 << led);
    while(((switches.read() & (0x01 << led)) >> led) == 1){
        
        if((start_time + max_reaction_time) < hwlib::now_us()) {
            hwlib::cout <<  hwlib::now_us() << hwlib::endl;
            end_score_game = current_score;
            score();
            current_score=0;
            current_state = GAME_OVER;
            return;
        }
    }
    auto end_time= hwlib::now_us();
    auto reaction_time = end_time - start_time;
    react[current_score] = reaction_time;
    current_score++;
    return;
}

void game::show_times_played(){
if (hwlib::now_us() > times_played_update_time + 800000){
        times_played_update_time = hwlib::now_us();
        display.clear();
        switch (times_played_text)
        {
        case 0:
            display.write_string("ganes", 5);
            break;
        case 1:
            display.write_string("played", 6);
            break;
        case 2:
            display.write_int(games_played);
            break;
        }
        times_played_text++;
        if(times_played_text>=3){
            times_played_text = 0; 
        }
    }
}

void game::average_reaction_time(){
    auto total =  0;
    for(unsigned int i = 0; i < end_score_game; ++i){
        total += react[i];
    }
    unsigned int average = total / end_score_game;

    if (hwlib::now_us() > reaction_update_time + 800000){
        reaction_update_time = hwlib::now_us();
        display.clear();
        switch (reaction_text)
        {
        case 0:
            display.write_string("reaction", 8);
            break;
        case 1:
            display.write_string("tine", 4);
            break;
        case 2:
            display.write_string("in us", 5);
            break;
        case 3:
            display.write_int(average);;
            break;
        }
        reaction_text++;
        if(reaction_text >= 4){
            reaction_text = 0; 
        }
    }
}



