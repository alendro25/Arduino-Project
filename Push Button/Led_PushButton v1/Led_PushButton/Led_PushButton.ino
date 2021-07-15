const int ledPin = 13;
const int switchPin = 2;

void setup()
{
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if(digitalRead(switchPin) == HIGH){
    digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }
}
