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
  //initialize pins
  pinMode(redOne, OUTPUT);
  pinMode(redTwo, OUTPUT);
  
  //wait for 20 seconds
  delay(12000);
}

void loop() 
{
  numLoops += 1;
  targetRun = random(1, 30000);
  
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
      digitalWrite(redOne, LOW); 
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
    //reset
    digitalWrite(redOne, LOW);
    digitalWrite(redTwo, LOW);
    numLoops = 0;
    targetRun = 0;
    
    // wait for 20 seconds
    delay(12000);
  }
}


