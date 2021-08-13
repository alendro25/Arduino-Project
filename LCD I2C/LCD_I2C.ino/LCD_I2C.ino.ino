#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>;

LiquidCrystal_I2C lcd(0x27,20,4);
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

byte derajat[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  //  Print a message to the LCD
  lcd.backlight();
  lcd.createChar(0, derajat);
  lcd.setCursor(0,1);
  lcd.print("Monitoring");
  lcd.setCursor(14,1);
  lcd.print("Suhu");
  lcd.setCursor(5,2);
  lcd.print("Tunggu...");
  delay(5000);
}

void loop() {
    delay(2000);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity : ");
    Serial.println(hum);
    Serial.print("Temperature : ");
    Serial.println(temp);
    
    //Print temp and humidity values to lcd monitor
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Humidity:");
    lcd.setCursor(11,1);
    lcd.print(hum);
    lcd.setCursor(15,1);
    lcd.print(" %");
    lcd.setCursor(0,2);
    lcd.print("Temp:");
    lcd.setCursor(7,2);
    lcd.print(temp);
    lcd.setCursor(13,2);
    lcd.write((byte)0);
    lcd.setCursor(14,2);
    lcd.print("C");
}
