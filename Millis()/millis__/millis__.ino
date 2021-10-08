#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Lampu 1
int led1 = 7;
unsigned long waktuSebelumnya_lampu1 = 0;
bool lampu1Status = false;
unsigned long intervalLampu1 = 1000;

// Lampu 2
int led2 = 8;
unsigned long waktuSebelumnya_lampu2 = 0;
bool lampu2Status = false;
unsigned long intervalLampu2 = 500;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  lcd.home(); // Sama dengan lcd.setCursor(0,0);
  lcd.print(F("Gerald Millis()"));
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long waktuSekarang = millis();
  lcd.setCursor(0,1);
  lcd.print(F("Time : "));
  lcd.print(waktuSekarang / 1000); // Supaya jadi detik dibagi 1000
  
  //  Lampu 1
  lcd.setCursor(0,2);
  lcd.print(F("Lampu 1 : "));
  if (waktuSekarang - waktuSebelumnya_lampu1 > intervalLampu1){
    // Flagging
    lampu1Status = !lampu1Status;

    if (lampu1Status){
      lcd.setCursor(10, 2);
      lcd.print(F("ON "));
      digitalWrite(led1, HIGH);
    } else {
      lcd.setCursor(10, 2);
      lcd.print(F("OFF"));
      digitalWrite(led1, LOW);
    }
    waktuSebelumnya_lampu1 = waktuSekarang;
  }

  //  Lampu 2
  lcd.setCursor(0,3);
  lcd.print(F("Lampu 2 : "));
  if (waktuSekarang - waktuSebelumnya_lampu2 > intervalLampu2){
    // Flagging
    lampu2Status = !lampu2Status;

    if (lampu2Status){
      lcd.setCursor(10, 3);
      lcd.print(F("ON "));
      digitalWrite(led2, HIGH);
    } else {
      lcd.setCursor(10, 3);
      lcd.print(F("OFF"));
      digitalWrite(led2, LOW);
    }
    waktuSebelumnya_lampu2 = waktuSekarang;
  }

  
}
