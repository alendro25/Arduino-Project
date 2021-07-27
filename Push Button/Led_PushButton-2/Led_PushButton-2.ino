const byte button = 2;
const byte led = 13;

int statusTombol = 0;
int statusLed = LOW;

void setup() 
{
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
}

void loop() 
{
  statusTombol = digitalRead(button);
  Serial.println(statusTombol);
  if(statusTombol == 1){
    statusLed=!statusLed;
//    delay(1000);
  }
  digitalWrite(led, statusLed);
}
