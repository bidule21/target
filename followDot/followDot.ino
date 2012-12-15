/*
  Target Training System
  
  This application runs a firearm training program that uses random timing intervals.
 */

int redOne = 9;
int redTwo = 10;
int numLoops = 0;
int runFor = 10;
int targetRun = 0;

void setup() 
{                
  // Initialize pins
  pinMode(redOne, OUTPUT);
  pinMode(redTwo, OUTPUT);

  // Turn them on for 20 seconds initially
  digitalWrite(redOne, HIGH);
  digitalWrite(redTwo, HIGH);
  delay(12000);
  digitalWrite(redOne, LOW);
  digitalWrite(redTwo, LOW);
}

void loop() 
{
  numLoops += 1;
  targetRun = random(1, 40000);
  
  if(numLoops < runFor)
  {
    if(targetRun < 10000)
    {
      //just redOne
      digitalWrite(redOne, HIGH);
      digitalWrite(redTwo, LOW);
    }
    else if(targetRun >= 10000 && targetRun < 20000)
    {
      //just redTwo
      digitalWrite(redTwo, LOW); 
      digitalWrite(redTwo, HIGH); 
    }
    else if(targetRun >= 20000 && targetRun < 30000)
    {
      //both redOne and redTwo
      digitalWrite(redOne, HIGH);
      digitalWrite(redTwo, HIGH);
    }
    else
    {
      //neither
      digitalWrite(redOne, LOW);
      digitalWrite(redTwo, LOW);
    }
    
    //wait a random amount of time before cycling
    delay(random(1500, 2500));
  }
  else
  {
    //AUTO RESET
    for(int i = 0; i < 8; i++)
    {
      digitalWrite(redOne, HIGH);
      digitalWrite(redTwo, HIGH);
      delay(500);
      digitalWrite(redOne, LOW);
      digitalWrite(redTwo, LOW);
      delay(500);
    }
    
    numLoops = 0;
    targetRun = 0;
    
    delay(18000);
  }
}


