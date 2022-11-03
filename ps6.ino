#include <Wire.h>
#include "lcd_wrapper.h"
#include "mastermind.h"

void setup() {
  pinMode(A0, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  lcd_init();

}

void loop() {
  char* code = NULL;
  code = generate_code(false, 4);
  //lcd_print_at(0,0, code);
  /*free(code);
  delay(2000);*/
  /*int peg_a;
  int peg_b;
  get_score("9347", "9436", &peg_a, &peg_b);
  char aa[4] = "A:a.";
  aa[2] = peg_a + '0';
  char bb[4] = "B:b.";
  bb[2] = peg_b + '0';
  lcd_print_at(0, 0, aa);
  lcd_print_at(0, 1, bb);
  //Serial.print(peg_a);
  //Serial.print(peg_b);
  analogWrite(6, 255);
  analogWrite(7, 255);
  analogWrite(8, 255);
  analogWrite(9, 255);
  analogWrite(10, 255);
  analogWrite(11, 255);
  analogWrite(12, 255);
  analogWrite(13, 255);
  //delay(5000);
  turn_off_leds();
  //delay(5000);
  render_leds(2, 2);
  /*char **history;
  history = (char **)calloc(10, sizeof(char));



history[0][0] = "1234";
history[1][0] = "5678";
history[2][0] = "9012";

render_history("9347", history, 2);
lcd_clear();
  play_game("5847");

  delay(99999999);*/
  play_game(code);
  free(code);
  delay(4000);

}
