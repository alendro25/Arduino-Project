int ledPower = 3;
int measurePin = A0;
int samplingTime = 280;
int sleepTime = 100;
 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
float voltDensity = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);

}

void loop() {
      digitalWrite(ledPower,LOW); // power on the LED
      delayMicroseconds(samplingTime);
     
      voMeasured = analogRead(measurePin); // read the dust value
      digitalWrite(ledPower,HIGH); // turn the LED off
      delayMicroseconds(sleepTime);
     
      calcVoltage = ( ( voMeasured * 5 ) / 1024);
      voltDensity = calcVoltage - 0.6;
      dustDensity = voltDensity * 0.17;
     
      Serial.print(" - Dust Density: ");
      Serial.print(dustDensity);
      Serial.println(" Kg/m3");
}
