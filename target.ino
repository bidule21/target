/*
  
 */
int green = 9;
int red = 10;

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);  
}

void loop() {
  halt();
  delay(1000);              // wait for a second
  shoot();
  delay(1000);              // wait for a second
}

void shoot() {
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
}

void halt() {
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
}
