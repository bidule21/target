const int targetOne = 9;
const int targetTwo = 10;
const int targetThree = 11;
const int buzzerPin = 12;
const int debug = 1;

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
        followDotMode();
        //progressivePaceMode();
        //anticipationMode();
    }
    else
    {
        targetReset();
        soundBuzzer(3, 500);
        //wait for 20 seconds
        delay(12000);
    }
}

void followDotMode()
{
    prevRun = currentRun;
    //will be truncated to int between 0 - 2
    currentRun = random(1, 30000) / 10000;


    //only update the target if we are below the max number of dupes
    if(duplicateCounter < 2)
    {
        if (debug)
        {
            Serial.println("Target Updated");
        }

        soundBuzzer(1, 0);

        if (currentRun == 0)
        {
            turnOnTarget(targetOne);
        }
        else if (currentRun == 1)
        {
            turnOnTarget(targetTwo);
        }
        else
        {
            turnOnTarget(targetThree);
        }

        //wait a random amount of time before cycling
        delay(random(1500, 2500));
        numLoops += 1;
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

void anticipationMode()
{

}

/**
 * Checks to see if we have more than two duplicate runs
 * param int currentRun
 * param int previousRun
 * return bool
 */
void (int currentRun, int previousRun)
{
    //check on duplicates
    if (previousRun == currentRun)
    {
        duplicateCounter += 1;
    }
    else
    {
        duplicateCounter = 0;
    }

    if (debug)
    {
        Serial.println(currentRun);
        Serial.print("# dupes - ");
        Serial.println(duplicateCounter);
    }

    if (duplicateCounter < 2)
    {
        return false;
    }
    return true;
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
    for (int i = 0; i < numberOfBuzzes; i++)
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

