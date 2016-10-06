#include <stdio.h>
#include <time.h>
#include "niusb6501.h"

#define PIOA 0
#define PIOB 1
#define PIOC 2
#define START_DATA 0xFE
#define GOAL_DATA 0xFD
#define TIME_LIMIT 180
#define HIGH_SCORE 180

typedef struct {
  int timer;
  char minute;
  char tens_sec;
  char ones_sec;
}gameTimer_t;

void clear_display(void);
void cursor_at_home(void);
void function_set(void);
void display_onoff_control(void);
void entrymode_set(void);
void move_line(void);
int is_start(void);
int is_goal(void);
void disp_char(char c);
void disp_str(char str[]);
void disp_timer(gameTimer_t timer);


int main(void){

  init_device();
  set_io_mode(0xFF, 0xFF, 0xFD);

  clear_display();
  cursor_at_home();
  function_set();
  display_onoff_control();
  entrymode_set();

  gameTimer_t timer = {
    .timer = TIME_LIMIT,
    .minute = '3',
    .tens_sec = '0',
    .ones_sec = '0',
  };
  
  int count;
  const char goal_str[] = "PUSH   ENTER!!";
  //const char high_socere_str[] = " HIGH SCORE!!";
  int high_score = HIGH_SCORE;
  
  unsigned char PIOC_dat;

  while(1){
    clear_display();

    while(!is_start());
    
    count = 5;
    
    disp_timer(timer);
    
    if(timer.timer > high_score){
      high_score = timer.timer;
      disp_str(" HIGH SCORE!!");
    }
     
    move_line();

    for(count = 0;goal_str[count] != '\0';count++){
      write_port(PIOB, 0x06);
      write_port(PIOA, goal_str[count]);
      write_port(PIOB, 0x00);
      usleep(40);
    }
    //    scanf("%*c");
    PIOC_dat = read_port(PIOC);
  }
  
  return 0;
}


void clear_display(void)
{
  write_port(PIOB, 0x04);
  write_port(PIOA, 0x01);
  write_port(PIOB, 0x00);
  usleep(1640);
}

void cursor_at_home(void)
{
  write_port(PIOB, 0x04);
  write_port(PIOA, 0x02);
  write_port(PIOB, 0x00);
  usleep(1640);
}

void function_set(void)
{
  write_port(PIOB, 0x04);
  write_port(PIOA, 0x38);
  write_port(PIOB, 0x00);
  usleep(40);
}

void display_onoff_control(void)
{
  write_port(PIOB, 0x04);
  write_port(PIOA, 0x0e);
  write_port(PIOB, 0x00);
  usleep(40);
}

void entrymode_set(void)
{
  write_port(PIOB, 0x04);
  write_port(PIOA, 0x06);
  write_port(PIOB, 0x00);
  usleep(40);
}

int is_start(void){
  char PIOC_dat;
    
  PIOC_dat = read_port(PIOC);

  if(PIOC_dat == START_DATA) return 1;
  return 0;
}
  
int is_goal(void){
  char PIOC_dat;
    
  PIOC_dat = read_port(PIOC);

  if(PIOC_dat == GOAL_DATA) return 1;
  return 0;
}
  
void move_line(void){
  write_port(PIOB, 0x04);
  write_port(PIOA, 0xC0);
  write_port(PIOB, 0x00);
  usleep(40);
}
      
void disp_char(char c){
  write_port(PIOB, 0x06);
  write_port(PIOA, c);
  write_port(PIOB, 0x00);
  usleep(40);    
}

void disp_str(char str[]){
  int i=0;
  while(str[i] != '\0'){
    write_port(PIOB, 0x06);
    write_port(PIOA, str[i]);
    write_port(PIOB, 0x00);
    usleep(40);
    i++;
  }
}

void disp_timer(gameTimer_t timer){
  for(timer.minute = '3',timer.tens_sec = '0',timer.ones_sec = '0',timer.timer = TIME_LIMIT;timer.timer >= 0;timer.timer--){
      
      clear_display();
      cursor_at_home();
      
      disp_char(timer.minute);
      disp_char(':');
      disp_char(timer.tens_sec);
      disp_char(timer.ones_sec);
      
      if(is_goal)break;
      
      if(timer.tens_sec == '0' && timer.ones_sec == '0'){
	timer.minute--;
	timer.tens_sec = '5';
	timer.ones_sec = '9';
      }else if(timer.ones_sec == '0'){
	timer.tens_sec--;
	timer.ones_sec = '9';
      }else{
	timer.ones_sec--;
      }
      sleep(1);
    }

}
