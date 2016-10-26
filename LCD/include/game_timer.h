#ifndef _INCLUDE_GAME_TIMER_
#define _INCLUDE_GAME_TIMER_

class GameTimer{ 
 private:
  int time;
  int minute;
  int tens_sec;
  int ones_sec;
  bool tick_flg;
  
 public:
  GameTimer();
  GameTimer(const int time_limit);
  void init(const int time_limit);
  void tick();
  void stop();
  int get_time();
  bool is_timeout();
  bool is_tick();
  void disp();

};

#endif
