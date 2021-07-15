#define r1 8

void setup() {
  pinMode(r1, OUTPUT);
}

void loop() {
    // Nyalain kipas
    digitalWrite(r1, LOW);//NO=NYALA
    // Kasi Delay 2 detik
    delay(5000);
    digitalWrite(r1, HIGH);
    // Kasi Delay 2 detik
    delay(10000);
}
