#include <SoftwareSerial.h>

SoftwareSerial BTserial(10, 11);  // RX, TX (Bluetooth communication pins)

int joyX, joyY;  // Joystick values

void setup() {
  Serial.begin(9600);         // Start the serial monitor for debugging
  BTserial.begin(38400);       // Start Bluetooth communication with the HC-05 module
}

void loop() {
  joyX = analogRead(A0);      // Read the horizontal joystick value (X-axis)
  joyY = analogRead(A1);      // Read the vertical joystick value (Y-axis)

  // Map joystick values to a range of -255 to 255 for easier use
  int mappedX = map(joyX, 0, 1023, -255, 255);
  int mappedY = map(joyY, 0, 1023, -255, 255);

  // Send joystick values over Bluetooth to the Slave HC-05
  BTserial.write(mappedX);    // Send X-axis joystick value
  BTserial.write(mappedY);    // Send Y-axis joystick value

  // Debugging: print the joystick values to the Serial Monitor
  Serial.print("X: ");
  Serial.print(mappedX);
  Serial.print(", Y: ");
  Serial.println(mappedY);

  delay(2000);  // Delay to control the data rate (in ms)
}
