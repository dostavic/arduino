#include <LiquidCrystal_I2C.h>

#include <Arduino.h>
#include <string.h>
#include "mastermind.h"
#include "lcd_wrapper.h"
#include <string.h>

char* generate_code(bool repeat, int length){
  if (length < 1){
    return NULL;
  }

  char* number = (char*)calloc(length + 1, sizeof(int));
  
  for(int i = 0; i < length; i++){
      number[i] = random(10) + '0';
      //number[i] = 0 + '0';
  }
  if(repeat == false){
    for(int i = 0; i < length; i++){
      for(int j = 0; j < i; j++){
        if(number[i] == number[j] && i != j){
          while(number[i] == number[j]){
            number[i] = random(10) + '0';
          }
          j = 0;
        }
      }  
    }
  }
    
  return number;
}

void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b){
  *peg_a = 0;
  *peg_b = 0;
  int len = strlen(secret);
  for(int i = 0; i < len; i++){
    if(secret[i] == guess[i]){
      *peg_a = *peg_a + 1;
    } 
  }
  for(int i = 0; i < len; i++){
    for(int j = 0; j < len; j++){
      if(secret[i] == guess[j] && i != j){
        *peg_b = *peg_b + 1;
      }
    }
  }
}

void turn_off_leds(){
  digitalWrite(LED_BLUE_1, LOW);
  digitalWrite(LED_RED_1, LOW);
  digitalWrite(LED_BLUE_2, LOW);
  digitalWrite(LED_RED_2, LOW);
  digitalWrite(LED_BLUE_3, LOW);
  digitalWrite(LED_RED_3, LOW);
  digitalWrite(LED_BLUE_4, LOW);
  digitalWrite(LED_RED_4, LOW);
}

void render_leds(const int peg_a, const int peg_b){
  //char a[4] = "0000";
  int a = 6;
  for(int i = 0; i < peg_a; i++){
    digitalWrite(a, HIGH);
    a = a + 2;
  }
  int b = 13;
  for(int i = 0; i < peg_b; i++){
    digitalWrite(b, HIGH);
    b = b - 2;
  }
}

void render_history(char* secret, char** history, const int entry_nr){
  lcd_clear();
  lcd_print_at(0,0,"HISTORY");
  lcd_print_at(12, 0, history[entry_nr]);
  char entry[2];
  entry[0] = entry_nr + '0';
  entry[1] = '\0';
  lcd_print_at(8, 0, entry);
  int peg_a = 0;
  int peg_b = 0;
  get_score(secret, history[entry_nr], &peg_a, &peg_b);
  char a[2];
  char b[2];
  a[0] = peg_a + '0';
  a[1] = '\0';
  b[0] = peg_b + '0';
  b[1] = '\0';
  lcd_print_at(0,1,a);
  lcd_print_at(3, 1, b);
}

