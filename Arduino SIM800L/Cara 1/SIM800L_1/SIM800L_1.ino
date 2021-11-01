#include <SoftwareSerial.h>
SoftwareSerial sim(2,3); // RX dan TX

int led = 13;
String pesan;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  digitalWrite(led, LOW);
  sim.begin(9600);
  delay(100);
  sim.println("AT");
  sim.println("AT+CMGF=1");
  sim.println("AT+CNMI=1,2,0,0,0");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    sim.write(Serial.read());
  }
  if(sim.available() > 0 ){
    pesan = sim.readStringUntil('\n');
    Serial.println(pesan);

    if(pesan == "Hai\r"){
      digitalWrite(led, HIGH);
      eksekusi(1);
      Serial.println("Led Menyala");
    }
    if(pesan == "A\r"){
      digitalWrite(led, LOW);
      eksekusi(0);
      Serial.println("Led Mati");
    }
  }
  
}

void eksekusi(bool tipe){
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"083831144432\"\r");
  delay(100);
  if(tipe==1){
    sim.println("LED Menyala.\r");
  }else {
    sim.println("LED Mati.\r");
  }
  delay(100);
  sim.println((char)26);
}
