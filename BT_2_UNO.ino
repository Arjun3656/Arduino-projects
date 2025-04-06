#include "SoftwareSerial.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
SoftwareSerial Serial1(10,11);
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int ENA = 2;
const int ENB = 7;
const int IN1 = 3;
const int IN2 = 4;
const int IN3 = 5;
const int IN4 = 6;
const int FrontLEd = A1;
const int BackLED = A2;
const int HORN= A0;
int motorSpeed = 150;
char receivedChar;
void setup() {
  pinMode(ENB, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(HORN, OUTPUT);
  pinMode(FrontLEd, OUTPUT);
  pinMode(BackLED, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600); 
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setBacklight(HIGH);
  lcd.setCursor(3, 0);
  lcd.print("Welcome To");
  lcd.setCursor(0, 1);
  lcd.print("Arjuna's Project");
  
}

void loop() {
  if (Serial1.available()) {
    receivedChar = Serial1.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);
    switch (receivedChar) {
    case 'F':
    lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Forward");
      moveForward();
      break;
    case 'B':
    lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Backward");
      moveBackward();
      break;
    case 'L':
    lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Left");
      turnLeft();
      break;
    case 'R':
    lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Right");
      turnRight();
      break;
    case 'S':
    lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Stop");
      stopMotors();
      break;
    case 'W':
      lcd.setCursor(0, 1);
      lcd.print("Front Light on  ");
      ONLED_F();
      break;
    case 'w':
      lcd.setCursor(0, 1);
      lcd.print("Front Light off");
      OFFLed_F();
      break;
    case 'U':
      lcd.setCursor(0, 1);
      lcd.print("Back Light on  ");
      ON_LEDB();
      break;
    case 'u':
      lcd.setCursor(0, 1);
      lcd.print("Back Light off");
      Off_LEDB();
      break;
    case 'V':
      lcd.setCursor(0, 1);
      lcd.print("Horn On       ");
      Hornon();
      break;
    case 'v':
      lcd.setCursor(0, 1);
      lcd.print("Horn off      ");
      Hornoff();
      break;


    case '+':
      if (motorSpeed < 255) {
        motorSpeed += 10;
      }
      lcd.setCursor(0, 1);
      lcd.print("Speed: ");
      lcd.print(motorSpeed);
      break;
    case '-':
      if (motorSpeed > 0) {
        motorSpeed -= 10; 
      }
      lcd.setCursor(0, 1);
      lcd.print("Speed: ");
      lcd.print(motorSpeed);
      break;
    default:
      break;
  }
  
  }
  
}
void moveForward(){
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}
void moveBackward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void turnLeft(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void turnRight(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void stopMotors(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void Hornon(){
  digitalWrite(HORN, HIGH);
}
void Hornoff(){
  digitalWrite(HORN, LOW);
}
void ONLED_F(){
  digitalWrite(FrontLEd, HIGH);
}
void OFFLed_F(){
  digitalWrite(FrontLEd, LOW);
}
void ON_LEDB(){
  digitalWrite(BackLED, HIGH);
}

void Off_LEDB(){
  digitalWrite(BackLED, LOW);
}



