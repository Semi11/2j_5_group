#ifndef _INCLUDE_SCORE_
#define _INCLUDE_SCORE_

#include <string>

class Score{
 private:
  std::string name;
  int score;
 public:
  void set(std::string name, int score);
  int get_score();
  void load(std::string file_name);
  void save(std::string file_name);
  void disp(); 
};

#endif
