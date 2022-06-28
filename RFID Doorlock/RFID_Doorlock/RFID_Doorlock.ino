#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_HIJAU 7 //akses diterima LED BIRU pin
#define LED_MERAH 8 //akses ditolak LED BIRU pin
#define LED_KUNING 5 //LED Standby
#define BUZZER 4 //buzzer pin
#define RELAY 2 //relay pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(RELAY, HIGH);
  digitalWrite(LED_KUNING, LOW);
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  digitalWrite(LED_KUNING, HIGH);
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }  
   //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "04 0A 4B 8A 38 58 80" || content.substring(1) == "59 F4 E4 43") //change here the UID of the card/cards that you want to give access
  {
    digitalWrite(LED_KUNING, LOW);
    Serial.println("akses kartu diterima");
    Serial.println();
    delay(500);
    digitalWrite(LED_HIJAU, HIGH);
    digitalWrite(RELAY, LOW);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
    delay(5000);
    digitalWrite(RELAY, HIGH);
    digitalWrite(LED_HIJAU, LOW);
  } else   {
    digitalWrite(LED_KUNING, LOW);
    Serial.println("akses kartu ditolak");
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(RELAY, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_HIJAU, LOW);
    noTone(BUZZER);
  }
  
}
