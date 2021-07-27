#include <Servo.h>
Servo myservo;
int servo = 2;
int LDR1 = A5;
int LDR2 = A2;
int sensor1;
int sensor2;

void setup() {
  myservo.attach(servo);
  Serial.begin(9600);
  myservo.write(90);
}

void loop() {
  sensor1 = analogRead(LDR1);
  sensor2 = analogRead(LDR2);
  Serial.print("sensor 1: ");
  Serial.println(sensor1);
  Serial.print("sensor 2: ");
  Serial.println(sensor2);
  if(sensor1>=390){
    myservo.write(138); 
    delay(80);
  }else if(sensor2>=390){
    myservo.write(138); 
    delay(80);
  }else{    
    myservo.write(90); 
    delay(50);
  }

}
