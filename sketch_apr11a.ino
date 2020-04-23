#include <Arduino.h>

const char* sixty[] = {
  "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
  "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
  "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
  "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
  "40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
  "50", "51", "52", "53", "54", "55", "56", "57", "58", "59",
  "00"
};

bool butt_flag_one = 0;
bool butt_flag_two = 0;
bool butt_flag_three = 0;
bool butt_flag_four = 0;

boolean allowed_timer1 = 0;
boolean allowed_timer2 = 0;
boolean switchTimer = false;

int buzzer = 32;
int turnOnBuzzer = 0;
int counter_buzzer = 0;

int A  = 53;
int B  = 52;
int C  = 51;
int D  = 50;
int E  = 10;
int F  = 11;
int G  = 12;
int DP = 13;

int digit_one   = 21;
int digit_two   = 20;
int digit_three = 19;
int digit_four  = 18;
int digit_five  = 0;
int digit_six   = 1;      

int button1 = 24;
int button2 = 25;
int button3 = 26;
int button4 = 27;

int digits[6] = {digit_one, digit_two, digit_three, digit_four, digit_five, digit_six};

int current_digit = 0;

boolean button1_state;
boolean button2_state;
boolean button3_state;
boolean button4_state;

int count_clicks = 0;
bool flag;

struct TimerOne {
  int hour;
  int minute;
  int second;
};

struct TimerTwo {
  unsigned char hour;
  unsigned char minute;
  unsigned char second;
};

TimerOne timerOne = { 0, 0, 0 };

TimerTwo timerTwo = { 0, 0, 0 };

int counter = 0;

void outputNumber(int number) 
{
  switch(number){
    case 0:
      digitalWrite(A, LOW);   
      digitalWrite(B, LOW);   
      digitalWrite(C, LOW);   
      digitalWrite(D, LOW);   
      digitalWrite(E, LOW);   
      digitalWrite(F, LOW);   
      digitalWrite(G, HIGH);  
      digitalWrite(DP, HIGH);  
      break;
    case 1:
      digitalWrite(A, HIGH);   
      digitalWrite(B, LOW);   
      digitalWrite(C, LOW);   
      digitalWrite(D, HIGH);   
      digitalWrite(E, HIGH);   
      digitalWrite(F, HIGH);   
      digitalWrite(G, HIGH);  
      digitalWrite(DP, HIGH); 
      break;
    case 2:
      digitalWrite(A, LOW);   
      digitalWrite(B, LOW);   
      digitalWrite(C, HIGH);   
      digitalWrite(D, LOW);   
      digitalWrite(E, LOW);   
      digitalWrite(F, HIGH);   
      digitalWrite(G, LOW);  
      digitalWrite(DP, HIGH); 
      break;
    case 3:
      digitalWrite(A, LOW);   
      digitalWrite(B, LOW);   
      digitalWrite(C, LOW);   
      digitalWrite(D, LOW);   
      digitalWrite(E, HIGH);   
      digitalWrite(F, HIGH);   
      digitalWrite(G, LOW);  
      digitalWrite(DP, HIGH); 
      break;
     case 4:
      digitalWrite(A, HIGH);   
      digitalWrite(B, LOW);   
      digitalWrite(C, LOW);   
      digitalWrite(D, HIGH);   
      digitalWrite(E, HIGH);   
      digitalWrite(F, LOW);   
      digitalWrite(G, LOW);  
      digitalWrite(DP, HIGH);
      break;
     case 5:
      digitalWrite(A, LOW);   
      digitalWrite(B, HIGH);   
      digitalWrite(C, LOW);   
      digitalWrite(D, LOW);   
      digitalWrite(E, HIGH);   
      digitalWrite(F, LOW);   
      digitalWrite(G, LOW);  
      digitalWrite(DP, HIGH);
      break;
     case 6:
      digitalWrite(A, LOW);   
      digitalWrite(B, HIGH);   
      digitalWrite(C, LOW);   
      digitalWrite(D, LOW);   
      digitalWrite(E, LOW);   
      digitalWrite(F, LOW);   
      digitalWrite(G, LOW);  
      digitalWrite(DP, HIGH);
      break;
     case 7:
      digitalWrite(A, LOW);   
      digitalWrite(B, LOW);   
      digitalWrite(C, LOW);   
      digitalWrite(D, HIGH);   
      digitalWrite(E, HIGH);   
      digitalWrite(F, HIGH);   
      digitalWrite(G, HIGH);  
      digitalWrite(DP, HIGH);
      break;
     case 8:
      digitalWrite(A, LOW);   
      digitalWrite(B, LOW);   
      digitalWrite(C, LOW);   
      digitalWrite(D, LOW);   
      digitalWrite(E, LOW);   
      digitalWrite(F, LOW);   
      digitalWrite(G, LOW);  
      digitalWrite(DP, HIGH);
      break;
     case 9:
      digitalWrite(A, LOW);   
      digitalWrite(B, LOW);   
      digitalWrite(C, LOW);   
      digitalWrite(D, LOW);   
      digitalWrite(E, HIGH);   
      digitalWrite(F, LOW);   
      digitalWrite(G, LOW);  
      digitalWrite(DP, HIGH);
      break;
  }
}

