#include <thread>
#include <iostream>
#include "LCD_lib.h"
#include "niusb6501.h"
#include "game_main.h"
#include <unistd.h>

GameMain::GameMain(){
  init();
}

void GameMain::init(){
  timer.init(TIME_LIMIT);
  high_score.load(HIGH_SCORE_DAT_FILE);
  goal_flg = false;
}

void GameMain::play(){
  auto th = std::thread(&GameMain::run_timer,this);
  th.detach();
  
  while(!(timer.is_timeout()) && !(goal_flg)){
    timer.disp();
    goal_flg = is_goal();
  }
  timer.stop();

  clear_display();  
  if(goal_flg){
    process_goal();
  }else{
    process_timeup();
  }
  
  clear_display();
  high_score.disp();
  sleep(5);
}

void GameMain::run_timer(){
  while(!(timer.is_timeout()) && (timer.is_tick())){
    timer.tick();
    sleep(1);
  }
}

void GameMain::process_goal(){
  std::string name;

  if(timer.get_time() > high_score.get_score()){
    disp_str(" HIGH SCORE!!");
    disp_str(" INPUT NAME");
    printf("input your name->");
    std::cin >> name;
    high_score.set(name, timer.get_time());
  }else{
    disp_str(" GOAL!!");
    sleep(5);
  }  
}

void GameMain::process_timeup(){
  disp_str(" TIME UP!!");
  sleep(5);
}

bool GameMain::is_start(){
  char PIOC_dat;
    
  PIOC_dat = read_port(PIOC);
  std::cout << std::hex << PIOC_dat << "\r";
  if((PIOC_dat & 0x03) == START_DATA) return true;

  return false;
}

bool GameMain::is_goal(){
  char PIOC_dat;
    
  PIOC_dat = read_port(PIOC);
  //std::cout << std::hex << PIOC_dat << "\r";
  printf("%x\r",PIOC_dat);
  if((PIOC_dat & 0x03)  == GOAL_DATA) return true;
  
  return false;
}
