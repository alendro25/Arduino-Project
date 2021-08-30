#include <Servo.h>

Servo myservo;

const int pot = A0;
int hasilPot;
int sudut;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pot, INPUT);
  myservo.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  hasilPot = analogRead(pot);
  sudut = map(hasilPot, 0,1023, 0,180);
  myservo.write(sudut);

  Serial.println(" ");
  Serial.print("Hasil Sebelum Maping : ");
  Serial.println(hasilPot); 
  Serial.print("Hasil Setelah Maping : ");
  Serial.println(sudut); 
  Serial.println(" ");
}
