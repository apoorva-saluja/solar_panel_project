#include <Servo.h>  // Include Servo library

// Servo objects
Servo horizontal; // Horizontal servo
Servo vertical;   // Vertical servo

// Initial servo positions
int servoh = 180;
int servov = 45;

// Servo movement limits
int servohLimitHigh = 180;
int servohLimitLow = 65;

int servovLimitHigh = 80;
int servovLimitLow = 15;

// LDR pin connections
int ldrlt = 0; // LDR top left (Bottom left on board)
int ldrrt = 1; // LDR top right (Bottom right)
int ldrld = 2; // LDR down left (Top left)
int ldrrd = 3; // LDR down right (Top right)

void setup() {
  Serial.begin(9600); // Initialize serial monitor

  // Attach servos to pins
  horizontal.attach(9);
  vertical.attach(10);

  // Move servos to initial positions
  horizontal.write(servoh);
  vertical.write(servov);

  delay(3000); // Allow time to stabilize
}

void loop() {
  // Read values from LDRs
  int lt = analogRead(ldrlt); // Top left
  int rt = analogRead(ldrrt); // Top right
  int ld = analogRead(ldrld); // Down left
  int rd = analogRead(ldrrd); // Down right

  int dtime = 10;  // Delay time
  int tol = 50;    // Tolerance

  // Average values
  int avt = (lt + rt) / 2; // Top average
  int avd = (ld + rd) / 2; // Bottom average
  int avl = (lt + ld) / 2; // Left average
  int avr = (rt + rd) / 2; // Right average

  // Differences
  int dvert = avt - avd;   // Vertical difference
  int dhoriz = avl - avr;  // Horizontal difference

  // Debug prints
  Serial.print(avt); Serial.print(" ");
  Serial.print(avd); Serial.print(" ");
  Serial.print(avl); Serial.print(" ");
  Serial.print(avr); Serial.print(" ");
  Serial.print(dtime); Serial.print(" ");
  Serial.print(tol); Serial.println(" ");

  // Vertical movement logic
  if (abs(dvert) > tol) {
    if (avt > avd) {
      servov++;
      if (servov > servovLimitHigh) servov = servovLimitHigh;
    } else if (avt < avd) {
      servov--;
      if (servov < servovLimitLow) servov = servovLimitLow;
    }
    vertical.write(servov);
  }

  // Horizontal movement logic
  if (abs(dhoriz) > tol) {
    if (avl > avr) {
      servoh--;
      if (servoh < servohLimitLow) servoh = servohLimitLow;
    } else if (avl < avr) {
      servoh++;
      if (servoh > servohLimitHigh) servoh = servohLimitHigh;
    }
    horizontal.write(servoh);
  }

  delay(dtime);
}