void play_game(char* secret){
    lcd_print_at(0,0,"Welcome to");
    lcd_print_at(3,1,"MasterMind");
    delay(5000);
    lcd_clear();
    char string[50] = "Your goal is to guess my secret combination. ";
    char** history = (char**)calloc(10, sizeof(char));
    for(int i = 0; i < 10; i++){
      history[i] = (char*)calloc(4, sizeof(char));
    }
    delay(1000);
    int len_st = strlen(string);
    /*for(int i = 15; i > 0; i--){
      lcd_set_cursor(i, 1);
      lcd_print(string);
      delay(500);
    }*/
    for(int i = 0; i <= len_st; i++){
      if(digitalRead(BTN_ENTER_PIN) == HIGH){
        delay(500);
        break;
      }
      lcd_set_cursor(0,0);
      lcd_print(string);
      for(int j = 0; j < len_st; j++){
        if(digitalRead(BTN_ENTER_PIN) == HIGH){
          delay(500);
          break;
        }
        if(string[j+1] == '\0'){
          string[j] = ' ';
        } else {
          string[j] = string[j+1];
        }
      }
      if(digitalRead(BTN_ENTER_PIN) == HIGH){
        delay(500);
        break;
      }
      delay(200);
    }
    
    char guess[4] = "0000";
    int peg_a = 0;
    int peg_b = 0;
    int check = 0;
    lcd_print_at(0,0, "Mmm.. number:   ");
    while(1){
      
      lcd_print_at(0,1, "Your guess: ");
      lcd_print_at(12,1, guess);
      //int button_enter = digitalRead(BTN_ENTER_PIN);
      //int button1 = digitalRead(BTN_1_PIN);
      //int button2 = digitalRead(BTN_2_PIN);
      //int button3 = digitalRead(BTN_3_PIN);
      //int button4 = digitalRead(BTN_4_PIN);

      if(digitalRead(BTN_1_PIN) == HIGH && digitalRead(BTN_2_PIN) == HIGH){
        int his = 0;
        delay(500);
        while(digitalRead(BTN_ENTER_PIN) == LOW){
          render_history(secret, history, his);
          delay(3000);
          if(digitalRead(BTN_1_PIN) == HIGH && his < 10){
            his = his + 1;
            delay(500);
          }
          if(digitalRead(BTN_2_PIN) == HIGH && his > 0){
            his = his - 1;
            delay(500);
          }
          //delay(500);
        }
        
        delay(500);
      }
      
      if(digitalRead(BTN_1_PIN) == HIGH){
        guess[0] = guess[0] + 1;
        if((guess[0] - '0') > 9){
          guess[0] = '0';
        }
        delay(500);
      }
      if(digitalRead(BTN_2_PIN) == HIGH){
        guess[1] = guess[1] + 1;
        if((guess[1] - '0') > 9){
          guess[1] = '0';
        }
        delay(500);
      }
      if(digitalRead(BTN_3_PIN) == HIGH){
        guess[2] = guess[2] + 1;
        if((guess[2] - '0') > 9){
          guess[2] = '0';
        }
        delay(500);
      }
      if(digitalRead(BTN_4_PIN) == HIGH){
        guess[3] = guess[3] + 1;
        if((guess[3] - '0') > 9){
          guess[3] = '0';
        }
        delay(500);
      }
      if(digitalRead(BTN_ENTER_PIN) == HIGH){
        for(int i = 0; i < 4; i++){
          history[check][i] = guess[i];
        }
        turn_off_leds();
        get_score(secret, guess, &peg_a, &peg_b);
        render_leds(peg_a, peg_b);
        check = check + 1;
        lcd_clear();
        if(check < 10){
          char check_text[2];
          check_text[0] = check + '0';
          check_text[1] = '\0';
          lcd_print_at(0,0, "0");
          lcd_print_at(1,0, check_text);
        } else {
          int k = 0;
          for(int i =0; i< 4; i++){
            if(secret[i] == guess[i]){
              k = k + 1;
            }
          }
          if(k != 4){
            lcd_print_at(0,0, "10");                                
            lcd_print_at(4,0, guess);
            lcd_print_at(2,0, ":");
            char peg_a_text[3];
            char peg_b_text[3];
            peg_a_text[0] = peg_a + '0';
            peg_a_text[1] = 'A';
            peg_a_text[2] = '\0';
            peg_b_text[0] = peg_b + '0';
            peg_b_text[1] = 'B';
            peg_b_text[2] = '\0';
            lcd_print_at(9,0, peg_a_text);
            lcd_print_at(11,0, peg_b_text);
            lcd_print_at(0,1, "LOX");
            lcd_print_at(7,1, secret);
            lcd_print_at(8,0, " ");
            turn_off_leds();
            digitalWrite(LED_RED_1, HIGH);
            digitalWrite(LED_RED_2, HIGH);
            digitalWrite(LED_RED_3, HIGH);
            digitalWrite(LED_RED_4, HIGH);
            delay(7000);
            if(digitalRead(BTN_ENTER_PIN) == HIGH){
              check = -1;
              turn_off_leds();
              lcd_clear();
              //lcd_print_at(0,0, "Mmm.. number:");
              delay(5000);
              return;
            } else {
              turn_off_leds();
              lcd_clear();
              lcd_print_at(0, 0, "Dmytro");
              lcd_print_at(9, 1, "Havrysh");
              break;
            }
          } else {
            lcd_print_at(2,0, ":");
        lcd_print_at(4,0, guess);
        lcd_print_at(8,0, " ");
        char peg_a_text[3];
        char peg_b_text[3];
        peg_a_text[0] = peg_a + '0';
        peg_a_text[1] = 'A';
        peg_a_text[2] = '\0';
        peg_b_text[0] = peg_b + '0';
        peg_b_text[1] = 'B';
        peg_b_text[2] = '\0';
        lcd_print_at(9,0, peg_a_text);
        lcd_print_at(11,0, peg_b_text);
            lcd_print_at(0,1, "Well done!");
            
            lcd_print_at(12,1, "10");
            lcd_print_at(0,0, "10");
            turn_off_leds();
            digitalWrite(LED_BLUE_1, HIGH);
            digitalWrite(LED_BLUE_2, HIGH);
            digitalWrite(LED_BLUE_3, HIGH);
            digitalWrite(LED_BLUE_4, HIGH);
            delay(7000);
            if(digitalRead(BTN_ENTER_PIN) == HIGH){
              check = 0;
              turn_off_leds();
              lcd_clear();
              //lcd_print_at(0,0, "Mmm.. number:");
              return;
            } else {
              turn_off_leds();
              lcd_clear();
              lcd_print_at(0, 0, "Dmytro");
              lcd_print_at(9, 1, "Havrysh");
              break;
            }
          }
        }
        lcd_print_at(2,0, ":");
        lcd_print_at(4,0, guess);
        lcd_print_at(8,0, " ");
        char peg_a_text[3];
        char peg_b_text[3];
        peg_a_text[0] = peg_a + '0';
        peg_a_text[1] = 'A';
        peg_a_text[2] = '\0';
        peg_b_text[0] = peg_b + '0';
        peg_b_text[1] = 'B';
        peg_b_text[2] = '\0';
        lcd_print_at(9,0, peg_a_text);
        lcd_print_at(11,0, peg_b_text);
        if(peg_a == 4){
          lcd_print_at(0,1, "Well done!");
          char check_text[2];
          check_text[0] = check + '0';
          check_text[1] = '\0';
          lcd_print_at(12,1, check_text);
          turn_off_leds();
          digitalWrite(LED_BLUE_1, HIGH);
          digitalWrite(LED_BLUE_2, HIGH);
          digitalWrite(LED_BLUE_3, HIGH);
          digitalWrite(LED_BLUE_4, HIGH);
          delay(7000);
          if(digitalRead(BTN_ENTER_PIN) == HIGH){
            check = 0;
            turn_off_leds();
            lcd_clear();
            //lcd_print_at(0,0, "Mmm.. number:");
            return;
          } else {
            turn_off_leds();
            lcd_clear();
            lcd_print_at(0, 0, "Dmytro");
            lcd_print_at(9, 1, "Havrysh");
            break;
          }
        }
        guess[0] = '0';
        guess[1] = '0';
        guess[2] = '0';
        guess[3] = '0';
        lcd_print_at(12,1, guess);
        delay(500);
      }
    }
    delay(999999999);
}
