byte sensorPin = 7;
byte sensorValue = 0;
byte buzzer = 11;
byte led = 13;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(led, OUTPUT);
 pinMode(buzzer, OUTPUT);
 pinMode(sensorPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = digitalRead(sensorPin);
  Serial.print("Pembacaan Sensor Api: ");
  Serial.println(sensorValue);

  if(sensorValue == HIGH){
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }else{
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
  }
}
