#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27,20,4);

#define ir 2
#define metal 4
#define serv 3


void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.setCursor(6,1);
  lcd.print("Pemilah");
  lcd.setCursor(2,2);
  lcd.print("Sampah Otomatis");
  lcd.clear();
  
  myservo.attach(serv);
  Serial.begin(9600);
  myservo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valIr = digitalRead(ir);
  int valMetal = digitalRead(metal);

  Serial.print("Nilai Sensor IR : ");
  Serial.println(valIr);
  Serial.print("Nilai Sensor Metal : ");
  Serial.println(valMetal);
  Serial.println("");

  delay(500);

  lcd.setCursor(0,1);
  lcd.print("-- Buanglah Sampah ");
  lcd.setCursor(2,2);
  lcd.print(" Pada Tempatnya --");

  if( valIr == LOW && valMetal == HIGH ){
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print("Sedang Memproses");
    delay(3000);
    lcd.clear();
    myservo.write(0);
    lcd.setCursor(1,1);
    lcd.print("Sampah Non-Logam");
    lcd.setCursor(4,2);
    lcd.print(" Terdeteksi");
    delay(2000);
    myservo.write(90);
    lcd.clear();
  }
  else if ( valIr == LOW && valMetal == LOW ){
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print("Sedang Memproses");
    delay(3000);
    lcd.clear();
    myservo.write(180);
    lcd.setCursor(4,1);
    lcd.print("Sampah Logam");
    lcd.setCursor(4,2);
    lcd.print(" Terdeteksi");
    delay(2000);
    myservo.write(90);
    lcd.clear();
  }
}
