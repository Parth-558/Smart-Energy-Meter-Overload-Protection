#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);  // I2C address 

const int potpin = A0;
const int  redpin = 7;
const int  greenpin = 6;
const int  resetbutton = 2;
const int  buzzerpin = 8;

float current = 0.0;
float  threeshold = 10.0;
bool overloaded = false;

void setup(){
 Serial.begin(9600);
  pinMode(redpin,OUTPUT);
  pinMode(greenpin,OUTPUT);
  pinMode(buzzerpin,OUTPUT);
  pinMode(resetbutton,INPUT_PULLUP);
  
  lcd.begin(16,2);
  lcd.setBacklight(1);
  lcd.setCursor(0,0);
  lcd.print("smart Energy: ");
  lcd.setCursor(0,1);
  lcd.print("System Starting...");
  lcd.clear();
  delay(2000);
}
void loop(){
 int potvalue = analogRead(potpin);
 current = map(potvalue,0,1023,0,2000)/100.0;
 
 Serial.print("Analog: ");
 Serial.print(potvalue);
 Serial.print(" -> current: ");
 Serial.print(current);
  
  if (!overloaded){
  if (current > threeshold){
     overloaded = true;
    triggerOverload();
  }else {
   normalOperation(); 
  }
  }
  else{
       showOverloadStatus(); 
    if (digitalRead(resetbutton == LOW)){
       delay(300);
      overloaded = false;
      lcd.clear();
      digitalWrite(redpin,LOW);
       digitalWrite(buzzerpin,LOW);
    }
  }
  delay(500);
}
void normalOperation() {
  digitalWrite(greenpin, HIGH);
  digitalWrite(redpin, LOW);
  digitalWrite( buzzerpin , LOW);

  lcd.setCursor(0, 0);
  lcd.print("Current: ");
  lcd.print(current, 1);
  lcd.print(" A     ");

  lcd.setCursor(0, 1);
  lcd.print("Status: Normal  ");
}

void triggerOverload() {
  digitalWrite(greenpin, LOW);
  digitalWrite(redpin, HIGH);
  digitalWrite( buzzerpin, HIGH);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Overload!");
  lcd.setCursor(0, 1);
  lcd.print("System Halted");
}

void showOverloadStatus() {
  digitalWrite(greenpin, LOW);
  digitalWrite(redpin, HIGH);
  digitalWrite( buzzerpin, HIGH);

  lcd.setCursor(0, 0);
  lcd.print("Current: ");
  lcd.print(current, 1);
  lcd.print(" A     ");

  lcd.setCursor(0, 1);
  lcd.print("Press Reset Btn");
}
