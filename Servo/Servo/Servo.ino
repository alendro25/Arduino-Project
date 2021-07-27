#include <Servo.h>
Servo myservo;
int servo = 9;
int pos;

void setup() {
  myservo.attach(servo);
  Serial.begin(9600);
  myservo.write(0); 
}

void loop() {
  delay(3000);
   for(pos = 00; pos < 180; pos += 1)  //fungsi perulangan yang akan dijadikan PWM dengan kenaikan 1
 {
  Serial.println(pos);
  myservo.write(pos); //prosedur penulisan data PWM ke motor servo
  delay(15); //waktu tunda 15 ms                 
 } 
 delay(3000);
 for(pos = 180; pos>=1; pos-=1)  //fungsi perulangan yang akan dijadikan PWM dengan penurunan 1
 { 
  Serial.println(pos);                             
  myservo.write(pos);                 
  delay(15);                        
 }
}
