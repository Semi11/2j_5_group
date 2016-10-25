#include <stdio.h>
#include "LCD_lib.h"
#include "niusb6501.h"

void init_LCD(){
  init_device();
  set_io_mode(0xFF, 0xFF, 0xFD);
  clear_display();
  cursor_at_home();
  function_set();
  display_onoff_control();
  entrymode_set();
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

void disp_str(const char str[]){
  int i=0;
  while(str[i] != '\0'){
    if(str[i] != '\n') disp_char(str[i]);
    i++;
  }

  printf("%s\n\n",str);
}

