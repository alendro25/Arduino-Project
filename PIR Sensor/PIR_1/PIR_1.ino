int ledPin = 13;                // LED 
int pirSensor = 12;                 // PIR Out pin 
int pirStatus = LOW;                   // PIR status
int nilaiPIR = 0;
 
void setup() {
  pinMode(ledPin, OUTPUT);     
  pinMode(pirSensor, INPUT);     
 
  Serial.begin(9600);
}
 
void loop(){
  nilaiPIR = digitalRead(pirSensor);
  if (nilaiPIR == HIGH){
    digitalWrite(ledPin, HIGH);
    if (pirStatus == LOW){
      Serial.println("OBJEK TERDETEKSI");
      pirStatus = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW);
    if (pirStatus == HIGH){
      Serial.println("OBJEK TIDAK TERDETEKSI");
      pirStatus = LOW;
    }
  }
  
}
