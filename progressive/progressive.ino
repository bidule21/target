const int targetOne = 9;
const int targetTwo = 10;
const int targetThree = 11;
const int buzzerPin = 12;
const int debug = 0;

int numLoops = 0;
int runFor = 12;
int currentRun = 0;
int prevRun = 0;
int duplicateCounter = 0;

void setup()
{
  if(debug)
  {
    Serial.begin(9600);
  }

  //initialize pins
  pinMode(targetOne, OUTPUT);
  pinMode(targetTwo, OUTPUT);
  pinMode(targetThree, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  //wait for 20 seconds
  delay(12000);
}

void loop()
{
  if(numLoops < runFor)
  {
    progressivePaceMode();
  }
  else
  {
    targetReset();
    soundBuzzer(3, 500);
    //wait for 20 seconds
    delay(12000);
  }
}

void progressivePaceMode()
{
  soundBuzzer(1, 0);

  turnOnTarget(targetOne + (currentRun % 3));
  delay(2500 - (currentRun * 100));

  currentRun += 1;

  numLoops += 1;
}

void turnOnTarget(int currentTarget)
{
  //turn off all the targets
  digitalWrite(targetOne, LOW);
  digitalWrite(targetTwo, LOW);
  digitalWrite(targetThree, LOW);
  //turn on the sent in target
  digitalWrite(currentTarget, HIGH);
}

void soundBuzzer(int numberOfBuzzes, int interval)
{
  for(int i = 0; i < numberOfBuzzes; i++)
  {
    tone(buzzerPin, 4000, 400);
    delay(interval);
  }
}

void targetReset()
{
    //reset pins
    digitalWrite(targetOne, LOW);
    digitalWrite(targetTwo, LOW);
    digitalWrite(targetThree, LOW);

    numLoops = 0;
    currentRun = 0;
    prevRun = 0;
    duplicateCounter = 0;
}
