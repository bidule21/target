/*
  Target Training System
  
  This application runs a firearm training program that uses random timing intervals.
 */

int green = 9;
int red = 10;

void setup() {                
  // Initialize pins
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);

  // Turn them on for 5 seconds initially to signal the training is starting.
  digitalWrite(green, HIGH);
  digitalWrite(red, HIGH);
  delay(3000);
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
}

void loop() {
  delay(random(3000,7000));
  shoot();
  halt();
}

void shoot() {
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
  delay(random(2000,3000));
}

void halt() {
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  delay(1500);
  digitalWrite(red, LOW);
}
