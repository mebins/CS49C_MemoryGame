//prototypes
void lightUp(int LED);
void lightOff(int LED);

//Declerations
const int LEDS[] = {13, 12, 11};
const int PUSHBUTTONS[] = {A0, A1, A2};
int buttonStates[3] = {0};
const int BUZZER = 10;
const int SOUNDFREQUENCIES[] = {200, 240, 255};
enum GAMESTATE {LOST, START, CONTINUE};
GAMESTATE gamestate;
boolean pressed;

void setup() {
  pressed = true;
  gamestate = START;
  // put your setup code here, to run once:
  for (int i = 0; i < 3; i++)
  {
    pinMode(LEDS[i], OUTPUT);
    pinMode(PUSHBUTTONS[i], INPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (gamestate == START)
  {
    lightUp(0);
    delay(500);
    lightUp(1);
    delay(500);
    lightUp(2);
    delay(500);
    lightOff(2);
    gamestate = CONTINUE;
  }
  else if (gamestate == CONTINUE)
  {
    while ((buttonStates[0] = digitalRead(PUSHBUTTONS[0])) == LOW && (buttonStates[1] = digitalRead(PUSHBUTTONS[1])) == LOW && (buttonStates[2] = digitalRead(PUSHBUTTONS[2])) == LOW)
    {
      pressed = false;
    }
    if (!pressed)
    {
      if (buttonStates[0]) {
        lightUp(0);
        pressed = true;
      }
      else if (buttonStates[1]) {
        lightUp(1);
        pressed = true;
      }
      else if (buttonStates[2]) {
        lightUp(2);
        pressed = true;
      }
      delay(250);
      for (int i = 0; i < 3; i++)
      {
        lightOff(i);
      }
    }
  }
  else if (gamestate == LOST)
  {

  }
}

void lightUp(int LED)
{
  for (int i = 0; i < 3; i++)
  {
    if (i != LED)
    {
      digitalWrite(LEDS[i], LOW);
    }
    else
    {
      digitalWrite(LEDS[i], HIGH);
      tone(BUZZER, SOUNDFREQUENCIES[i], 250);
    }
  }
}
void lightOff(int LED)
{
  digitalWrite(LEDS[LED], LOW);
}

