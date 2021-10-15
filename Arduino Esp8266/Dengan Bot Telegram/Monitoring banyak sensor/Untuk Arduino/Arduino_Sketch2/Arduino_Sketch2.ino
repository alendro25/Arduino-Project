#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); // Pin 2 = RX, Pin 3 = TX


//pin Ultrasonik
#define trigPin 7
#define echoPin 6

const int led = 13;
String statusLed = "OFF";
String statusSampah = "";
const int sensor1 = random(0,10);
const int sensor2 = random(11,20);
String data = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
      if (distance <= 10){
        mySerial.print(" Sampah Penuh");
        statusSampah = "Sampah Penuh";
      } else if (distance >= 10 && distance < 16){
        mySerial.print(" Sampah Terisi");
        statusSampah = "Sampah Terisi";
      } else {
        mySerial.print(" Sampah Kosong");
        statusSampah = "Sampah Kosong";
      }
//      mySerial.print(" Sensor1 : " + String(sensor1));
    }
     else if (data == "SENSOR2"){
      mySerial.print(" Sensor2 : " + String(sensor2));
    }
     else if (data == "STATUS"){
      mySerial.print(String(" Kondisi Led : " + statusLed + '#' 
                            + " Sensor1 : " + statusSampah + '#'
                            + " Sensor2 : " + sensor2));
    }
    data = "";
  }  
}
