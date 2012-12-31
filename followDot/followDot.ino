/*
  Target Training System
  
  This application runs a firearm training program that uses random timing intervals.
 */

const int redOne = 9;
const int redTwo = 10;
const int redThree = 11;
const int buzzerPin = 12;

int numLoops = 0;
int runFor = 10;
int targetRun = 0;

void setup() 
{                
  //initialize pins
  pinMode(redOne, OUTPUT);
  pinMode(redTwo, OUTPUT);
  pinMode(redThree, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  //wait for 20 seconds
  delay(12000);
}

void loop() 
{
  numLoops += 1;
  targetRun = random(1, 40000);
  
  tone(buzzerPin, 523, 200);  
  
  if(numLoops < runFor)
  {
    if(targetRun < 10000)
    {
      //just redOne
      digitalWrite(redOne, HIGH);
      digitalWrite(redTwo, LOW);
      digitalWrite(redThree, LOW);
    }
    else if(targetRun >= 10000 && targetRun < 20000)
    {
      //just redTwo
      digitalWrite(redOne, LOW); 
      digitalWrite(redTwo, HIGH);
      digitalWrite(redThree, LOW); 
    }
    else if(targetRun >= 20000 && targetRun < 30000)
    {
      //just redThree
      digitalWrite(redOne, LOW); 
      digitalWrite(redTwo, LOW);
      digitalWrite(redThree, HIGH);
    }
    else
    {
      //neither
      digitalWrite(redOne, LOW);
      digitalWrite(redTwo, LOW);
      digitalWrite(redThree, LOW);
    }
    
    //wait a random amount of time before cycling
    delay(random(1500, 2500));
  }
  else
  {
    //reset
    digitalWrite(redOne, LOW);
    digitalWrite(redTwo, LOW);
    digitalWrite(redThree, LOW);
    
    tone(buzzerPin, 523, 200);
    delay(500);
    tone(buzzerPin, 523, 200);
    
    numLoops = 0;
    targetRun = 0;
    
    // wait for 20 seconds
    delay(12000);
  }
}


