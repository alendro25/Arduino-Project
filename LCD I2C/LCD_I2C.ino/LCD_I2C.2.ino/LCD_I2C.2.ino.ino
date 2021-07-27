#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x27, 20, 4);

byte tujuh[] = {
  B11111,
  B11111,
  B00000,
  B00000,
  B11111,
  B11110,
  B11110,
  B11110
};

byte tujuhKanan[] = {
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00011,
  B00111,
  B00111
};

byte tujuh_bawah[] = {
  B11111,
  B00111,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte tujuh_bawahKanan[] = {
  B00111,
  B00111,
  B00111,
  B11111,
  B01111,
  B00111,
  B00011,
  B00001
};

byte lima[] = {
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00011,
  B00011,
  B00011
};

byte limaKanan[] = {
  B11111,
  B11111,
  B11111,
  B00111,
  B00111,
  B11111,
  B11111,
  B11111
};

byte lima_bawah[] = {
  B00000,
  B11100,
  B11100,
  B00000,
  B00000,
  B11100,
  B11000,
  B10000
};

byte lima_bawahKanan[] = {
  B11111,
  B11110,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte love[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};


void setup() {
  Serial.begin(9600); // Memulai Serial
  lcd.init();
  lcd.backlight();

   lcd.createChar(0, tujuh);
   lcd.createChar(1, tujuh_bawah);
   lcd.createChar(2, lima);
   lcd.createChar(3, lima_bawah);
   lcd.createChar(4, tujuhKanan);
   lcd.createChar(5, tujuh_bawahKanan);
   lcd.createChar(6, limaKanan);
   lcd.createChar(7, lima_bawahKanan);
   lcd.createChar(8, love);
   
   lcd.setCursor(0,0);
   lcd.write((byte)0);
   
   lcd.setCursor(0,1);
   lcd.write((byte)1);
  
   lcd.setCursor(1,0);
   lcd.write((byte)4);
   
   lcd.setCursor(1,1);
   lcd.write((byte)5);
  
   lcd.setCursor(2,0);
   lcd.write((byte)2);
  
   lcd.setCursor(3,0);
   lcd.write((byte)6);
  
   lcd.setCursor(2,1);
   lcd.write((byte)3);
  
   lcd.setCursor(3,1);
   lcd.write((byte)7);

  lcd.setCursor(5,0);
  lcd.print("INDONESIA");
  lcd.setCursor(6,1);
  lcd.print("MERDEKA !!!");


  lcd.setCursor(0,2);
  lcd.print("Created By :");

  lcd.setCursor(13,2);
  lcd.print("Gerald");

  lcd.setCursor(3,3);
  lcd.print("Made With");

  lcd.setCursor(14,3);
  lcd.write((byte)8);
}

void loop() {
}
