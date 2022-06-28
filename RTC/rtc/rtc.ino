#include <DS3231.h>

DS3231 rtc(SDA, SCL); // Inisialisasi penggunaan I2C

Time t;
#define buz 11

String hari, tanggal, jam;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rtc.begin();

  rtc.setDOW(SATURDAY);
  rtc.setDate(18, 6, 2022);
  rtc.setTime(16, 19, 18);
}

void loop() {
  // put your main code here, to run repeatedly:
  hari = rtc.getDOWStr();
  jam = rtc.getTimeStr();
  tanggal = rtc.getDateStr();
  
  Serial.print(hari); // Prosedur pembacaan Hari
  Serial.print(", ");

  Serial.print(tanggal); // Prosedur pembacaan Tanggal
  Serial.print(" -- ");

  Serial.println(jam); // Prosedur pembacaan Jam

  delay(1000);
}
