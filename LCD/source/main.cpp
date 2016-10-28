#include <stdio.h>
#include "LCD_lib.h"
#include "game_main.h"

int main(void){  
  GameMain game;

  init_LCD();
  
  while(true){
    
    clear_display();
    game.init();
    
    disp_str(" PLEASE START");
    while(!game.is_start());
    clear_display();

    game.play();

    clear_display();

    disp_str(" PUSH ENTER!!");
    getchar();
  }
  
  return 0;
}
