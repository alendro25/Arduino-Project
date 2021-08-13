#include <Servo.h>
Servo myservo;
int pos = 0;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  myservo.write(90);

  Serial.println("Mengatur Arah Servo :");
}

void loop() {
  if(Serial.available()>0){
    String baca = Serial.readString();
    unsigned int sudut = baca.toInt();
    Serial.print("Sudut Putar : ");
    Serial.println(sudut);
    myservo.write(sudut);
  }
}
