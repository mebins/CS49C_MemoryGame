#include <EEPROM.h>
//prototypes
void lightUp(int LED);
boolean checker(int input, int index);
void playPattern();

//Declerations
#define SIZE 100

struct board {
  int BUZZER;
  int * LEDS;
  int * PUSHBUTTONS;
  int * SOUNDFREQUENCIES;
  int NOISEPIN;
};

int buttonStates[3] = {0};
const int MEMORYADDRESS = 256;
enum GAMESTATE {LOST, START, CONTINUE};
GAMESTATE gamestate;
int level;
struct board arduino;

int leds[3] = {13, 12, 11};

int pushbuttons[3] = {A0, A1, A2};

int sndFrequencys[3] = {200, 240, 255};



boolean pressed;

int pattern[SIZE];
int index;
int highscore;

void setup() {
  arduino.LEDS = leds;
  arduino.BUZZER = 10;
  arduino.PUSHBUTTONS = pushbuttons;
  arduino.SOUNDFREQUENCIES = sndFrequencys;
  arduino.NOISEPIN = A3;
  randomSeed(analogRead(arduino.NOISEPIN));
  Serial.begin(9600);
  pressed = false;
  gamestate = START;
  // put your setup code here, to run once:
  for (int i = 0; i < 3; i++)
  {
    pinMode(arduino.LEDS[i], OUTPUT);
    pinMode(arduino.PUSHBUTTONS[i], INPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (gamestate == START)
  {
    Serial.print("HighScore: ");
    Serial.println(highscore = EEPROM.read(MEMORYADDRESS));

    for (int i = 0; i < SIZE; i++)
    {
      pattern[i] = (int)random(3);
    }

    level = 0;
    index = 0;
    lightUp(0);
    delay(500);
    lightUp(1);
    delay(500);
    lightUp(2);
    delay(500);
    gamestate = CONTINUE;
  }
  else if (gamestate == CONTINUE)
  {
    //START OF LEVEL
    levelUp();
    playPattern();
    Serial.print("Level: ");
    Serial.print(level);
    Serial.print(" Index: ");
    Serial.println(index);
    while (index <= level && gamestate == CONTINUE)
    {
      while ((buttonStates[0] = digitalRead(arduino.PUSHBUTTONS[0])) == LOW && (buttonStates[1] = digitalRead(arduino.PUSHBUTTONS[1])) == LOW && (buttonStates[2] = digitalRead(arduino.PUSHBUTTONS[2])) == LOW)
      {
        pressed = false;
      }
      if (!pressed)
      {
        if (buttonStates[0]) {
          pressed = true;
          if (checker(0, index))
          {
            lightUp(0);
            index++;
          }
          else
          {
            gamestate = LOST;
          }
        }
        else if (buttonStates[1]) {
          pressed = true;
          if (checker(1, index))
          {
            lightUp(1);
            index++;
          }
          else
          {
            gamestate = LOST;
          }

        }
        else if (buttonStates[2]) {
          pressed = true;
          if (checker(2, index))
          {
            lightUp(2);
            index++;
          }
          else
          {
            gamestate = LOST;
          }

        }
      }
    }
    if (index > level)
    {
      level++;
      index = 0;
    }
  }
  else if (gamestate == LOST)
  {
    if (highscore < level + 1) EEPROM.write(MEMORYADDRESS, level + 1);
    gamestate = START;
  }
}

void lightUp(int LED)
{
  for (int i = 0; i < 3; i++)
  {
    if (i != LED)
    {
      digitalWrite(arduino.LEDS[i], LOW);
    }
    else
    {
      digitalWrite(arduino.LEDS[i], HIGH);
      tone(arduino.BUZZER, arduino.SOUNDFREQUENCIES[i], 250);
    }
  }
  delay(250);
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(arduino.LEDS[i], LOW);
  }
  delay(250);
}

void levelUp()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(arduino.LEDS[i], HIGH);
  }
  delay(250);
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(arduino.LEDS[i], LOW);
  }
  delay(250);
}
void playPattern()
{
  for (int i = 0; i <= level; i++)
  {
    lightUp(pattern[i]);
  }
}

boolean checker(const int input, const int index)
{
  if (input == pattern[index])
  {
    return true;
  }
  return false;
}
