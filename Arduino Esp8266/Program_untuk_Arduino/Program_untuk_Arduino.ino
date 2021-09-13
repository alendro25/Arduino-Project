#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11); // RX, TX

String data;
char c;
const int relay = 13;

int pot = A0;
int valPot;
int val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(relay, OUTPUT);
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (mySerial.available() > 0){
    delay(10);
    c = mySerial.read();
    data += c;
  }

  if (data.length() > 0){
    Serial.println(data);
    if (data == "1") {
      digitalWrite(relay, LOW);
      Serial.println("Relay ON");
    } else if (data == "0"){
      digitalWrite(relay, HIGH);
      Serial.println("Relay OFF");
    } else if (data == "r"){
      valPot = analogRead(pot);
      mySerial.print(valPot);
      Serial.println(valPot);
    }
    data = "";
  }
  
}
