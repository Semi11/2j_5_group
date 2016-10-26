#include "score.h"
#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "LCD_lib.h"

void Score::set(std::string name, int score){
  this->name = name;
  this->score = score;
}

int Score::get_score(){
  return score;
}

void Score::load(std::string file_name){
  std::string buf;
  
  std::ifstream reading_file(file_name, std::ios::in);
  assert(reading_file.is_open());
  std::getline(reading_file, name);
  std::getline(reading_file, buf);
  std::istringstream is(buf);
  is >> score;
  reading_file.close();
}

void Score::save(std::string file_name){
  std::ofstream writing_file(file_name, std::ios::trunc);
  assert(writing_file.is_open());
  writing_file << name << std::endl;
  writing_file << score << std::endl;
  writing_file.close();
}

void Score::disp(){
  disp_str(name.c_str());
  move_line();
  disp_str(std::to_string(score).c_str());
}
