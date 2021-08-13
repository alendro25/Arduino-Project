#include <Servo.h>
Servo myservo;
Servo myservo2;
int nilai = 0;

void setup() {
  myservo.attach(9); // Harus Pin PWM
  myservo2.attach(6); // Harus Pin PWM
  Serial.begin(9600);
  myservo.write(0);
}

void loop() {
  for(int wait = 0; wait<=10; wait++){
    Serial.println("Wait for Servo");
    Serial.print(wait);
    Serial.println(" detik. ");
    delay(1000);
  }
    for (int i = 0; i<=180; i++){
      Serial.println(i);
      myservo.write(i);
      myservo2.write(i); 
      delay(50);
  }
     for (int i = 180; i>=0; i--){
      Serial.println(i);
      myservo.write(i); 
      myservo2.write(i); 
      delay(50);
    }
}
