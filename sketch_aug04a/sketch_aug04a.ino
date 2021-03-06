//http://tsukutta.hatenablog.com/entry/2013/12/15/062500


#define IN_PIN_UP 2
#define IN_PIN_DOWN 3
#define IN_PIN_LEFT 4
#define IN_PIN_RIGHT 7
#define OUT_PIN_MOTOR_A 8
#define OUT_PIN_MOTOR_B 6
#define OUT_PIN_MOT_AB_PWM 9
#define OUT_PIN_MOTOR_C 10
#define OUT_PIN_MOTOR_D 5
#define OUT_PIN_MOT_CD_PWM 11
#define MOTOR_AB_PWM 255
#define MOTOR_CD_PWM 255
#define BUTTON_ON LOW
#define BUTTON_OFF HIGH

void setup() {
  pinMode(IN_PIN_UP, INPUT);
  pinMode(IN_PIN_DOWN, INPUT);
  pinMode(IN_PIN_LEFT, INPUT);
  pinMode(IN_PIN_RIGHT, INPUT);
  pinMode(OUT_PIN_MOTOR_A, OUTPUT);
  pinMode(OUT_PIN_MOTOR_B, OUTPUT);
  pinMode(OUT_PIN_MOTOR_C, OUTPUT);
  pinMode(OUT_PIN_MOTOR_D, OUTPUT);
}

void loop() {
  if (digitalRead(IN_PIN_UP) == BUTTON_ON && digitalRead(IN_PIN_DOWN) == BUTTON_OFF){
    digitalWrite(OUT_PIN_MOTOR_A, HIGH);
    digitalWrite(OUT_PIN_MOTOR_B, LOW);
    analogWrite(OUT_PIN_MOT_AB_PWM, MOTOR_AB_PWM);
  } else if (digitalRead(IN_PIN_UP) == BUTTON_OFF && digitalRead(IN_PIN_DOWN) == BUTTON_ON){
    digitalWrite(OUT_PIN_MOTOR_A, LOW);
    digitalWrite(OUT_PIN_MOTOR_B, HIGH);
    analogWrite(OUT_PIN_MOT_AB_PWM, MOTOR_AB_PWM);
  } else {
    digitalWrite(OUT_PIN_MOTOR_A, HIGH);
    digitalWrite(OUT_PIN_MOTOR_B, HIGH);
  }

  if (digitalRead(IN_PIN_LEFT) == BUTTON_ON && digitalRead(IN_PIN_RIGHT) == BUTTON_OFF) {
    digitalWrite(OUT_PIN_MOTOR_C, HIGH);
    digitalWrite(OUT_PIN_MOTOR_D, LOW);
    analogWrite(OUT_PIN_MOT_AB_PWM, MOTOR_CD_PWM);
  } else if (digitalRead(IN_PIN_RIGHT) == BUTTON_ON && digitalRead(IN_PIN_LEFT) == BUTTON_ON) {
    digitalWrite(OUT_PIN_MOTOR_C, LOW);
    digitalWrite(OUT_PIN_MOTOR_D, HIGH);
    analogWrite(OUT_PIN_MOT_AB_PWM, MOTOR_CD_PWM);
  } else {
    digitalWrite(OUT_PIN_MOTOR_C, HIGH);
    digitalWrite(OUT_PIN_MOTOR_D, HIGH);
  }

  delay(50);

}
