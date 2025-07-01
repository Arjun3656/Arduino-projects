#include <Servo.h>

// Motor A (Left)
const int ENA = 2;
const int IN1 = 3;
const int IN2 = 4;

// Motor B (Right)
const int ENB = 5;
const int IN3 = 6;
const int IN4 = 7;

// Servos
Servo servo1; // Arm
Servo servo2; // Gripper

// RGB LED Pins (PWM)
const int frontRed = A4;
const int frontGreen = A5;
const int frontBlue = A6;

const int backRed = A7;
const int backGreen = A8;
const int backBlue = A9;

// Joystick Pins
const int joyMoveX = A0;
const int joyMoveY = A1;
const int joyArmY  = A2;
const int joyArmX  = A3;
const int joyButton = A10;  // Push button pin

// Servo Angles
int armAngle = 90;
int gripAngle = 90;
int lastArmAngle = 90;
int lastGripAngle = 90;

const int center = 512;
const int threshold = 50;

// Debounce
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

// RGB Color Structure
struct RGBColor {
  int r, g, b;
};

// Define multiple RGB colors
RGBColor frontColors[] = {
  {255, 0, 0},    // Red
  {0, 255, 0},    // Green
  {0, 0, 255},    // Blue
  {0, 255, 255},  // Cyan
  {255, 0, 255},  // Magenta
  {255, 255, 0},  // Yellow
  {0, 0, 0}       // OFF
};

RGBColor backColors[] = {
  {0, 255, 255},  // Cyan
  {255, 128, 0},  // Orange
  {128, 0, 255},  // Purple
  {0, 255, 128},  // Mint
  {255, 0, 255},  // Magenta
  {0, 0, 255},    // Blue
  {0, 0, 0}       // OFF
};


const int numColors = sizeof(frontColors) / sizeof(frontColors[0]);
int colorIndex = 0;

void setup() {
  Serial.begin(9600);

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();

  // Attach servos
  servo1.attach(11);
  servo2.attach(10);
  servo1.write(armAngle);
  servo2.write(gripAngle);

  // RGB LED pins
  pinMode(frontRed, OUTPUT);
  pinMode(frontGreen, OUTPUT);
  pinMode(frontBlue, OUTPUT);
  pinMode(backRed, OUTPUT);
  pinMode(backGreen, OUTPUT);
  pinMode(backBlue, OUTPUT);

  // Joystick button
  pinMode(joyButton, INPUT_PULLUP);
}

void loop() {
  // Movement control
  int x1 = analogRead(joyMoveX) - center;
  int y1 = analogRead(joyMoveY) - center;

  if (abs(x1) < threshold) x1 = 0;
  if (abs(y1) < threshold) y1 = 0;

  if (y1 > 0 && x1 == 0) moveForward();
  else if (y1 < 0 && x1 == 0) moveBackward();
  else if (x1 > 0 && y1 == 0) turnRight();
  else if (x1 < 0 && y1 == 0) turnLeft();
  else stopMotors();

  // Joystick button to cycle colors
  bool reading = digitalRead(joyButton);
  if (reading == LOW && lastButtonState == HIGH && millis() - lastDebounceTime > debounceDelay) {
    colorIndex = (colorIndex + 1) % numColors;
    lastDebounceTime = millis();
  }
  lastButtonState = reading;

  // Set RGB LEDs to current color
  setRGB(frontRed, frontGreen, frontBlue,
         frontColors[colorIndex].r,
         frontColors[colorIndex].g,
         frontColors[colorIndex].b);

  setRGB(backRed, backGreen, backBlue,
         backColors[colorIndex].r,
         backColors[colorIndex].g,
         backColors[colorIndex].b);

  // Arm & Gripper control
  int x2 = analogRead(joyArmX);
  int y2 = analogRead(joyArmY);

  armAngle = map(y2, 0, 1023, 0, 180);
  gripAngle = map(x2, 0, 1023, 0, 180);

  if (abs(armAngle - lastArmAngle) > 2) {
    servo1.write(armAngle);
    lastArmAngle = armAngle;
    delay(10);
  }

  if (abs(gripAngle - lastGripAngle) > 2) {
    servo2.write(gripAngle);
    lastGripAngle = gripAngle;
    delay(10);
  }

  delay(50);
}

// RGB LED control
void setRGB(int rPin, int gPin, int bPin, int rVal, int gVal, int bVal) {
  analogWrite(rPin, rVal);
  analogWrite(gPin, gVal);
  analogWrite(bPin, bVal);
}

// Motor control
void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

void moveForward() {
  digitalWrite(ENA, HIGH); digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(ENA, HIGH); digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(ENA, HIGH); digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(ENA, HIGH); digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}
