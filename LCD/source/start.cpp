#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "LCD_lib.h"
#include "game_timer.h"
#include "niusb6501.h"

#define START_DATA 0x01
#define GOAL_DATA 0x02
#define NAME_LENGTH 17
#define SCORE_LENGTH 6
#define HIGH_SCORE_DAT_FILE "dat/highscore.dat"

typedef struct {
  char name[NAME_LENGTH];
  int score;
}score_t;

int is_start(void);
int is_goal(void);
void disp_high_score(const score_t *high_score); 
void load_high_score(score_t *high_score);
void save_high_score(const score_t *high_score);

int main(void){  
  gameTimer_t timer;
  score_t high_score;
  int goal_flg = 0;

  init_LCD();
  
  while(1){
    
    //puts("task start");
    clear_display();
    init_timer(&timer);
    goal_flg = 0;
    load_high_score(&high_score);

    disp_str(" PLEASE START");
    while(!is_start());
    clear_display(); 

    while(timer.timer >= 0 && !goal_flg){
      tick_timer(&timer);
      goal_flg = is_goal();
      
    }

    clear_display();

    if(goal_flg){
      if(timer.timer > high_score.score){
	high_score.score = timer.timer;
	disp_str(" HIGH SCORE!!");
	disp_str(" INPUT NAME");
	printf("input your name->");
	fgets(high_score.name, NAME_LENGTH, stdin);
	save_high_score(&high_score);
      }else{
	disp_str(" GOAL!!");
	sleep(5);
      }
    }else{
      disp_str(" TIME UP!!");
      sleep(5);
    }

    disp_high_score(&high_score);

    disp_str(" PUSH ENTER!!");
    getchar();
  }
  
  return 0;
}

void load_high_score(score_t *high_score){
  FILE *fp;
  char score_buf[SCORE_LENGTH];

  fp = fopen(HIGH_SCORE_DAT_FILE, "r");
  assert(fp != NULL);
  fgets(high_score->name, NAME_LENGTH, fp);
  fgets(score_buf, SCORE_LENGTH, fp);
  high_score->score = atoi(score_buf);
  fclose(fp);
}

void save_high_score(const score_t *high_score){
  FILE *fp;
  
  fp = fopen(HIGH_SCORE_DAT_FILE, "w");
  fprintf(fp,"%s", high_score->name);
  fprintf(fp,"%d\n", high_score->score);
  
  fclose(fp);
}

int is_start(void){
  char PIOC_dat;
    
  PIOC_dat = read_port(PIOC);
  printf("%x\r",PIOC_dat);
  if((PIOC_dat & 0x03) == START_DATA) return 1;

  return 0;
}
  
int is_goal(void){
  char PIOC_dat;
    
  PIOC_dat = read_port(PIOC);
  printf("%x\r",PIOC_dat);

  if((PIOC_dat & 0x03)  == GOAL_DATA) return 1;

  return 0;
}

void disp_high_score(const score_t *high_score){
  char score[SCORE_LENGTH];

  sprintf(score, "%d", high_score->score);

  clear_display();  
  disp_str(high_score->name);
  disp_str(score);

  sleep(5);

  clear_display();
}
