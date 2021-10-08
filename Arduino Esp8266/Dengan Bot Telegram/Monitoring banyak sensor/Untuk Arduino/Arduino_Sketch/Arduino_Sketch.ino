#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); // Pin 2 = RX, Pin 3 = TX

const int led = 13;
String statusLed = "OFF";
const int sensor1 = random(0,10);
const int sensor2 = random(11,20);
String data = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
    while (mySerial.available() > 0){
      char c = mySerial.read();
      data += c;
    }

  if(data.length() > 0){
    Serial.println("Data yang masuk : " + data);
    if (data == "LED ON"){
      digitalWrite(led, HIGH);
      statusLed = "ON";
      mySerial.print(" LED is ON");
    }
    else if (data == "LED OFF"){
      digitalWrite(led, LOW);
      statusLed = "OFF";
      mySerial.print(" LED is OFF");
    }
    else if (data == "SENSOR1"){
      mySerial.print(" Sensor1 : " + String(sensor1));
    }
     else if (data == "SENSOR2"){
      mySerial.print(" Sensor2 : " + String(sensor2));
    }
     else if (data == "STATUS"){
      mySerial.print(String(" Kondisi Led : " + statusLed + '#' 
                            + " Sensor1 : " + sensor1 + '#'
                            + " Sensor2 : " + sensor2));
    }
    data = "";
  }  
}
