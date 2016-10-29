#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LCD_lib.h"
#include "niusb6501.h"
#include "game_main.h"
#include <unistd.h>
#include <assert.h>

GameMain::GameMain(){
  init();
}

void GameMain::init(){
  std::string time_limit_str = load_time_limit(TIME_LIMIT_DAT_FILE);
  int time_limit;
  
  std::istringstream is(time_limit_str);
  is >> time_limit;
  timer.init(time_limit);
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
  Score score;

  if(timer.get_time() > high_score.get_score()){
    disp_str(" HIGH SCORE!!");
    sleep(3);
    clear_display();
    disp_str(" INPUT NAME");
    printf("input your name->");
    std::cin >> name;
    high_score.set(name, timer.get_time());
    high_score.save(HIGH_SCORE_DAT_FILE);
  }else{
    score.set("YOUR SCORE", timer.get_time());

    disp_str(" GOAL!!");
    sleep(5);
    clear_display();
    score.disp();
    sleep(5);
    clear_display();
    disp_str(" HIGH SCORE");
    sleep(5);
    clear_display();   
  }  
}

void GameMain::process_timeup(){
  disp_str(" TIME UP!!");
  sleep(5);
}

bool GameMain::is_start(){
  char PIOC_dat;
    
  PIOC_dat = read_port(PIOC);
  //  std::cout << std::hex << PIOC_dat << "\r";
  printf("%x\r",PIOC_dat);
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

std::string GameMain::load_time_limit(std::string file_name){
  std::string buf;
  
  std::ifstream reading_file(file_name, std::ios::in);
  assert(reading_file.is_open());
  std::getline(reading_file, buf);
  reading_file.close();

  return buf;
}
