#include "LCD_lib.h"
#include "game_timer.h"
#include <unistd.h>

#define DELAY 5000

GameTimer::GameTimer(){
  init(180);
}

GameTimer::GameTimer(const int time_limit){
  init(time_limit);
}

void GameTimer::init(const int time_limit){
  // timer->minute = '3';
  // timer->tens_sec = '0';
  // timer->ones_sec = '0';
  time = time_limit;
  minute = time_limit / 60;
  tens_sec = time_limit % 60 /10;
  ones_sec = time_limit % 60 %10;
}

void GameTimer::tick_timer(){
  static int cnt = DELAY;
  cnt++;

  if(cnt > DELAY){
    disp_timer(timer);
    timer->timer--;
    if(timer->tens_sec == '0' && timer->ones_sec == '0'){
      timer->minute--;
      timer->tens_sec = '5';
      timer->ones_sec = '9';
    }else if(timer->ones_sec == '0'){
      timer->tens_sec--;
      timer->ones_sec = '9';
    }else{
      timer->ones_sec--;
    }
    cnt = 0;
  }
  
  usleep(1);
}

void GameTimer::disp_timer(){
  clear_display();
  cursor_at_home();
      
  disp_char(timer->minute);
  disp_char(':');
  disp_char(timer->tens_sec);
  disp_char(timer->ones_sec);

}
