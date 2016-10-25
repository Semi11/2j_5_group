#include "LCD_lib.h"
#include "game_timer.h"
#include <unistd.h>
#include <string>

GameTimer::GameTimer(){
  init(180);
}

GameTimer::GameTimer(const int time_limit){
  init(time_limit);
}

void GameTimer::init(const int time_limit){
  time = time_limit;
  minute = time_limit / 60;
  tens_sec = time_limit % 60 /10;
  ones_sec = time_limit % 60 %10;
}

void GameTimer::tick_timer(){

  disp_timer();
  time--;
  if((tens_sec == 0) && (ones_sec == 0)){
    minute--;
    tens_sec = 5;
    ones_sec = 9;
  }else if(ones_sec == 0){
    tens_sec--;
    ones_sec = 9;
  }else{
    ones_sec--;
  }
  
  usleep(1000000);
}

int GameTimer::get_time(){
  return time;
}

bool GameTimer::is_timeout(){
  if(time < 0) return true;
  return false;
}

void GameTimer::disp_timer(){
  clear_display();
  cursor_at_home();
      
  disp_str(std::to_string(minute).c_str());
  disp_char(':');
  disp_str(std::to_string(tens_sec).c_str());
  disp_str(std::to_string(ones_sec).c_str());

}
