const int targetOne = 2;
const int targetTwo = 3;
const int targetThree = 4;
const int buzzerPin = 5;
const int gameModeOne = 6;
const int gameModeTwo = 7;
const int gameModeThree = 8;
const int gameModeFour = 9;

const int debug = 0;

/*
    12 loops seems to be about right for a full
    size double-stack pistol at a medium pace.
    If you are really going to burn it down,
    decrease this. If you want to incorporate a
    reload, increase this.
*/
int runFor = 12;
int numLoops = 0;
int currentRun = 0;
int prevRun = 0;
int duplicateCounter = 0;

int gameModeButtonValue = 0;

/**
 * Initialization
 */
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

    pinMode(gameModeOne, INPUT);
    pinMode(gameModeTwo, INPUT);
    pinMode(gameModeThree, INPUT);
    pinMode(gameModeFour, INPUT);

    playStartUpTune();
}

/**
 * Main program loop - sits and waits for input from the
 * RF receiver (gameModeButtonValue)
 */
void loop()
{
    gameModeButtonValue = 0;
    gameModeButtonValue = digitalRead(gameModeOne);
    if (gameModeButtonValue > 0)
    {
        debugLog("Progressive Pace Mode");
        progressivePaceMode();
    }

    gameModeButtonValue = digitalRead(gameModeTwo);
    if (gameModeButtonValue > 0)
    {
        debugLog("Follow Dot Mode");
        followDotMode();
    }

    gameModeButtonValue = digitalRead(gameModeThree);
    if (gameModeButtonValue > 0)
    {
        debugLog("Sundance Mode");
        sundanceMode();
    }

    gameModeButtonValue = digitalRead(gameModeFour);
    if (gameModeButtonValue > 0)
    {
        debugLog("Anticipation Mode");
        anticipationMode();
    }
}

/**
 * Follow The Dot target mode - a random target will light up for
 * a random amount of time and then switch to another target.
 */
void followDotMode()
{
    delay(6000);

    while (numLoops < runFor)
    {
        prevRun = currentRun;
        //will be truncated to int between 0 - 2
        currentRun = random(1, 30000) / 10000;

        //only update the target if we are below the max number of dupes
        if (duplicateCounter < 2)
        {
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

    targetReset();
}

/**
 * Progressive target mode - light up targets in order at an
 * ever increasing speed.
 */
void progressivePaceMode()
{
    currentRun = 0;
    delay(6000);

    while (numLoops < runFor)
    {
        soundBuzzer(1, 0);
        turnOnTarget(targetOne + (currentRun % 3));
        delay(2500 - (currentRun * 200));

        currentRun += 1;
        numLoops += 1;
    }

    targetReset();
}

/**
 * Anticipation target mode - similar to follow the dot
 * mode, but with brief pauses in between target switches.
 */
void anticipationMode()
{
    delay(6000);

    while (numLoops < runFor)
    {
        prevRun = currentRun;
        //will be truncated to int between 0 - 2
        currentRun = random(1, 30000) / 10000;

        //only update the target if we are below the max number of dupes
        if (duplicateCounter < 2)
        {
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

            delay(random(1500, 2500));
            turnOffTargets();
            delay(random(3000, 4000));

            numLoops += 1;
        }
    }

    targetReset();
}

/**
 * Sundance target mode - quickly turn on one of the targets
 * and then turn it back off. Runs once.
 */
void sundanceMode()
{
    delay(random(4000, 6000));
    soundBuzzer(1, 0);

    currentRun = random(1, 30000) / 10000;

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

    delay(2500);
    soundBuzzer(1, 0);
    turnOffTargets();

    delay(1000);
    targetReset();
}

/**
 * Checks to see if we have more than two duplicate runs
 * param int currentRun Current run's target value
 * param int previousRun Previous run's target value
 * return bool Returns true if we've had two runs of the same target
 */
bool checkForDupes(int currentRun, int previousRun)
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

    debugLog("# dupes - " + duplicateCounter);

    if (duplicateCounter < 2)
    {
        return false;
    }
    return true;
}

/**
 * Turns on the light for the current target
 * param int currentTarget Target to light up
 */
void turnOnTarget(int currentTarget)
{
    turnOffTargets();
    //turn on the sent in target
    digitalWrite(currentTarget, HIGH);

    debugLog((String) currentTarget);
}

/**
 * Turns off all the target lights
 */
void turnOffTargets()
{
    digitalWrite(targetOne, LOW);
    digitalWrite(targetTwo, LOW);
    digitalWrite(targetThree, LOW);
}

/**
 * Completely reset the targets. Sounds end buzzer.
 */
void targetReset()
{
    turnOffTargets();
    soundBuzzer(3, 500);

    numLoops = 0;
    currentRun = 0;
    prevRun = 0;
    duplicateCounter = 0;
}

/**
 * Wrapper for sounding the buzzer
 */
void soundBuzzer(int numberOfBuzzes, int interval)
{
    for (int i = 0; i < numberOfBuzzes; i++)
    {
        tone(buzzerPin, 4000, 400);
        delay(interval);
    }
}

/**
 * Plays a silly tune at startup
 */
void playStartUpTune()
{
    tone(buzzerPin, 5000, 400);
    delay(500);
    tone(buzzerPin, 4000, 400);
    delay(500);
    tone(buzzerPin, 3000, 400);
    delay(500);
    tone(buzzerPin, 3000, 300);
    delay(400);
    tone(buzzerPin, 3500, 300);
    delay(400);
    tone(buzzerPin, 3000, 300);
}

/**
 * If debugging is on, print messages to the serial monitor.
 * Enable debugging by setting the debug const to 1.
 */
void debugLog(String message)
{
    if (debug)
    {
        Serial.println(message);
    }
}
