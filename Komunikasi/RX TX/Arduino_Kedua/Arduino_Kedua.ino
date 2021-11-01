#include <SoftwareSerial.h>

SoftwareSerial serial (10,11);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    serial.write(Serial.read());
  }
  if (serial.available()) {
      Serial.write(serial.read());
  }

}
