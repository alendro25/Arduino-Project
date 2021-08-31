#include <Servo.h>
Servo myservo;

//pin Ultrasonik
#define trigPin 7
#define echoPin 8
#define servo 9
#define bzr 12

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(bzr, OUTPUT);
  myservo.attach(servo);
  myservo.write(180); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  Serial.println(distance);

  if(distance >= 4 && distance <= 15  ){
    myservo.write(0);
    digitalWrite(bzr, HIGH);
    delay(70);
    digitalWrite(bzr, LOW);
    delay(3000);
  } else {
    myservo.write(180);
  }
}
