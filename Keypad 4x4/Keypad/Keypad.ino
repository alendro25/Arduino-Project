#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

String keyData;

const byte ROWS= 4; //baris pada keypad
const byte COLS= 4; //Kolom pada keypad

char keys[ROWS][COLS] =
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte rowPins[ROWS]= {9,8,7,6}; 
byte colPins[COLS]= {5,4,3,2}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("Keypad");
  
  lcd.setCursor(2, 1);
  lcd.print("Arduino Uno");
  delay(5000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("Tekan Keypad :");
  
  char keypressed = keypad.getKey();
  
  if (keypressed){
    if (keyData.length() < 20){ // Menampung 20 karakter
      keyData += keypressed;
      lcd.setCursor(0,1);
      lcd.print(keyData);
    }
  }
  // Untuk Mereset LCD dan data yg tersimpan
  if (keypressed == 'D'){
    lcd.clear();
    keyData = "";
  }
}
