//ankoder
#define S1 5
#define S2 6
#define key 7

//lcd
#define _LCD_TYPE 1


#include <LCD_1602_RUS_ALL.h>
LCD_1602_RUS lcd(0x27, 16, 2);

bool buttonWasUp = false;
bool flag;
int prevS1;
int curS1, curS2;
int val=0;

bool buttUp=false;
int curKey;
unsigned long whenKeyPress = 0;

void setup() {
  lcd.init(); 
  lcd.backlight();
  Serial.begin(9600);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  prevS1=digitalRead(S1);
  lcd.setCursor(0, 1);
  lcd.print("Выкл.");
}

void loop() {
  if(buttonWasUp==true) encoder();
  
  curKey= digitalRead(key);
  if(curKey==LOW){
    if(buttUp==false){
      if(millis()- whenKeyPress>50){
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Вкл.");
        lcd.setCursor(0, 0);
        lcd.print(val, DEC);
        buttUp=true;
        buttonWasUp=true;
      }
      whenKeyPress=millis();
    }
    else{
      if(millis()- whenKeyPress>50){
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Выкл.");
        buttUp=false;
        buttonWasUp=false;
        val=0;
      }
      whenKeyPress=millis();  
    }
  }
}

void encoder(){
  curS1=digitalRead(S1);
  if(curS1!=prevS1){
    curS2=digitalRead(S2);
    if(flag){
      if(curS2==curS1)
      {
        if(val>18){
          val=0;
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("Вкл.");
        }
        else val++;
      }
      else{
        if(val<1){
          val=20;
        }
        if(val<=14){
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("Вкл.");
          val--;
        }
        else val--;
      }
      lcd.setCursor(0, 0);
      lcd.print(val, DEC);
      lcd.setCursor(0, 1);
      lcd.print("Вкл.");
      flag=false;
    }
    else{
      flag=true;
    }
  }
  prevS1=curS1;
}
