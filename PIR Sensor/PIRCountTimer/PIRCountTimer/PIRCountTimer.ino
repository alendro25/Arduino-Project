#include "Countimer.h"
#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Countimer timer;
DS3231  rtc(SDA, SCL);
Time t;
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int led = 12;
const int pir = 2;
int pirStatus = LOW;
int nilaiPir;

void setup() {
  Serial.begin(9600);
  rtc.begin();
  lcd.init();
  lcd.backlight();
  
  pinMode(led, OUTPUT);
  pinMode(pir, INPUT);
  digitalWrite(led, LOW);
  digitalWrite(pir, LOW);

    // Set up count down timer with 10s and call method onComplete() when timer is complete.
    // 00h:00m:10s
     timer.setCounter(0, 0, 10, timer.COUNT_DOWN, onComplete);

    // Print current time every 1s on serial port by calling method refreshClock().
    // timer.setInterval(refreshClock, 1000);
}

void refreshClock() {
  Serial.print("Current count time is: ");
  Serial.println(timer.getCurrentTime());
  lcd.setCursor(2,0);
  lcd.print("Count : ");
  lcd.print(timer.getCurrentTime());
}

void onComplete() {
  Serial.println("Complete!!!");
  lcd.setCursor(6,2);
  lcd.print("LED Mati");
  digitalWrite(led, LOW);
}

void loop() {
//  timer.setCounter(0, 0, 10, timer.COUNT_DOWN, onComplete);
  timer.setInterval(refreshClock, 1000);
  
  // Run timer
  timer.run();

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
  
    // Now timer is running and listening for actions.
    // If you want to start the timer, you have to call start() method.
    if(nilaiPir == HIGH) {
      timer.start();
      lcd.setCursor(4,2);
      lcd.print("LED Menyala");
      digitalWrite(led, HIGH);
    }
//    else{
//      lcd.setCursor(6,2);
//      lcd.print("LED Mati");
//      digitalWrite(led, LOW);
//    }
}
