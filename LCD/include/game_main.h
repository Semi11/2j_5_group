#ifndef _INCLUDE_GAME_MAIN_
#define _INCLUDE_GAME_MAIN_

#include "game_timer.h"
#include "score.h"

#define START_DATA 0x01
#define GOAL_DATA 0x02
#define TIME_LIMIT 100
#define HIGH_SCORE_DAT_FILE "dat/highscore.dat"

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
};

#endif