ISR(TIMER0_COMPA_vect) {
  if (counter <= 2) {
    counter++;
  } else {
   
      if (allowed_timer1 == 1) {
        if (timerOne.second == 0 && timerOne.minute != 0) {
          timerOne.minute--;
        } else if (timerOne.second == 0 && timerOne.minute == 0 && timerOne.hour != 0) {
          timerOne.minute = 59;
          timerOne.hour--;
        }
        if (++timerOne.second == 60) {
          timerOne.second = 0;
          if (timerOne.minute != 0) {
            timerOne.minute--;
          } else if (timerOne.minute == 0) {
            if (timerOne.hour != 0) {
              timerOne.minute = 60;
              timerOne.hour--;
            } else if (timerOne.hour == 0) {
              timerOne.hour = 0;
              allowed_timer1 = 0;
              turnOnBuzzer = 1;
            }
          }
        }
      }
     
      if (allowed_timer2 == 1) {
        if (timerTwo.second == 0 && timerTwo.minute != 0) {
          timerTwo.minute--;
        } else if (timerTwo.second == 0 && timerTwo.minute == 0 && timerTwo.hour != 0) {
          timerTwo.minute = 59;
          timerTwo.hour--;
        }
        if (++timerTwo.second == 60) {
          timerTwo.second = 0;
          if (timerTwo.minute != 0) {
            timerTwo.minute--;
          } else if (timerTwo.minute == 0) {
            if (timerTwo.hour != 0) {
              timerTwo.minute = 60;
              timerTwo.hour--;
            } else if (timerTwo.hour == 0) {
              timerTwo.hour = 0;
              allowed_timer2 = 0;
              turnOnBuzzer = 1;
            }
          }
        }
      }
    

    if (turnOnBuzzer == 1) {
      if ((counter_buzzer % 2) == 0) {
          digitalWrite(buzzer, HIGH);
          counter_buzzer++;
        } else {
          digitalWrite(buzzer, LOW);
          counter_buzzer++;
        }
        if (counter_buzzer == 30) {
          digitalWrite(buzzer, LOW);
          turnOnBuzzer = 0;
        }
      }

   counter = 0;
  } 
}


ISR(TIMER1_COMPA_vect)
{
  clearLEDs();

  if (current_digit < 6) {
    
    if (switchTimer == true) {
      if (allowed_timer1 == 1) {
        outputSecond(sixty[60 - timerOne.second], current_digit, current_digit);
        outputHour(sixty[timerOne.hour], current_digit, current_digit); 
        
        if (timerOne.minute == 0) {
          outputMinute(sixty[60], current_digit, current_digit); 
        } else {
          outputMinute(sixty[timerOne.minute], current_digit, current_digit); 
        }
      } else {
        outputHour(sixty[timerOne.hour], current_digit, current_digit); 
        outputMinute(sixty[timerOne.minute], current_digit, current_digit);
        outputSecond(sixty[timerOne.second], current_digit, current_digit);
      }
    } else if (switchTimer == false) {
      if (allowed_timer2 == 1) {
        outputSecond(sixty[60 - timerTwo.second], current_digit, current_digit);
        outputHour(sixty[timerTwo.hour], current_digit, current_digit); 
        
        if (timerTwo.minute == 0) {
          outputMinute(sixty[60], current_digit, current_digit); 
        } else {
          outputMinute(sixty[timerTwo.minute], current_digit, current_digit); 
        }
      } else {
        outputHour(sixty[timerTwo.hour], current_digit, current_digit); 
        outputMinute(sixty[timerTwo.minute], current_digit, current_digit);
        outputSecond(sixty[timerTwo.second], current_digit, current_digit);
      }
    }

    switch (current_digit) {
      case 1:
        digitalWrite(DP, LOW);
        break;
      case 3:
        digitalWrite(DP, LOW);
        break;
    }
    
    current_digit++;

    } else {
      current_digit = 0;
  }
}

