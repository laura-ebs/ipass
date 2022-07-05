//Copyright (c) 2022 Laura Ebskamp. All rights reserved.

//This work is licensed under the terms of the MIT license.
//For a copy, see https://opensource.org/licenses/MIT.

#include "application.hpp"
#include "MAX7219.hpp"
#include "hwlib.hpp"

game::game(hwlib::target::pin_out &leds[5],hwlib::target::pin_in &switches[5],hwlib::target::pin_in &statistics_switches[4],MAX7219 max7219_display(max_data_in, max_cs, max_clock )):
    leds(leds),
    switches(switches),
    statistics_switches(statistics_switches),
    max7219_display(max7219_display)
{}


void game::statistics(){
    if (statistic_switches[0].read==1){
        start_reset();
    }
    else if (statistic_switches[1].read==1){
        highscore();
    }
    else if (statistic_switches[2].read==1){
        gemiddelde_reactietijd();
    }
    else if (statistic_switches[3].read==1){
        times_played();
    }
}

void game::start_reset(){
    game_it();
    games_played++;
}

void game::score(){
    scores[gamesplayed]==end_score_game;
}

void game::highscore(){
    for(unsigned int i; i<sizeof(scores); i++){
        if (score[i]>highscore_num){
            highscore_num=score[i];
        }  
    }
}


bool game::check(){
    if(current_score % 5 == 0) {
        max_game_time -= 100000;
    }
    auto led=hwlib::random_in(0,4);
    auto start_time= hwlib::now_us;
    leds[led].write(1);
    while(switch[led]==0){
        if(start_time+max_game_time < hwlib::now_us) {
            end_score_game = current_score;
            current_score=0;
            return 0;
        }
    }
    if (switch[led]==1){
        current_score++;
    }
    return 1;
}

void game::times_played(){

}

void game::game_it(){
    for(;;){
        if (check==0){ 
        }
    }
}





int main(){
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
auto SWITCH_0=hwlib::target::pin_in(hwlib::target::pins::d15);
auto SWITCH_1=hwlib::target::pin_in(hwlib::target::pins::d2);
auto SWITCH_2=hwlib::target::pin_in(hwlib::target::pins::d4);
auto SWITCH_3=hwlib::target::pin_in(hwlib::target::pins::d6);
auto SWITCH_4=hwlib::target::pin_in(hwlib::target::pins::d8);
auto SWITCH_START_RESET=hwlib::target::pin_in(hwlib::target::pins::d10);
auto SWITCH_HIGHSCORE=hwlib::target::pin_in(hwlib::target::pins::d11);
auto SWITCH_TIMES_PLAYED=hwlib::target::pin_in(hwlib::target::pins::d12);
auto SWITCH_REACTIETIJD=hwlib::target::pin_in(hwlib::target::pins::d13);

MAX7219 max7219_display(max_data_in, max_cs, max_clock);
//array for switches with statistics
hwlib::target::pin_in statistics_switches[4]={SWITCH_START_RESET,SWITCH_HIGHSCORE ,SWITCH_TIMES_PLAYED, SWITCH_REACTIETIJD};
//arrays for switches game and leds.
hwlib::target::pin_out leds[5]={LED_0,LED_1,LED_2,LED_3,LED_4};
hwlib::target::pin_in switches[5]={SWITCH_0, SWITCH_1, SWITCH_2, SWITCH_3, SWITCH_4};

//constuctor game
game game1(leds,switches,statistics_switches, max7219_display);

}