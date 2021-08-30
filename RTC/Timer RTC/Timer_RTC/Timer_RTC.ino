/*
--------------------------------
 Timer Project RTC dan LCD I2C
--------------------------------
*/

#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,20,4);
DS3231 rtc(SDA, SCL); // Inisialisasi penggunaan I2C
int led = 13;
int led2 = 12;

Time waktu;
String hari, jam, tanggal;
float suhu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  rtc.begin();
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(led2, HIGH);

//  rtc.setDOW(TUESDAY);
//  rtc.setDate(24, 8, 2021);
//  rtc.setTime(12, 39, 40);
}

void loop() {
  // put your main code here, to run repeatedly:
  hari = rtc.getDOWStr();
  jam = rtc.getTimeStr();
  tanggal = rtc.getDateStr();
  suhu = rtc.getTemp();

  lcd.setCursor(6,0);
  lcd.print(suhu);
  lcd.setCursor(12,0);
  lcd.print("C");
  
  lcd.setCursor(0,1);
  lcd.print(hari);// Prosedur pembacaan Hari
  lcd.setCursor(7,1);
  lcd.print(", ");

  lcd.setCursor(9,1);
  lcd.print(tanggal); // Prosedur pembacaan Tanggal

  lcd.setCursor(5,2);
  lcd.print(jam); // Prosedur pembacaan Jam

  delay(1000);
  lcd.clear();

  waktu = rtc.getTime();
  if(waktu.sec >= 10 && waktu.sec <= 30){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }

  
}
