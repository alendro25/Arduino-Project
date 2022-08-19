#include <DS3231.h>
#include <Wire.h>

DS3231 rtc(SDA, SCL); // Inisialisasi penggunaan I2C
Time t;
String hari, jam, tanggal;

int statusPIR_A;
int statusPIR_B;

//Inisialisasi Pin Pada Arduino
const int PIR_A = 2;
const int PIR_B = 4;
const int RELAY_1 = 7;
const int RELAY_2 = 8;

//Deklarasi variabel untuk Status
String MATKUL5 = " ";
String MATKUL6 = " ";
String STATE_5 = " ";
String STATE_6 = " ";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Buka Serial Monitor u/ cek Status
  rtc.begin();
  initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  t = rtc.getTime();
  hari = rtc.getDOWStr();
  jam = rtc.getTimeStr();
  tanggal = rtc.getDateStr();

  // Cek kondisi ruangan untuk penerangan otomatis
  ruang_405();
  ruang_406();

  /*Nama_Function(Hari, Waktu Nyala (HH, MM, SS), Waktu Mati (HH, MM, SS), MATKUL)
  Hari(English - Awal Kapital) : Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday */

  /*-------------------------- Jadwal Ruang 405 -----------------------------------*/
  // Hari Senin
  Jadwal_405("Monday", 18, 42, 0, 18, 43, 0, "Bhs. Indonesia"); // Matkul 1
  Jadwal_405("Monday", 19, 0, 0, 21, 0, 0, "Agama"); // Matkul 2
  // Hari Selasa
  Jadwal_405("Tuesday", 18, 42, 0, 18, 43, 0, "Matematika Diskrit"); // Matkul 1
  Jadwal_405("Tuesday", 18, 44, 0, 18, 45, 0, "Database"); // Matkul 2
  // Hari Rabu
  Jadwal_405("Wednesday", 18, 42, 0, 18, 43, 0, "Augmented Reality"); // Matkul 1
  // Hari Kamis
  Jadwal_405("Thursday", 15, 22, 0, 15, 23, 0, "Pemrograman Android"); // Matkul 1
  Jadwal_405("Thursday", 14, 54, 0, 14, 55, 0, "IMK"); // Matkul 2
  // Hari Jumat
  Jadwal_405("Friday", 21, 0, 0, 21, 3, 0, "Pemrograman Dasar"); // Matkul 1
  Jadwal_405("Friday", 19, 10, 0, 19, 12, 0, "IMK"); // Matkul 2
  // Hari Sabtu
  Jadwal_405("Saturday", 16, 5, 0, 16, 7, 0, "IMK"); // Matkul 1
  
  /*---------------------------- Akhir Ruang 405 ----------------------------------*/

  /*-------------------------- Jadwal Ruang 406 -----------------------------------*/
  // Hari Senin
  Jadwal_406("Monday", 18, 42, 0, 18, 43, 0, "Kalkulus I"); // Matkul 1
  Jadwal_406("Monday", 19, 0, 0, 21, 0, 0, "Interpersonal Skill"); // Matkul 2
  // Hari Selasa
  Jadwal_406("Tuesday", 18, 42, 0, 18, 44, 0, "Computer Vision"); // Matkul 1
  // Hari Rabu
  Jadwal_406("Wednesday", 18, 42, 0, 18, 43, 0, "Metode Numerik"); // Matkul 1
  Jadwal_406("Wednesday", 19, 0, 0, 21, 0, 0, "Sistem Operasi"); // Matkul 2
  // Hari Kamis
  Jadwal_406("Thursday", 13, 25, 0, 13, 26, 0, "Pemrograman Dasar"); // Matkul 1
  Jadwal_406("Thursday", 14, 41, 0, 14, 42, 0, "IMK"); // Matkul 2
  // Hari Jumat
  Jadwal_406("Friday", 18, 36, 0, 18, 40, 0, "Pengolahan Sinyal Digital"); // Matkul 1
  Jadwal_406("Friday", 18, 44, 0, 18, 48, 0, "Pemrograman Framework"); // Matkul 2
  // Hari Sabtu
  Jadwal_406("Saturday", 16, 52, 0, 16, 53, 0, "IMK"); // Matkul 1
  /*---------------------------- Akhir Ruang 406 ----------------------------------*/
  
  Serial.println();
  Serial.println("--------------- STATUS ---------------");
  Serial.print("Hari, Tanggal : "); Serial.print(hari); Serial.print(", ");Serial.println(tanggal);
  Serial.print("Jam : "); Serial.println(jam); 
  Serial.print("STATUS Ruang 405" ); Serial.print("("); Serial.print(MATKUL5); Serial.print("): "); Serial.println(STATE_5);
  Serial.print("STATUS Ruang 406" ); Serial.print("("); Serial.print(MATKUL6); Serial.print("): "); Serial.println(STATE_6);
  Serial.println("--------------------------------------");
  Serial.println();
  delay(1000);
}

