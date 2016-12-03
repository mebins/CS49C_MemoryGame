//prototypes
void lightUp(int LED);
const int LEDS[] = {3,4,5};
const int PUSHBUTTONS[] = {A0,A1,A2};
const int BUZZER = A3;
const int SOUNDFREQUENCIES[] = {90,140,180};
enum GAMESTATE{LOST, START, CONTINUE};

void setup() {
  GAMESTATE gamestate = START;
  // put your setup code here, to run once:
  for(int i = 0; i < 3; i++)
  {
    pinMode(LEDS[i],OUTPUT);
    pinMode(PUSHBUTTONS[i],INPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(gamestate == START)
  {
    
  }
  else if(gamestate == CONTINUE)
  {
    
  }
  else if(gamestate == LOST)
  {

  }
}

void lightUp(int LED)
{
  for(int i = 0; i < 3; i++)
  {
    if(i != LED)
    {
      digitalWrite(LEDS[i],LOW);
    }
    else
    {
      digitalWrite(LEDS[i],HIGH);
      analogWrite(BUZZER,SOUNDFREQUENCIES[i]);
    }
  }
}

