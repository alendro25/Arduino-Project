#include <SoftwareSerial.h>

SoftwareSerial sim(2,3); // RX dan TX

int dustPin = A0; // dust sensor - Arduino A0 pin
int ledPin = 5; // led dust sensor - Arduino D5 pin
int Persen;
String pesan;
String Status = "LOW";

boolean low = false;
boolean med = false;
boolean hi = false;

float voltsMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
 
void setup()
{
  Serial.begin(9600);
  sim.begin(9600);
  
  pinMode(ledPin,OUTPUT);
  delay(100);
  
  sim.println("AT");
  sim.println("AT+CMGF=1");
  sim.println("AT+CNMI=1,2,0,0,0");

  for(int i = 0; i < 20; i++){
    Serial.print(i);
    delay(1000);
  }
} // End Void Setup

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin,LOW); // power on the LED
  delayMicroseconds(280);
 
  voltsMeasured = analogRead(dustPin); // read the dust value
  Persen = map(voltsMeasured, 228, 762, 0, 100);

  Serial.print("Ketebalan Debu : ");Serial.print(voltsMeasured);
  Serial.print(" | Kondisi Filter : "); Serial.print(Persen); Serial.println(" %");
 
  delayMicroseconds(40);
  digitalWrite(ledPin,HIGH); // turn the LED off
  delayMicroseconds(9680);
 
  //measure your 5v and change below
  calcVoltage = voltsMeasured * (5.0 / 1024.0); // Mengubah nilai integer menjadi float 0.0 - 5.0 volts
  dustDensity = 0.17 * calcVoltage - 0.1;
  delay(1000);

   if (Persen > 0 && Persen <= 30){
      Status = "LOW";
      low = true;
      med = false;
      hi = false;
   }
   else if (Persen > 31 && Persen <= 90){
      Status = "MED";
      med = true;
      low = false;
      hi = false;
   }
   else if (Persen >= 90){ // Sistem Notifikasi jika ketebalan 90% maka SIM800L kirim SMS
     if(!hi){
      eksekusi(1);
      Status = "HIGH";
      Serial.println("Filter Kotor");
      hi = true;
      low = false;
      med = false;
    }
   }

  // Sistem SMS (Jika kita SMS ke SIM800)
  if(Serial.available()){ // Cek apakah di Serial arduino ada pesan?
    sim.write(Serial.read()); // Kalau ada, peasn dari arduino di tulis di Serial SIM
  }
  
  if(sim.available() > 0 ){ // Jika di Serial SIM terdapat pesan
    pesan = sim.readStringUntil('\n'); // Maka, baca sampai ada newLine dan pesan akan
                                       // ditampung pada variabel 'pesan'       
    Serial.println(pesan); // Cetak isi pesan pada Serial Arduino

    if(pesan == "Status\r"){ // Jika pesan yg dikirim pada Serial SIM bertuliskan "Status"
      eksekusi(2);
      Serial.println("Status Terkini");
    }
  }
} // End Void Loop

void eksekusi(int tipe){
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"083831144432\"\r");
  delay(100);
  if(tipe == 1){
    sim.print("Filter Udara Kotor, silahkan cek dan bersihkan.\r");  
  }
  else if(tipe == 2){
    sim.print("Kondisi filter : ");
    sim.print(Persen);
    sim.print("% - ");
    sim.println(Status);
    sim.print("\nLakukan Pengecekan Secara Berkala Agar Kondisi Filter Udara Tetap Bersih");
  }
  delay(100);
  sim.println((char)26);
} // End Void Eksekusi
