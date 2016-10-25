#ifndef _INCLUDE_GAME_TIMER_
#define _INCLUDE_GAME_TIMER_

#define TIME_LIMIT 180

class GameTimer{ 
  
 public:
  GameTimer();
  GameTimer(const int time_limit);
  void init(const int time_limit);
  void tick_timer();
  void disp_timer();

 private:
  int time;
  char minute;
  char tens_sec;
  char ones_sec;
};

#endif