void clearLEDs() //clear the 7-segment display screen
{
  digitalWrite(digit_one, LOW);
  digitalWrite(digit_two, LOW);
  digitalWrite(digit_three, LOW);
  digitalWrite(digit_four, LOW);
  digitalWrite(digit_five, LOW);
  digitalWrite(digit_six, LOW);
}

void setup() 
{
  noInterrupts();

  TCCR1A = 0x00;
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
  TIMSK1 = (1 << OCIE1A);
  OCR1A = 0x5;

  TCCR0A = 0x00;
  TCCR0B = (1 << WGM02) | (1 << CS00) | ( 1<<CS02);
  TIMSK0 = (1 << OCIE0A);
  OCR0A = 0xFF;
  
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);

  pinMode(digit_one, OUTPUT);
  pinMode(digit_two, OUTPUT);
  pinMode(digit_three, OUTPUT);
  pinMode(digit_four, OUTPUT);
  pinMode(digit_five, OUTPUT);
  pinMode(digit_six, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);

  interrupts();
}

void default_screen(int dig) {
  outputNumber(0);
  digitalWrite(digits[dig], HIGH);
}

int charToInt(char c){
  return c - '0';
}

void outputHour(const char *hour, int digit_one, int digit_two) {
  if (strlen(hour) <= 2 && atoi(hour) <= 59) {
    int num_one = charToInt(hour[0]);
    int num_two = charToInt(hour[1]); 
    
    if (digit_one == 0) {
      outputNumber(num_one);
      digitalWrite(digits[digit_one], HIGH);
    }
    if (digit_two == 1) {
      outputNumber(num_two);
      digitalWrite(digits[digit_two], HIGH);
    }
  }
}

void outputMinute(const char *minute, int digit_one, int digit_two) {
  if (strlen(minute) <= 2 && atoi(minute) <= 59) {
    int num_one = charToInt(minute[0]);
    int num_two = charToInt(minute[1]); 

    if (digit_one == 2) {
      outputNumber(num_one);
      digitalWrite(digits[digit_one], HIGH);
    }
    if (digit_two == 3) {
      outputNumber(num_two);
      digitalWrite(digits[digit_two], HIGH);
    }
  }
}

void outputSecond(const char *second, int digit_one, int digit_two) {
  if (strlen(second) <= 2 && atoi(second) <= 59) {
    int num_one = charToInt(second[0]);
    int num_two = charToInt(second[1]); 

    if (digit_one == 4) {
      outputNumber(num_one);
      digitalWrite(digits[digit_one], HIGH);
    }
    if (digit_two == 5) {
      outputNumber(num_two);
      digitalWrite(digits[digit_two], HIGH);
    }
  }
}

void loop()
{
  button1_state = !digitalRead(button1);
  button2_state = !digitalRead(button2);
  button3_state = !digitalRead(button3);
  button4_state = !digitalRead(button4);


  // button 1
  if (button1_state != butt_flag_one) {
    if (button1_state == 1) {
      if (switchTimer == true) {
        if (timerOne.hour < 24) {
          timerOne.hour++; 
        } else {
          timerOne.hour = 0;
        } 
      } else if (switchTimer == false) {
        if (timerTwo.hour < 24) {
          timerTwo.hour++; 
        } else {
          timerTwo.hour = 0;
        } 
      }
    } 
  }
  
  butt_flag_one = button1_state;


  // button 2
  if (button2_state != butt_flag_two) {
    if (button2_state == 1) {
      if (switchTimer == true) {
        if (timerOne.minute < 59) {
          timerOne.minute++;
        } else {
          timerOne.minute = 0;
        } 
      } else if (switchTimer == false) {
        if (timerTwo.minute < 59) {
          timerTwo.minute++;
        } else {
          timerTwo.minute = 0;
        } 
      }
    }
  }

  butt_flag_two = button2_state;


  //button 3
  if (button3_state == 1 && butt_flag_three == 0) {
    butt_flag_three = 1;
    switchTimer = !switchTimer; 
  }
  if (button3_state == 0 && butt_flag_three == 1) {
    butt_flag_three = 0;
  }


  // button 4
  if (button4_state == 1 && butt_flag_four == 0) {
    butt_flag_four = 1;
    if (switchTimer == true) {
      allowed_timer1 = !allowed_timer1;
      if (allowed_timer1 == 0) {
        timerOne.hour = 0;
        timerOne.minute = 0;
        timerOne.second = 0;
      } 
    } else if (switchTimer == false) {
      allowed_timer2 = !allowed_timer2;
      if (allowed_timer2 == 0) {
        timerOne.hour = 0;
        timerOne.minute = 0;
        timerOne.second = 0;
      } 
    }
  }
  if (button4_state == 0 && butt_flag_four == 1) {
    butt_flag_four = 0;
  }
}
