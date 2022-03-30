/* 
 Tekan * untuk Cancle
 Tekan # untuk Ok
*/
#include <Keypad.h>
#include <Password.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

const int ledM = 13;
const int ledH = 12;
const int buzz = 11;
byte currentLength = 0;

Password password = Password("1234"); //Password bisa di ubah ubah

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Deklarasi Pin dimulai dari Kiri Keypad
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad. 
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  pinMode(ledM, OUTPUT);
  pinMode(ledH, OUTPUT);
  pinMode(buzz, OUTPUT);
  
  digitalWrite(ledM, LOW);
  digitalWrite(ledH, LOW);
  digitalWrite(buzz, LOW);
  
  Serial.begin(9600);
  customKeypad.addEventListener(keypadEvent);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,1);
  lcd.print("Keamanan Pintu");
  lcd.setCursor(7,2);
  lcd.print("Rumah");
  delay(1000);
  lcd.clear();
}
  
void loop(){
    lcd.setCursor(0,1);
    lcd.print("Masukkan Password");
    lcd.setCursor(0,2);
    lcd.print("Pass : ");
    customKeypad.getKey();
}

void checkPassword(){
  if (password.evaluate()){
    True(2, 100);
    lcd.clear();
    lcd.setCursor(3,1);
    lcd.print("Silahkan Masuk");
    delay(5000);
    lcd.clear();
    lcd.setCursor(5,1);
    lcd.print("Terkunci");
    True(1, 100);
    delay(500);
    password.reset();
  } else {
    False(1);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Salah, Coba Lagi!");
    delay(3000);
    password.reset();
  }
}

void keypadEvent(KeypadEvent eKey){
  
  switch (customKeypad.getState()){  
    case PRESSED:
//  lcd.setCursor(0,0);
//        lcd.print(eKey);
  switch (eKey){
    case '#': checkPassword(); lcd.clear(); currentLength=0;break;
    case '*': password.reset(); lcd.clear();currentLength=0; break;
    default:// password.append(eKey);
          password << eKey;
          currentLength++;
        
        //Print some feedback.
        lcd.setCursor(0,2);
        lcd.print("Pass : ");
        for (byte i=0; i<currentLength; i++){
            lcd.print('*');
        }
    }
  }  
}  

void True (int jumlah, int jeda){
  for (int i=1; i <= jumlah; i++){
    digitalWrite(ledH, HIGH);
    digitalWrite(buzz, HIGH);
    delay(jeda);
    digitalWrite(ledH, LOW);
    digitalWrite(buzz, LOW);
    delay(jeda);
  }
}

void False (int jumlah){
  for (int i=1; i <= jumlah; i++){
    digitalWrite(ledM, HIGH);
    digitalWrite(buzz, HIGH);
    delay(800);
    digitalWrite(ledM, LOW);
    digitalWrite(buzz, LOW);
  }
}
