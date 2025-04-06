#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ENA = 2;
const int ENB = 7;
const int IN1 = 3;
const int IN2 = 4;
const int IN3 = 5;
const int IN4 = 6;
const int FrontLED = 24;
const int BackLED = 8;
const int HORN = 22;

int motorSpeed = 150;
int joyX, joyY;  // Joystick values
char receivedChar;

void setup() {
  pinMode(ENB, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(HORN, OUTPUT);
  pinMode(FrontLED, OUTPUT);
  pinMode(BackLED, OUTPUT);

  Serial.begin(9600);  // Start the serial monitor for debugging
  Serial1.begin(38400);// Start Bluetooth communication with the HC-05 module

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
    Serial.println(receivedChar);
    switch (receivedChar) {
      case 'F':  // Front LED on
        lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Forward");
      moveForward();
        break;
      case 'B':  // Front LED on
        lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Backward");
      moveBackward();
        break;
      case 'R':  // Front LED on
        lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Right");
      turnRight();
        break;
      case 'L':  // Front LED on
        lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Left");
      turnLeft();
        break;
      case 'S':  // Front LED on
        lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Stop");
      stopMotors();
        break;
      case 'W':  // Front LED on
        lcd.setCursor(0, 1);
        lcd.print("Front Light on");
        ONLED_F();
        break;
      case 'w':  // Front LED off
        lcd.setCursor(0, 1);
        lcd.print("Front Light off");
        OFFLed_F();
        break;
      case 'U':  // Back LED on
        lcd.setCursor(0, 1);
        lcd.print("Back Light on");
        ON_LEDB();
        break;
      case 'u':  // Back LED off
        lcd.setCursor(0, 1);
        lcd.print("Back Light off");
        Off_LEDB();
        break;
      case 'V':  // Horn on
        lcd.setCursor(0, 1);
        lcd.print("Horn On");
        Hornon();
        break;
      case 'v':  // Horn off
        lcd.setCursor(0, 1);
        lcd.print("Horn off");
        Hornoff();
        break;
      default:
        break;
    }
 }
}

void moveForward() {
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Hornon() {
  digitalWrite(HORN, HIGH);
}

void Hornoff() {
  digitalWrite(HORN, LOW);
}

void ONLED_F() {
  digitalWrite(FrontLED, HIGH);
}

void OFFLed_F() {
  digitalWrite(FrontLED, LOW);
}

void ON_LEDB() {
  digitalWrite(BackLED, HIGH);
}

void Off_LEDB() {
  digitalWrite(BackLED, LOW);
}
