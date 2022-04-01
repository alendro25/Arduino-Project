#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int ldr = 2;
const int btn = 3;
const int laser = 4;
const int buzz = 6;
const int ledM = 7;
const int ledH = 8;

LiquidCrystal_I2C lcd(0x27,20,4);

boolean benar = false;
boolean salah = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(ldr, INPUT);
  pinMode(laser, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(ledM, OUTPUT);
  pinMode(ledH, OUTPUT);

  digitalWrite(laser, HIGH);
  digitalWrite(buzz, LOW);
  digitalWrite(ledM, LOW);
  digitalWrite(ledH, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,1);
  lcd.print("Sistem Keamanan ");
  lcd.setCursor(7,2);
  lcd.print("Rumah ");
  delay(3000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrV = digitalRead(ldr);
  int btnV = digitalRead(btn);
  
  if(btnV == HIGH){
    if(!benar){  
      digitalWrite(buzz, HIGH);
      delay(100);
      digitalWrite(buzz, LOW);
      benar = true;
      salah = false;
    }
    
    Serial.println("Secure Mode");
        
    if (ldrV == LOW){
      lcd.clear();
      digitalWrite(ledM, LOW);
      digitalWrite(buzz, LOW);
      digitalWrite(ledH, HIGH);
      Serial.println("Pintu Terkunci \n");
      lcd.setCursor(2,0);
      lcd.print("-- Secure Mode -- ");
      lcd.setCursor(3,2);
      lcd.print("Pintu Terkunci");
    } else {
      lcd.clear();
      digitalWrite(ledM, HIGH);
      digitalWrite(buzz, HIGH);
      digitalWrite(ledH, LOW);
      Serial.println("Pintu Terbuka \n");
      lcd.setCursor(2,0);
      lcd.print("-- Secure Mode -- ");
      lcd.setCursor(4,2);
      lcd.print("Pintu Terbuka");
    }
  } else if (btnV == LOW){
    lcd.clear();
    Serial.println("Daily Mode");
    lcd.setCursor(2,1);
    lcd.print("-- Daily Mode -- ");
    digitalWrite(ledH, HIGH);
    digitalWrite(ledM, LOW);
    if(!salah){  
      digitalWrite(buzz, HIGH);
      delay(100);
      digitalWrite(buzz, LOW);
      salah = true;
      benar = false;
    }
  }
  delay(700);
}
