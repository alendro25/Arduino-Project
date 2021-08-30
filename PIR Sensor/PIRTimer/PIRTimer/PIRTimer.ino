#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

DS3231  rtc(SDA, SCL);
Time t;
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int led = 12;
const int pir = 2;
int pirStatus = LOW;
int nilaiPir;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rtc.begin();
  lcd.init();
  lcd.backlight();
  
  pinMode(led, OUTPUT);
  pinMode(pir, INPUT);
  digitalWrite(led, LOW);
  digitalWrite(pir, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  t = rtc.getTime();
  lcd.setCursor(1,1);
  lcd.print(t.hour);
  lcd.setCursor(3,1);
  lcd.print(":");
  lcd.setCursor(4,1);
  lcd.print(t.min);
  lcd.setCursor(6,1);
  lcd.print(":");
  lcd.print(t.sec);
  lcd.setCursor(12,1);
  lcd.print(rtc.getTemp());
  lcd.print(" C");
  delay (1000);
  lcd.clear();

  nilaiPir = digitalRead(pir);
  if(nilaiPir == HIGH){
    digitalWrite(led, HIGH);    
    if(pirStatus == LOW){
      lcd.setCursor(4,2);
      lcd.print("LED Menyala");
      pirStatus = HIGH;  
    }
    
  } else{
    digitalWrite(led, LOW);
    if(pirStatus == HIGH){
      lcd.setCursor(6,2);
      lcd.print("LED Mati");
      pirStatus = LOW;  
    }    
  }

  
}
