// Project Arduino Bilik Disinfektan
// Menggunakan sensor proximity dan Motor DC ditambah relay sebagai saklar elekronik
int sensor = 2;
int nilai;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  nilai = digitalRead(sensor);
  Serial.println(nilai);
  if(nilai == LOW){
    digitalWrite(7, LOW);
    delay(2000);
  }else{
    digitalWrite(7, HIGH);
  }
}
