#include <Arduino.h>

#define RELAY_1 A4
#define RELAY_2 A3
#define RELAY_3 A2
#define RELAY_4 A1
#define RELAY_5 A0

#define RELAY_COUNT 5
#define BUFFERCOUNT 5

char inputbuffer[BUFFERCOUNT];
short relays[] = {A0,A1,A2,A3,A4};


// put function declarations here:
enum Instruction
{
  SET_ON,
  SET_OFF,
  IGNORE
};

Instruction getInstruction(char value)
{
    switch (value)
    {
      case '0' :
      return SET_OFF;
      
      case '1' :
      return SET_ON;
      
      case 'x' :
      return IGNORE;

      default:
      return IGNORE; 
    }
}

void do_action(short relay, Instruction action)
{
  switch (action)
  {

    case SET_ON:
    digitalWrite(relay, HIGH);
    break;
    
    case SET_OFF:
    digitalWrite(relay, LOW);
    break;

    default:
    break;

  }
}



void setup() {
  Serial.begin(115200);
  for(int i =0; i < RELAY_COUNT; i++)
  {
    pinMode(relays[i], OUTPUT);
  }
}



void loop()
{
  delay(1);
  if(Serial.available() > BUFFERCOUNT)
  {
    for(int i = 0; i < BUFFERCOUNT; i++)
    {
      inputbuffer[i] = Serial.read();
    }

    Serial.flush();
    do_action(relays[0], getInstruction(inputbuffer[0]));
    do_action(relays[1], getInstruction(inputbuffer[1]));
    do_action(relays[2], getInstruction(inputbuffer[2]));
    do_action(relays[3], getInstruction(inputbuffer[3]));
    do_action(relays[4], getInstruction(inputbuffer[4]));

    for(int  i = 0; i < RELAY_COUNT; i++)
    {
      Serial.print(digitalRead(relays[i]) == HIGH? '1': '0');
    }    
    Serial.println();
  }
  while(Serial.available())
  {
    Serial.read();
  }
}
