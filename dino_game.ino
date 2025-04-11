

// include the library code:
#include <LiquidCrystal.h>
#include <stdbool.h>
// initialize the library by associating any needed LCD interface pin
const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int switchPin=2;
int rel_space_1,rel_space_2,rel_space_3;
int first_tree_pos=15;
float t= 1.0;
bool game_over = false ;
int score = 0;
bool previousButtonState = false;
// Making Graphics
byte dino_pranjal[8] = {
  B01111,
  B01010,
  B01010,
  B01111,
  B01100,
  B11100,
  B11100,
  B11100
};
byte dino[8] = {
  0b01111,
  0b01011,
  0b01001,
  0b01111,
  0b01100,
  0b11100,
  0b11100,
  0b11100
};
byte tree[8] = {
  B00000,
  B10101,
  B10101,
  B10101,
  B11111,
  B00100,
  B00100,
  B00100
};
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

  
void setup()
{ 
  pinMode(switchPin,INPUT);
  lcd.begin(16,2);
  lcd.createChar(0,dino);
  lcd.createChar(1,tree);
  lcd.createChar(2,tree);
  lcd.createChar(3,tree);
  lcd.createChar(4,dino_pranjal);
  //Initial Cursor set
  lcd.setCursor(1,1);
  //Displaying Dino. Fixing it at (0,1)
  lcd.write((byte)0);
  Serial.begin(9600);
  srand(time(0));
  rel_space_1 = (rand()%3)+3;
  rel_space_2 = (rand()%3)+3;
}

void loop() {
  srand(time(0));
  rel_space_3=(rand()%3) +3;
  while(first_tree_pos>=0)
  {
  Serial.print("Rel_Space_1 :");
  Serial.println(rel_space_1);
  Serial.print("Rel_Space_2 :");
  Serial.println(rel_space_2);
  Serial.print("Rel_Space_3 :");
  Serial.println(rel_space_3);
    if(game_over)
    {
     first_tree_pos=2;
     lcd.setCursor(8,1);
     lcd.print("S:");
     lcd.print(score);
     break;
    }
    if((digitalRead(switchPin)==0 && first_tree_pos==2))
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Game Over ! BKL");
      game_over=true;
      break;
     }
    score=score+1;
    lcd.setCursor(8,0);
    lcd.print("S:");
    lcd.print(score);
    t=1.0;
    bool currentButtonState = digitalRead(switchPin);
    Serial.print("Switch_State :");
    Serial.println(currentButtonState);
    Serial.println("****************");
   if(currentButtonState==HIGH && previousButtonState==LOW)
  {
    t=0.5;
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.write((byte)4);
    delay(150);
    lcd.clear();
    lcd.setCursor(1,1);
    lcd.write((byte)0);
    lcd.setCursor(8,0);
    lcd.print("S:");
    lcd.print(score);
  }
  previousButtonState = currentButtonState;
  //Displaying 2 Trees and moving the trees with time
  for(int j=0;j<=15;j++)
  {
    lcd.setCursor(j,1);
    if(j==1){continue;}
    lcd.print(" ");
  }
  lcd.setCursor(first_tree_pos,1);
  lcd.write((byte)1);
  for(int i=1;i<=rel_space_1;i++)
  {
  lcd.print(" ");
  }
  lcd.write((byte)1);
  first_tree_pos=first_tree_pos-1;
  for(int i=1;i<=rel_space_2;i++)
  {
  lcd.print(" ");
  }
  lcd.write((byte)2);
  for(int i=1;i<=rel_space_3;i++)
  {
  lcd.print(" ");
  }
  lcd.write((byte)3);
  lcd.setCursor(1,1);
  lcd.write((byte)0);
  delay(300*t);
  //We need to erase previous copies therefore clear but this also erases our dino
  }
  first_tree_pos=rel_space_1;
  rel_space_1=rel_space_2;
  rel_space_2 = rel_space_3;
  //Serial.println(digitalRead(switchPin));
  }
