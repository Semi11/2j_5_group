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

void clear_display(void);
void cursor_at_home(void);
void function_set(void);
void display_onoff_control(void);
void entrymode_set(void);
void move_line(void);
int is_start(void);
int is_goal(void);



int main(void){

  init_device();
  set_io_mode(0xFF, 0xFF, 0xFD);

  clear_display();
  cursor_at_home();
  function_set();
  display_onoff_control();
  entrymode_set();
  
  int stimer,count;
  char asec,bsec,minute;
  char Gchar[] = "PUSH   ENTER!!";
  int high_score = HIGH_SCORE;
  
  unsigned char PIOC_dat;

  while(1){
    clear_display();

    while(!is_start());
    
    count = 5;
    
    for(minute = '3',asec = '0',bsec = '0',stimer = TIME_LIMIT;stimer >= 0;stimer--){
      
      clear_display();
      cursor_at_home();
      
      write_port(PIOB, 0x06);
      write_port(PIOA, minute);
      write_port(PIOB, 0x00);
      usleep(40);
      
      write_port(PIOB, 0x06);
      write_port(PIOA, ':');
      write_port(PIOB, 0x00);
      usleep(40);
      
      write_port(PIOB, 0x06);
      write_port(PIOA, asec);
      write_port(PIOB, 0x00);
      usleep(40);
      
      write_port(PIOB, 0x06);
      write_port(PIOA, bsec);
      write_port(PIOB, 0x00);
      usleep(40);
      
      if(is_goal)break;
      
      if(asec == '0' && bsec == '0'){
	minute--;
	asec = '5';
	bsec = '9';
      }else if(bsec == '0'){
	asec--;
	bsec = '9';
      }else{
	bsec--;
      }
      sleep(1);
    }

    char Hchar[] = " HIGH SCORE!!";
    if(stimer > high_score){
      high_score = stimer;
      for(count = 0;Hchar[count] != '\0';count++){
	write_port(PIOB, 0x06);
	write_port(PIOA, Hchar[count]);
	write_port(PIOB, 0x00);
	usleep(40);
      }
    }
     
    move_line();

    for(count = 0;Gchar[count] != '\0';count++){
      write_port(PIOB, 0x06);
      write_port(PIOA, Gchar[count]);
      write_port(PIOB, 0x00);
      usleep(40);
    }
    scanf("%*c");
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
      
