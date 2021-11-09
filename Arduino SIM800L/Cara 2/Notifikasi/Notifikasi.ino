#include <SoftwareSerial.h>
#include <DHT.h>;

//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

SoftwareSerial sim(2,3); // RX dan TX

int dustPin = A0; // dust sensor - Arduino A0 pin
int ledPin = 5;
int ledYpin = 11;
int ledGpin = 12;
String pesan;
String Status = "Mati";
int Persen;

int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
 
float voltsMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
 
void setup()
{
  dht.begin();
  Serial.begin(9600);
  sim.begin(9600);
  
  pinMode(ledPin,OUTPUT);
  pinMode(ledYpin,OUTPUT);
  pinMode(ledGpin, OUTPUT);
  digitalWrite(ledYpin, LOW);
  digitalWrite(ledGpin, LOW);
  delay(100);
  
  sim.println("AT");
  sim.println("AT+CMGF=1");
  sim.println("AT+CNMI=1,2,0,0,0");

  for(int i = 0; i < 5; i++){
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
 
  delayMicroseconds(40);
  digitalWrite(ledPin,HIGH); // turn the LED off
  delayMicroseconds(9680);
 
  //measure your 5v and change below
  calcVoltage = voltsMeasured * (5.0 / 1024.0);
  dustDensity = 0.17 * calcVoltage - 0.1;
  delay(1000);

  // Sistem Notifikasi jika kepekatan 80% maka SIM800L kirim SMS
  if (Persen >= 80){
      digitalWrite(ledYpin, HIGH);
      delay(500);
      digitalWrite(ledYpin, LOW);
      eksekusi(1);
      Serial.println("Filter Kotor");
    }

  // Sistem SMS (Jika kita SMS ke SIM800)
  if(Serial.available()){ // Cek apakah di Serial arduino ada pesan?
    sim.write(Serial.read()); // Kalau ada, peasn dari arduino di tulis di Serial SIM
  }
  
  if(sim.available() > 0 ){ // Jika di Serial SIM terdapat pesan
    pesan = sim.readStringUntil('\n'); // Maka, baca sampai ada newLine dan pesan akan
                                       // ditampung pada variabel 'pesan'       
    Serial.println(pesan); // Cetak isi pesan pada Serial Arduino

    if(pesan == "Nyala\r"){ // Jika pesan yg dikirim pada Serial SIM bertuliskan "Nyala"
      digitalWrite(ledGpin, HIGH);
      Status = "Hidup";
      eksekusi(2);
      Serial.println("Led Mati");
    }
    if(pesan == "Mati\r"){ // Jika pesan yg dikirim pada Serial SIM bertuliskan "Mati"
      digitalWrite(ledGpin, LOW);
      Status = "Mati";
      eksekusi(0);
      Serial.println("Led Mati");
    }
    if(pesan == "Status\r"){ // Jika pesan yg dikirim pada Serial SIM bertuliskan "Status"
      eksekusi(3);
      Serial.println("Status Terkini");
    }
    if(pesan == "Dht\r"){ // Jika pesan yg dikirim pada Serial SIM bertuliskan "DHT"
      eksekusi(4);
      Serial.println("Status Suhu dan Kelembaban");
    }
    if(pesan == "Kode\r"){ // Jika pesan yg dikirim pada Serial SIM bertuliskan "DHT"
      eksekusi(5);
      Serial.println("Kode");
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
  }else if(tipe == 0){
    sim.print("LED Mati.\r");
  }
  else if(tipe == 2){
    sim.print("LED Hijau Nyala.\r");
  }
  else if(tipe == 3){
    sim.print("Kondisi filter : ");
    sim.print(Persen);
    sim.println("%");
    sim.print("Led Hijau : ");
    sim.print(Status);
  }
   else if(tipe == 4){
    cekSuhu();
  }
  else if(tipe == 5){
    sim.println(pesan);
  }
  delay(100);
  sim.println((char)26);
} // End Void Eksekusi

void cekSuhu(){
    delay(2000);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    sim.print("Humidity: ");
    sim.print(hum);
    sim.println(" %");
    sim.print("Temp: ");
    sim.print(temp);
    sim.print(" *C");
}
