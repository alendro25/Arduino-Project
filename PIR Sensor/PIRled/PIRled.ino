const int PIR= 12;
const int Pinled = 8;
const int batasdelay = 1000;
int waktuawal = 0;

void setup() {
Serial.begin (9600);

pinMode (Pinled,OUTPUT);
pinMode (PIR,INPUT);
}

void loop() {
 int dataPIR = digitalRead(PIR);
 Serial.println(dataPIR);
   if(dataPIR == HIGH){
    digitalWrite(Pinled, HIGH);
    waktuawal = millis();
//    Serial.println(millis());
   }
   if (millis() - waktuawal > batasdelay){
    digitalWrite(Pinled, LOW);
   }
 delay(500);
  
 }
