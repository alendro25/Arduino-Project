#include <DHT.h>;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
String data;
char c;
const int relay = 12;

#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  dht.begin();
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  delay(10);
}

void loop() {
  while(mySerial.available()>0){
    delay(10);
    c = mySerial.read();
    data += c;
  }  
  if (data.length()>0) {
    Serial.println(data);
    if (data == "LAMPU ON") {
      digitalWrite(relay, LOW);
      Serial.println("LAMPU ON");
    } 
    else if (data == "LAMPU OFF") {
      digitalWrite(relay, HIGH);
      Serial.println("LAMPU OFF");
    } 
    else if (data == "TEMPERATURE") {
      
      delay(1000);
      //Read data and store it to variables hum and temp
      temp= dht.readTemperature();
      hum = dht.readHumidity();
      
      //Print temp and humidity values to serial monitor
      mySerial.print("Humidity : ");
      mySerial.println(hum);
      Serial.println(hum);

      mySerial.print("Temperature : ");
      mySerial.print(temp);
      Serial.print(temp);
    }
    data = "";
  }
}
