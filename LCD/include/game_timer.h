#ifndef _INCLUDE_GAME_TIMER_
#define _INCLUDE_GAME_TIMER_

class GameTimer{ 
  
 public:
  GameTimer();
  GameTimer(const int time_limit);
  void init(const int time_limit);
  void tick_timer();
  void disp_timer();
  int get_time();
  bool is_timeout();

 private:
  int time;
  int minute;
  int tens_sec;
  int ones_sec;
};

#endif
