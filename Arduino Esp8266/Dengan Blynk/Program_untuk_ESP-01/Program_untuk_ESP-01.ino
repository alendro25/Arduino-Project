#include <Blynk.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

String sensorValue; // Menampung nilai potensiometer
char c;

char auth[] = "saqtVbefGwq6DIEjzebtqY8OFd7i4FK6";
char ssid[] = "FA-30";
char pass[] = "19222511";

BLYNK_WRITE(V1) { 
  int pinValue = param.asInt(); // Ketika btn di blynk diklik/push maka akan dikirim nilai ke esp8266
  Serial.print(pinValue); // Hanya untuk debugging
}

void sendSensor()
{
  Serial.print("r"); // Meminta nilai sensor ke Arduino dengan mengirim karakter "r"
  delay(100);

  while(Serial.available() > 0){
    delay(10);
    c = Serial.read();
    sensorValue += c; // sensorValue + c
  }
 
  if (sensorValue.length() > 0) {
    Blynk.virtualWrite(V5, sensorValue);
    delay(10);
    sensorValue = "";
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(3000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
