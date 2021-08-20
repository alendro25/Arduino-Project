byte ldr = A0;
byte led = 13;
byte relay = 2;
int nilai;

void setup() {
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  nilai = analogRead(ldr);
  Serial.print("Nilai LDR: ");
  Serial.println(nilai);

  if (nilai > 500 && nilai < 920) {
    digitalWrite(relay, HIGH);
  }
  else {
    digitalWrite(relay, LOW);
  }

}
