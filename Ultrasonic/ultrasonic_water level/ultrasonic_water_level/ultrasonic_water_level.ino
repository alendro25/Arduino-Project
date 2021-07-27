#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,20,4);

//pin Ultrasonik
#define trigPin 7
#define echoPin 6

#define led1 9
#define led2 10
#define led3 11
#define relay 4

void setup() {
  Serial.begin (9600);
  lcd.init();
  lcd.backlight();
 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(relay, OUTPUT);

  digitalWrite(relay, HIGH);

  lcd.setCursor(4,0);
  lcd.print("Refil Pureit");
  lcd.setCursor(6,1);
  lcd.print("Otomatis");
  lcd.setCursor(6,3);
  lcd.print("Tunggu...");
  delay(5000);
  lcd.clear();
}

void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(led1, redValue);
  analogWrite(led2, greenValue);
  analogWrite(led3, blueValue);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

//  Serial.println(distance);

  if (distance > 18) 
  {
    setColor(255, 0, 0);
    digitalWrite(relay, LOW);
    lcd.setCursor(7,0);
    lcd.print("Pureit");
    lcd.setCursor(0,1);
    lcd.print("Level Air :");
    lcd.setCursor(12,1);
    lcd.print(distance);
//    lcd.setCursor(15,1);
//    lcd.print("cm");
    lcd.setCursor(0,2);
    lcd.print("Status : Habis");
    
    Serial.print(distance);
    Serial.println(" (Habis)");
  }
  
  if (distance>3 && distance <= 18) 
  {
    digitalWrite(relay, LOW);
    setColor(255, 255, 0);

    lcd.setCursor(7,0);
    lcd.print("Pureit");
    lcd.setCursor(0,1);
    lcd.print("Level Air :");
    lcd.setCursor(12,1);
    lcd.print(distance);
//    lcd.setCursor(14,1);4 
    lcd.setCursor(0,2);
    lcd.print("Status : Sedng");
    
    Serial.print("Jarak : ");
    Serial.print(distance);
    Serial.println(" (Sedang)");
  }
  
  if (distance<=3) {
    digitalWrite(relay, HIGH);
    setColor(0, 255, 0);

    lcd.setCursor(7,0);
    lcd.print("Pureit");
    lcd.setCursor(0,1);
    lcd.print("Level Air :");
    lcd.setCursor(12,1);
    lcd.print(distance);
//    lcd.setCursor(14,1);
//    lcd.print("cm");
    lcd.setCursor(0,2);
    lcd.print("Status : Penuh");
    
    Serial.print("Jarak : ");
    Serial.print(distance);
    Serial.println(" (Penuh)");
  }

  delay(500);
}
