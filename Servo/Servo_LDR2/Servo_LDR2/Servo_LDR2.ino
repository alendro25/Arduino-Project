#include <Servo.h>
Servo myservo;
int sensorLDR=A0;
int hasil;

void setup() {
  myservo.attach(6);
  Serial.begin(9600);
  myservo.write(90); 
}

void loop() {
  hasil = analogRead(sensorLDR);
  hasil = map(hasil, 10, 800, 0, 180);
  Serial.println(hasil);
  myservo.write(hasil);
  delay(500);
}
