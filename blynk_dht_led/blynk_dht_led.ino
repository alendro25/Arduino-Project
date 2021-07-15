#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define DHTPIN 0   
#define DHTTYPE DHT22
BlynkTimer timer;

DHT dht(DHTPIN, DHTTYPE);
char auth[] = "VeH0jhkDhcgJFgBdQ2kZx4ypCRmZ7EHz";

char ssid[] = "FA-30";
char pass[] = "19222511";

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
void setup()
{
  pinMode(2,OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

BLYNK_WRITE(V1) { 
digitalWrite(2, param.asInt()); 
}

void loop()
{
  Blynk.run();
  timer.run();
}
