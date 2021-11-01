/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 * YWROBOT
 *Compatible with the Arduino IDE 1.0
 *Library version:1.1
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

char * messagePadded = "                Twinkle Twinkle Little star how I wonder what you are, up above the world so high, like a diamond in the sky.                ";
char * message = "                 Dino Iki Dino Jum'at                ";

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("Mari bernyanyi");
  lcd.clear();
}

void loop()
{
  lcd.setCursor(5,0);
  lcd.print("Lirik nihh : ");
  
  for (int letter = 0; letter <= strlen(messagePadded) - 20; letter++) //From 0 to upto n-20 characters supply to below function
  {
    showLetters(0, letter);
  }

   for (int letter = 0; letter <= strlen(message) - 20; letter++) //From 0 to upto n-20 characters supply to below function
  {
    showLetterss(0, letter);
  }
}

void showLetters(int printStart, int startLetter)
{
  lcd.setCursor(printStart, 1);
  for (int letter = startLetter; letter <= startLetter + 19; letter++) // Print only 19 chars in Line #2 starting 'startLetter'
  {
    lcd.print(messagePadded[letter]);
  }
  lcd.print(" ");
  delay(250);
}

void showLetterss(int printStart, int startLetter)
{
  lcd.setCursor(printStart, 3);
  for (int letter = startLetter; letter <= startLetter + 19; letter++) // Print only 19 chars in Line #4 starting 'startLetter'
  {
    lcd.print(message[letter]);
  }
  lcd.print(" ");
  delay(250);
}