void initialize(){
  pinMode(PIR_A, INPUT);
  pinMode(PIR_B, INPUT);
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(PIR_A, LOW);
  digitalWrite(PIR_B, LOW);
  for (int i = 1; i < 6; i++){
    Serial.print(i);
    delay(1000);
    Serial.println();
  }
}

void Jadwal_405(String Hari, int OnHour , int OnMin, int OnSec, int OffHour, int OffMin, int OffSec, String MataKuliah){
  if(hari == Hari){
    if((t.hour == OnHour && t.min == OnMin) && t.sec == OnSec){
      MATKUL5 = MataKuliah;
      if(statusPIR_A == HIGH){
          digitalWrite(RELAY_1, LOW);
          STATE_5 = "NYALA";
        }else{
          digitalWrite(RELAY_1, HIGH);
          STATE_5 = "MATI";
        }
    }
    else if((t.hour == OffHour && t.min == OffMin) && t.sec  == OffSec){
      digitalWrite(RELAY_1, HIGH);
      STATE_5 = "MATI";
      MATKUL5 = " ";
    }
  }  
}
  
void Jadwal_406(String Hari, int OnHour , int OnMin, int OnSec, int OffHour, int OffMin, int OffSec, String MataKuliah){
  if(hari == Hari){
      if((t.hour == OnHour && t.min == OnMin) && t.sec == OnSec){
        MATKUL6 = MataKuliah;
        if(statusPIR_B == HIGH){
          digitalWrite(RELAY_2, LOW);
          STATE_6 = "NYALA";
        }else{
          digitalWrite(RELAY_2, HIGH);
          STATE_6 = "MATI";
        }
      }
      else if((t.hour == OffHour && t.min == OffMin) && t.sec == OffSec){
        digitalWrite(RELAY_2, HIGH);
        STATE_6 = "MATI";
        MATKUL6 = " ";
      }
    }  
}
  
void ruang_405(){
  statusPIR_A = digitalRead(PIR_A);
  if (statusPIR_A == HIGH){ //jika sensor membaca gerakan maka relay akan aktif 
    digitalWrite(RELAY_1, LOW);
    Serial.print("(Ruang 405)Gerakan Terdeteksi - ");
    Serial.print("("); Serial.print(statusPIR_A); Serial.println(")");
    STATE_5 = "NYALA";
  }else {
    digitalWrite(RELAY_1, HIGH);//jika sensor tidak membaca gerakan maka relay akan off
    Serial.print("(Ruang 405)Gerakan Tidak Terdeteksi - ");
    Serial.print("("); Serial.print(statusPIR_A); Serial.println(")");
    STATE_5 = "MATI";
  }
}

void ruang_406(){
  statusPIR_B = digitalRead(PIR_B);
  if (statusPIR_B == HIGH) { //jika sensor membaca gerakan maka relay akan aktif
    digitalWrite(RELAY_2, LOW);
    Serial.print("(Ruang 406)Gerakan Terdeteksi - ");\
    Serial.print("("); Serial.print(statusPIR_B); Serial.println(")");
    STATE_6 = "NYALA";
  }else {
    digitalWrite(RELAY_2, HIGH);//jika sensor tidak membaca gerakan maka relay akan off
    Serial.print("(Ruang 406)Gerakan Tidak Terdeteksi - ");
    Serial.print("("); Serial.print(statusPIR_B); Serial.println(")");
    STATE_6 = "MATI";
  }
} 
