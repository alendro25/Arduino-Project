#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Password.h>

byte currentLength = 0;

Password password = Password("1234"); //Password bisa di ubah ubah

LiquidCrystal_I2C lcd(0x27,20,4); //pin lcd yang di gunakan

const byte ROWS= 4; //baris pada keypad
const byte COLS= 4; //Kolom pada keypad

//inisialisasi led dan relay sebagai output bila password betul maka akan menyala relay,
//dan bila password salah akan menyala led merah

const int red = 13; //pin yang digunakan u/ indikator salah password
const int green = 12; //pin yang digunakan u/ indikator password benar

/*keymap mendefinisikan tombol ditekan sesuai
dengan baris dan kolom seperti muncul pada keypad*/
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

void setup(){
  Serial.begin(9600);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);

  //sumber diambil pada examples di library password.
  keypad.addEventListener(keypadEvent);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Password");
  
  lcd.setCursor(0, 1);
  lcd.print("Gerald AT");
  delay(5000);
  lcd.clear();
}

// Jika tombol ditekan, tombol ini disimpan dalam 'keypressed' variabel
// Jika kunci tidak sama dengan 'NO_KEY', maka tombol ini dicetak
// Jika jumlah = 17, maka penghitungan reset kembali ke 0 (ini berarti tidak ada tombol yang ditekan selama proses pemindaian seluruh keypad

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Masukan Password");
  lcd.setCursor(0,1);
  lcd.print("Pass: ");
  keypad.getKey();;
}

void checkPassword(){
   if(password.evaluate()){        
      digitalWrite(green, HIGH); 
      lcd.clear();
      lcd.print("Berhasil");
      delay(5000);//Lama waktu relay
      digitalWrite(green, LOW);
   }
   else {
      digitalWrite(red, HIGH);
      lcd.clear();
      lcd.print("Salah coba lagi");
      delay(5000);//lama led on 
      digitalWrite(red, LOW);  
   }
}


void keypadEvent(KeypadEvent eKey){
  
  switch (keypad.getState()){  
    case PRESSED:
  lcd.setCursor(0,1);
        lcd.print(eKey);
  switch (eKey){
    case '*': checkPassword(); lcd.clear(); currentLength=0; break;
    case '#': password.reset(); lcd.clear();currentLength=0; break;
    default:// password.append(eKey);
          password << eKey;
          currentLength++;
        
        //Print some feedback.
        lcd.setCursor(0,1);
        lcd.print("Pass: ");
        for (byte i=0; i<currentLength; i++){
            lcd.print('*');
        }
           
   }
  }  
}  
