#include <Servo.h>
Servo myservo;
Servo myservo2;

#define serv 3
#define serv2 4
#define meta2 52
#define meta3 51
#define ir 27

int nMeta2;
int nMeta3;
int nIr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(meta2, INPUT);
  pinMode(meta3, INPUT);
  pinMode(ir, INPUT);

  myservo.attach(serv);
  myservo2.attach(serv2);
  myservo.write(90);
  myservo2.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  nMeta2 = digitalRead(meta2);
  nMeta3 = digitalRead(meta3);
  nIr = digitalRead(ir);


//  Serial.print("Nilai Metal 1 : ");
//  Serial.print(nMeta2);
//  Serial.print("\t");
//
//  Serial.print("Nilai Metal 2 : ");
//  Serial.print(nMeta3);
//  Serial.print("\t");
//
//  Serial.print("Nilai Infrared : ");
//  Serial.println(nIr);

  delay(1000);

  if (nMeta2 == HIGH && nIr == LOW){
    Serial.println("Logam Terdeteksi");
    myservo2.write(0);
    delay(1000);
    myservo2.write(90);
  }
  else if (nMeta3 == LOW && nIr == LOW){
    Serial.println("Logam Terdeteksi");
    myservo.write(0);
    delay(1000);
    myservo.write(90);
  }
  else if (nMeta2 == HIGH && nMeta3 == LOW && nIr == LOW){
    Serial.println("Logam Terdeteksi");
    myservo.write(0);
    delay(1000);
    myservo.write(90);
  }
  else if (nMeta2 == LOW && nMeta3 == HIGH && nIr == LOW){
    Serial.println("Non-Logam Terdeteksi");
    myservo.write(180);
    delay(1000);
    myservo.write(90);
  }
  
  
}
