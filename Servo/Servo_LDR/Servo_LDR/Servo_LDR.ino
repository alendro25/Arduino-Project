#include <Servo.h>
Servo myservo;
int pinSensor = A5;
int sensor;

void setup() {
  myservo.attach(2);
  Serial.begin(9600);
  myservo.write(90);
}

void loop() {
  sensor=analogRead(pinSensor);
  Serial.println(sensor);
  if(sensor>390){
    myservo.write(130); 
    delay(50);
  }else{    
  myservo.write(90); 
  delay(50);
  }

}
