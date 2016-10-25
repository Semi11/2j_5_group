#ifndef _INCLUDE_LCD_LIB_
#define _INCLUDE_LCD_LIB_

#ifdef __cplusplus
extern "C" {
#endif

#define PIOA 0
#define PIOB 1
#define PIOC 2

void init_LCD();
void clear_display(void);
void cursor_at_home(void);
void function_set(void);
void display_onoff_control(void);
void entrymode_set(void);
void move_line(void);
void disp_char(char c);
void disp_str(const char str[]);

#ifdef __cplusplus
};
#endif

#endif
