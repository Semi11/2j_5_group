#ifndef _INCLUDE_GAME_MAIN_
#define _INCLUDE_GAME_MAIN_

#include "game_timer.h"
#include "score.h"

#define TIME_LIMIT 180
#define START_DATA 0x01
#define GOAL_DATA 0x02
#define HIGH_SCORE_DAT_FILE "dat/highscore.dat"
#define TIME_LIMIT_DAT_FILE "dat/timelimit.dat"

class GameMain{
 private:
  GameTimer timer;
  Score high_score;
  bool goal_flg;
 public:
  GameMain();
  void init();
  void play();
  void run_timer();
  void process_goal();
  void process_timeup();
  bool is_start();
  bool is_goal();
  std::string load_time_limit(std::string file_name);
};

#endif
