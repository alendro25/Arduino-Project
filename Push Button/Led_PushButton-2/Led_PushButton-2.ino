const byte button = 2;
const byte led = 13;

int statusTombol = 0;
boolean statusLed = false;

void setup() 
{
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
}

void loop() 
{
  statusTombol = digitalRead(button);

  if(statusTombol == 1){
    statusLed=!statusLed;
    delay(1000);
  }
  digitalWrite(led, statusLed);
}
